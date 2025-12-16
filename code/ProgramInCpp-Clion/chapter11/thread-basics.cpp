#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 1: C++17 线程基础
// ===================================

// 1. 简单的线程函数
void simple_thread() {
    cout << "线程ID: " << this_thread::get_id() << " - 执行简单任务" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "简单任务完成" << endl;
}

// 2. 带参数的线程函数
void thread_with_params(int id, const string& message) {
    cout << "线程" << id << ": " << message << endl;
    this_thread::sleep_for(chrono::milliseconds(50));
}

// 3. 使用Lambda创建线程
void lambda_thread_demo() {
    cout << "\n=== Lambda线程示例 ===" << endl;
    
    int count = 0;
    thread t([&count]() {
        for (int i = 0; i < 5; ++i) {
            count++;
            cout << "Count: " << count << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });
    
    t.join();  // 等待线程完成
    cout << "最终count: " << count << endl;
}

// 4. 类成员函数作为线程
class Worker {
    int id;
public:
    Worker(int i) : id(i) {}
    
    void do_work() {
        cout << "Worker " << id << " 开始工作" << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "Worker " << id << " 完成工作" << endl;
    }
};

// 5. 多线程示例
void multiple_threads_demo() {
    cout << "\n=== 多线程示例 ===" << endl;
    
    vector<thread> threads;
    
    // 创建5个线程
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_with_params, i, "正在处理数据");
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "所有线程已完成" << endl;
}

// 6. detach vs join
void detach_vs_join() {
    cout << "\n=== detach vs join ===" << endl;
    
    // join: 等待线程完成
    thread t1([]() {
        cout << "t1: 运行并等待完成" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    });
    t1.join();  // 主线程等待t1完成
    cout << "t1已完成" << endl;
    
    // detach: 线程独立运行（危险！）
    thread t2([]() {
        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "t2: 独立运行（可能看不到输出）" << endl;
    });
    t2.detach();  // t2独立运行
    
    // 主线程不等待t2
    this_thread::sleep_for(chrono::milliseconds(100));
}

// 7. 获取硬件并发数
void hardware_concurrency_demo() {
    cout << "\n=== 硬件信息 ===" << endl;
    
    unsigned int cores = thread::hardware_concurrency();
    cout << "CPU核心数: " << cores << endl;
    cout << "建议线程数: " << cores << endl;
}

int main() {
#ifdef _WIN32
    // 设置控制台输出为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 线程基础示例" << endl;
    cout << "======================================" << endl;
    
    // 1. 简单线程
    cout << "\n=== 简单线程 ===" << endl;
    thread t1(simple_thread);
    t1.join();
    
    // 2. 带参数的线程
    cout << "\n=== 带参数的线程 ===" << endl;
    thread t2(thread_with_params, 1, "Hello from thread");
    t2.join();
    
    // 3. Lambda线程
    lambda_thread_demo();
    
    // 4. 类成员函数线程
    cout << "\n=== 类成员函数线程 ===" << endl;
    Worker w(42);
    thread t3(&Worker::do_work, &w);
    t3.join();
    
    // 5. 多线程
    multiple_threads_demo();
    
    // 6. detach vs join
    detach_vs_join();
    
    // 7. 硬件并发
    hardware_concurrency_demo();
    
    cout << "\n======================================" << endl;
    cout << "  所有示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
