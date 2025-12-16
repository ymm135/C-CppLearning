#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 2: 互斥锁和锁管理
// ===================================

// 全局共享资源
int shared_counter = 0;
mutex counter_mutex;

// 1. 不安全的计数器（展示竞态条件）
void unsafe_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 竞态条件：读-修改-写 不是原子操作
        shared_counter++;
    }
}

// 2. 使用mutex手动加锁（不推荐）
void manual_lock_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter_mutex.lock();
        shared_counter++;
        counter_mutex.unlock();
        // 如果中间抛异常，unlock永远不会执行！
    }
}

// 3. 使用lock_guard自动管理锁（推荐）
void lockguard_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        lock_guard<mutex> lock(counter_mutex);
        shared_counter++;
        // lock_guard析构时自动unlock，异常安全
    }
}

// 4. 使用unique_lock（更灵活）
void uniquelock_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        unique_lock<mutex> lock(counter_mutex);
        shared_counter++;
        lock.unlock();  // 可以提前解锁
        
        // 做一些不需要锁的工作
        // ...
        
        lock.lock();  // 可以重新加锁
        shared_counter++;
    }
}

// 5. 死锁示例
mutex mutex1, mutex2;

void deadlock_thread1() {
    lock_guard<mutex> lock1(mutex1);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock2(mutex2);  // 等待mutex2...
    cout << "Thread1 获得两个锁" << endl;
}

void deadlock_thread2() {
    lock_guard<mutex> lock2(mutex2);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock1(mutex1);  // 等待mutex1... 死锁！
    cout << "Thread2 获得两个锁" << endl;
}

// 6. 避免死锁：使用std::lock
void safe_thread1() {
    lock(mutex1, mutex2);  // 原子性地获取两个锁
    lock_guard<mutex> lock1(mutex1, adopt_lock);
    lock_guard<mutex> lock2(mutex2, adopt_lock);
    cout << "Safe Thread1 获得两个锁" << endl;
}

void safe_thread2() {
    lock(mutex1, mutex2);
    lock_guard<mutex> lock1(mutex1, adopt_lock);
    lock_guard<mutex> lock2(mutex2, adopt_lock);
    cout << "Safe Thread2 获得两个锁" << endl;
}

// 7. 读写锁（C++17 shared_mutex）
shared_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    // 共享锁（多个读者可以同时持有）
    shared_lock<shared_mutex> lock(rw_mutex);
    cout << "Reader " << id << " 读取数据: " << shared_data << endl;
    this_thread::sleep_for(chrono::milliseconds(50));
}

void writer(int id, int value) {
    // 独占锁（只有一个写者）
    unique_lock<shared_mutex> lock(rw_mutex);
    shared_data = value;
    cout << "Writer " << id << " 写入数据: " << value << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}

// 8. scoped_lock（C++17，替代lock_guard）
void scoped_lock_demo() {
    cout << "\n=== scoped_lock示例 ===" << endl;
    
    // 可以同时锁定多个mutex
    scoped_lock lock(mutex1, mutex2);
    cout << "使用scoped_lock同时锁定两个mutex" << endl;
    // 自动按正确顺序解锁
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 互斥锁和锁管理" << endl;
    cout << "======================================" << endl;
    
    // 1. 竞态条件演示
    cout << "\n=== 竞态条件（不安全） ===" << endl;
    shared_counter = 0;
    vector<thread> unsafe_threads;
    for (int i = 0; i < 10; ++i) {
        unsafe_threads.emplace_back(unsafe_increment, 1000);
    }
    for (auto& t : unsafe_threads) {
        t.join();
    }
    cout << "不安全的计数器结果: " << shared_counter 
         << " (期望: 10000)" << endl;
    
    // 2. lock_guard安全计数
    cout << "\n=== lock_guard（安全） ===" << endl;
    shared_counter = 0;
    vector<thread> safe_threads;
    for (int i = 0; i < 10; ++i) {
        safe_threads.emplace_back(lockguard_increment, 1000);
    }
    for (auto& t : safe_threads) {
        t.join();
    }
    cout << "安全的计数器结果: " << shared_counter 
         << " (期望: 10000)" << endl;
    
    // 3. 避免死锁
    cout << "\n=== 避免死锁 ===" << endl;
    thread st1(safe_thread1);
    thread st2(safe_thread2);
    st1.join();
    st2.join();
    
    // 4. 读写锁
    cout << "\n=== 读写锁 ===" << endl;
    vector<thread> rw_threads;
    
    // 创建多个读者和写者
    for (int i = 0; i < 3; ++i) {
        rw_threads.emplace_back(reader, i);
    }
    rw_threads.emplace_back(writer, 1, 42);
    for (int i = 3; i < 6; ++i) {
        rw_threads.emplace_back(reader, i);
    }
    
    for (auto& t : rw_threads) {
        t.join();
    }
    
    // 5. scoped_lock
    scoped_lock_demo();
    
    cout << "\n======================================" << endl;
    cout << "  锁管理示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
