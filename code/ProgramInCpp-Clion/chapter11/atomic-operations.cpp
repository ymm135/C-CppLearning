#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 4: 原子操作
// ===================================

// 1. atomic vs 非atomic
int non_atomic_counter = 0;
atomic<int> atomic_counter{0};

void increment_non_atomic(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        non_atomic_counter++;  // 不是原子操作，有竞态条件
    }
}

void increment_atomic(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        atomic_counter++;  // 原子操作，线程安全
    }
}

// 2. atomic操作演示
void atomic_operations_demo() {
    cout << "\n=== atomic操作类型 ===" << endl;
    
    atomic<int> value{10};
    
    // load: 原子读取
    int loaded = value.load();
    cout << "load(): " << loaded << endl;
    
    // store: 原子写入
    value.store(20);
    cout << "store(20): " << value.load() << endl;
    
    // exchange: 原子交换
    int old = value.exchange(30);
    cout << "exchange(30), old value: " << old << ", new value: " << value << endl;
    
    // fetch_add: 原子加法并返回旧值
    old = value.fetch_add(5);
    cout << "fetch_add(5), old: " << old << ", new: " << value << endl;
    
    // fetch_sub: 原子减法
    old = value.fetch_sub(3);
    cout << "fetch_sub(3), old: " << old << ", new: " << value << endl;
    
    // 后置++/前置++
    cout << "value++: " << value++ << ", value: " << value << endl;
    cout << "++value: " << ++value << ", value: " << value << endl;
}

// 3. compare_exchange_weak/strong（CAS操作）
void cas_demo() {
    cout << "\n=== Compare-And-Swap (CAS) ===" << endl;
    
    atomic<int> value{100};
    int expected = 100;
    int desired = 200;
    
    // compare_exchange_strong: 如果value==expected，则设置为desired
    if (value.compare_exchange_strong(expected, desired)) {
        cout << "CAS成功: value从" << expected << "变为" << value << endl;
    } else {
        cout << "CAS失败: expected=" << expected << ", actual=" << value << endl;
    }
    
    // 再次尝试（会失败）
    expected = 100;
    if (value.compare_exchange_strong(expected, 300)) {
        cout << "CAS成功" << endl;
    } else {
        cout << "CAS失败: expected=" << expected << ", actual=" << value << endl;
    }
}

// 4. 自旋锁实现（使用atomic）
class SpinLock {
    atomic<bool> flag{false};
    
public:
    void lock() {
        // 忙等待，直到获得锁
        while (flag.exchange(true, memory_order_acquire)) {
            // 自旋
        }
    }
    
    void unlock() {
        flag.store(false, memory_order_release);
    }
};

SpinLock spinlock;
int spinlock_counter = 0;

void spinlock_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        spinlock.lock();
        spinlock_counter++;
        spinlock.unlock();
    }
}

// 5. 无锁栈（Lock-Free Stack）
template<typename T>
class LockFreeStack {
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    
    atomic<Node*> head{nullptr};
    
public:
    void push(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head.load();
        
        // CAS循环：确保head没有被其他线程修改
        while (!head.compare_exchange_weak(new_node->next, new_node)) {
            // 如果失败，new_node->next会被更新为当前head值
            // 继续尝试
        }
    }
    
    bool pop(T& result) {
        Node* old_head = head.load();
        
        while (old_head && 
               !head.compare_exchange_weak(old_head, old_head->next)) {
            // 如果失败，old_head会被更新，继续尝试
        }
        
        if (old_head) {
            result = old_head->data;
            delete old_head;
            return true;
        }
        return false;
    }
    
    ~LockFreeStack() {
        T dummy;
        while (pop(dummy)) {}
    }
};

// 6. memory_order说明
void memory_order_demo() {
    cout << "\n=== Memory Order ===" << endl;
    
    atomic<int> x{0}, y{0};
    atomic<bool> ready{false};
    
    thread t1([&]() {
        x.store(100, memory_order_relaxed);
        y.store(200, memory_order_relaxed);
        ready.store(true, memory_order_release);  // 释放语义
    });
    
    thread t2([&]() {
        while (!ready.load(memory_order_acquire)) {}  // 获取语义
        
        // 保证看到x和y的最新值
        cout << "x: " << x.load(memory_order_relaxed) << endl;
        cout << "y: " << y.load(memory_order_relaxed) << endl;
    });
    
    t1.join();
    t2.join();
}

// 7. atomic_flag（最轻量的原子类型）
void atomic_flag_demo() {
    cout << "\n=== atomic_flag ===" << endl;
    
    atomic_flag flag = ATOMIC_FLAG_INIT;
    
    // test_and_set: 设置为true并返回旧值
    bool was_set = flag.test_and_set();
    cout << "第一次test_and_set: " << was_set << endl;
    
    was_set = flag.test_and_set();
    cout << "第二次test_and_set: " << was_set << endl;
    
    // clear: 设置为false
    flag.clear();
    cout << "clear后再test_and_set: " << flag.test_and_set() << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 原子操作" << endl;
    cout << "======================================" << endl;
    
    // 1. atomic vs 非atomic对比
    cout << "\n=== atomic vs 非atomic ===" << endl;
    
    vector<thread> threads;
    
    // 非atomic（不安全）
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment_non_atomic, 1000);
    }
    for (auto& t : threads) {
        t.join();
    }
    cout << "非atomic计数器: " << non_atomic_counter 
         << " (期望: 10000)" << endl;
    
    threads.clear();
    
    // atomic（安全）
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment_atomic, 1000);
    }
    for (auto& t : threads) {
        t.join();
    }
    cout << "atomic计数器: " << atomic_counter 
         << " (期望: 10000)" << endl;
    
    // 2. atomic操作
    atomic_operations_demo();
    
    // 3. CAS操作
    cas_demo();
    
    // 4. 自旋锁
    cout << "\n=== 自旋锁 ===" << endl;
    threads.clear();
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(spinlock_increment, 1000);
    }
    for (auto& t : threads) {
        t.join();
    }
    cout << "自旋锁计数器: " << spinlock_counter 
         << " (期望: 10000)" << endl;
    
    // 5. 无锁栈
    cout << "\n=== 无锁栈 ===" << endl;
    LockFreeStack<int> stack;
    
    // 多线程push
    threads.clear();
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&stack, i]() {
            for (int j = 0; j < 100; ++j) {
                stack.push(i * 100 + j);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // pop验证
    int count = 0;
    int value;
    while (stack.pop(value)) {
        count++;
    }
    cout << "无锁栈元素数量: " << count << " (期望: 500)" << endl;
    
    // 6. memory order
    memory_order_demo();
    
    // 7. atomic_flag
    atomic_flag_demo();
    
    cout << "\n======================================" << endl;
    cout << "  原子操作示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
