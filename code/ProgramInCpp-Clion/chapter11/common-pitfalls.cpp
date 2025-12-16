#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <chrono>
#include <condition_variable>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 7: 并发编程常见陷阱
// ===================================

// 陷阱1: 数据竞争（Data Race）
int global_counter = 0;  // 多线程共享，无保护

void dangerous_increment() {
    for (int i = 0; i < 1000; ++i) {
        global_counter++;  // 数据竞争！
    }
}

void data_race_demo() {
    cout << "\n=== 陷阱1: 数据竞争 ===" << endl;
    global_counter = 0;
    
    vector<thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(dangerous_increment);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "结果: " << global_counter << " (期望: 10000)" << endl;
    cout << "❌ 数据竞争导致结果不正确！" << endl;
}

// 陷阱2: 死锁（Deadlock）
mutex m1, m2;

void deadlock_func1() {
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock2(m2);  // 等待m2...
}

void deadlock_func2() {
    lock_guard<mutex> lock2(m2);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lock1(m1);  // 等待m1... 死锁！
}

void deadlock_demo() {
    cout << "\n=== 陷阱2: 死锁 ===" << endl;
    cout << "说明: 两个线程互相等待对方的锁" << endl;
    cout << "解决方案: 使用 std::lock() 原子性获取多个锁" << endl;
}

// 陷阱3: 忘记join或detach
void forgot_join_demo() {
    cout << "\n=== 陷阱3: 忘记join/detach ===" << endl;
    
    // thread t([]() {
    //     this_thread::sleep_for(chrono::milliseconds(100));
    // });
    // // 忘记 t.join() 或 t.detach()
    // // 程序崩溃！std::terminate() 被调用
    
    cout << "❌ 线程对象销毁前必须join或detach" << endl;
}

// 陷阱4: 引用捕获的Lambda
void lambda_capture_demo() {
    cout << "\n=== 陷阱4: Lambda引用捕获陷阱 ===" << endl;
    
    int value = 10;
    
    thread t([&value]() {  // 危险！引用捕获
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "线程中的value: " << value << endl;
    });
    
    // value = 20;  // 主线程修改
    // value超出作用域后，线程访问悬空引用！
    
    t.join();
    
    cout << "⚠️ 引用捕获可能导致悬空引用" << endl;
    cout << "✅ 建议: 使用值捕获或确保生命周期" << endl;
}

// 陷阱5: 虚假唤醒（Spurious Wakeup）
mutex cv_mutex;
condition_variable cv;
bool ready = false;

void spurious_wakeup_bad() {
    unique_lock<mutex> lock(cv_mutex);
    cv.wait(lock);  // ❌ 没有谓词，可能虚假唤醒
    // 假设ready为true，但实际不一定！
}

void spurious_wakeup_good() {
    unique_lock<mutex> lock(cv_mutex);
    cv.wait(lock, []() { return ready; });  // ✅ 有谓词，防止虚假唤醒
}

void spurious_wakeup_demo() {
    cout << "\n=== 陷阱5: 虚假唤醒 ===" << endl;
    cout << "❌ cv.wait(lock) - 可能虚假唤醒" << endl;
    cout << "✅ cv.wait(lock, predicate) - 防止虚假唤醒" << endl;
}

// 陷阱6: 过度使用锁（Lock Contention）
mutex heavy_lock;
int shared_data = 0;

void heavy_lock_demo() {
    cout << "\n=== 陷阱6: 锁竞争 ===" << endl;
    
    vector<thread> threads;
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back([]() {
            for (int j = 0; j < 1000; ++j) {
                lock_guard<mutex> lock(heavy_lock);
                shared_data++;  // 锁粒度太大
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "使用锁耗时: " << duration.count() << "ms" << endl;
    cout << "⚠️ 锁竞争严重影响性能" << endl;
    cout << "✅ 解决: 减少锁粒度或使用atomic" << endl;
}

// 陷阱7: atomic的使用误区
atomic<int> a{0};
atomic<int> b{0};

void atomic_pitfall() {
    // ❌ 多个atomic操作不是原子的！
    if (a.load() == 0) {
        b.store(1);  // 其他线程可能在这之间修改a
    }
    
    // ✅ 如果需要组合操作，仍需要mutex
}

void atomic_pitfall_demo() {
    cout << "\n=== 陷阱7: atomic误区 ===" << endl;
    cout << "❌ 多个atomic操作不是原子的" << endl;
    cout << "if (a.load() == 0) { b.store(1); }" << endl;
    cout << "✅ 需要mutex保护组合操作" << endl;
}

// 陷阱8: shared_ptr的线程安全
void shared_ptr_demo() {
    cout << "\n=== 陷阱8: shared_ptr线程安全 ===" << endl;
    cout << "✅ 引用计数是线程安全的" << endl;
    cout << "❌ 指向的对象不是线程安全的" << endl;
    cout << "❌ 修改shared_ptr本身不是线程安全的" << endl;
    
    // shared_ptr<int> p = make_shared<int>(10);
    // thread t1([&p]() { p = make_shared<int>(20); });  // ❌ 竞态条件
    // thread t2([&p]() { p = make_shared<int>(30); });  // ❌ 竞态条件
}

// 陷阱9: 异常安全
mutex ex_mutex;

void exception_unsafe() {
    ex_mutex.lock();
    // 如果这里抛异常，unlock永远不会执行！
    // throw runtime_error("error");
    ex_mutex.unlock();
}

void exception_safe() {
    lock_guard<mutex> lock(ex_mutex);  // ✅ RAII，异常安全
    // 即使抛异常，lock_guard析构时也会unlock
}

void exception_demo() {
    cout << "\n=== 陷阱9: 异常安全 ===" << endl;
    cout << "❌ 手动lock/unlock - 异常不安全" << endl;
    cout << "✅ lock_guard/unique_lock - 异常安全" << endl;
}

// 陷阱10: detach后访问局部变量
void detach_pitfall_demo() {
    cout << "\n=== 陷阱10: detach陷阱 ===" << endl;
    
    // int local_var = 42;
    // thread t([&local_var]() {
    //     this_thread::sleep_for(chrono::seconds(1));
    //     cout << local_var << endl;  // 悬空引用！
    // });
    // t.detach();
    // // 函数结束，local_var销毁，线程访问无效内存
    
    cout << "❌ detach后线程仍在运行，但局部变量已销毁" << endl;
    cout << "✅ detach时避免捕获局部变量引用" << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 并发编程常见陷阱" << endl;
    cout << "======================================" << endl;
    
    data_race_demo();
    deadlock_demo();
    forgot_join_demo();
    lambda_capture_demo();
    spurious_wakeup_demo();
    heavy_lock_demo();
    atomic_pitfall_demo();
    shared_ptr_demo();
    exception_demo();
    detach_pitfall_demo();
    
    cout << "\n======================================" << endl;
    cout << "  总结：避免这些陷阱！" << endl;
    cout << "======================================" << endl;
    cout << "1. 永远保护共享数据" << endl;
    cout << "2. 按顺序获取多个锁" << endl;
    cout << "3. 线程必须join或detach" << endl;
    cout << "4. 小心Lambda的捕获" << endl;
    cout << "5. condition_variable使用谓词" << endl;
    cout << "6. 减少锁粒度" << endl;
    cout << "7. atomic不是万能的" << endl;
    cout << "8. shared_ptr需额外保护" << endl;
    cout << "9. 使用RAII管理资源" << endl;
    cout << "10. detach时小心生命周期" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
