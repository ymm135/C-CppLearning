#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 5: Future和Promise
// ===================================

// 1. 基本的future和promise
void basic_future_promise() {
    cout << "\n=== 基本Future/Promise ===" << endl;
    
    // promise用于设置值
    promise<int> prom;
    
    // future用于获取值
    future<int> fut = prom.get_future();
    
    // 在另一个线程中设置值
    thread t([](promise<int> p) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "设置promise值为42" << endl;
        p.set_value(42);  // 设置值
    }, move(prom));
    
    cout << "等待future结果..." << endl;
    int result = fut.get();  // 阻塞等待
    cout << "Future结果: " << result << endl;
    
    t.join();
}

// 2. promise传递异常
void promise_exception() {
    cout << "\n=== Promise异常传递 ===" << endl;
    
    promise<int> prom;
    future<int> fut = prom.get_future();
    
    thread t([](promise<int> p) {
        try {
            this_thread::sleep_for(chrono::milliseconds(300));
            throw runtime_error("计算错误！");
        } catch (...) {
            // 传递异常到future
            p.set_exception(current_exception());
        }
    }, move(prom));
    
    try {
        cout << "等待结果..." << endl;
        int result = fut.get();  // 会重新抛出异常
        cout << "结果: " << result << endl;
    } catch (const exception& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    t.join();
}

// 3. shared_future
void shared_future_demo() {
    cout << "\n=== shared_future ===" << endl;
    
    promise<int> prom;
    shared_future<int> sfut = prom.get_future();
    
    // 多个线程可以同时等待shared_future
    thread t1([sfut]() {
        cout << "线程1等待..." << endl;
        int result = sfut.get();
        cout << "线程1获得结果: " << result << endl;
    });
    
    thread t2([sfut]() {
        cout << "线程2等待..." << endl;
        int result = sfut.get();
        cout << "线程2获得结果: " << result << endl;
    });
    
    this_thread::sleep_for(chrono::milliseconds(500));
    prom.set_value(100);
    
    t1.join();
    t2.join();
}

// 4. packaged_task
void packaged_task_demo() {
    cout << "\n=== packaged_task ===" << endl;
    
    // 打包一个可调用对象
    packaged_task<int(int, int)> task([](int a, int b) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "计算 " << a << " + " << b << endl;
        return a + b;
    });
    
    // 获取future
    future<int> result = task.get_future();
    
    // 在线程中执行task
    thread t(move(task), 10, 20);
    
    cout << "等待计算结果..." << endl;
    cout << "结果: " << result.get() << endl;
    
    t.join();
}

// 5. async - 异步任务
int long_computation(int x) {
    cout << "开始长时间计算..." << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    return x * x;
}

void async_demo() {
    cout << "\n=== async异步任务 ===" << endl;
    
    // launch::async - 保证在新线程中执行
    future<int> fut1 = async(launch::async, long_computation, 10);
    
    // launch::deferred - 延迟执行，调用get时才执行
    future<int> fut2 = async(launch::deferred, long_computation, 20);
    
    cout << "主线程继续工作..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    
    cout << "获取async结果: " << fut1.get() << endl;
    cout << "获取deferred结果(此时才开始计算): " << fut2.get() << endl;
}

// 6. wait_for和wait_until
void wait_for_demo() {
    cout << "\n=== future超时等待 ===" << endl;
    
    future<int> fut = async(launch::async, []() {
        this_thread::sleep_for(chrono::milliseconds(2000));
        return 42;
    });
    
    cout << "等待结果（最多1秒）..." << endl;
    
    // wait_for: 等待一段时间
    future_status status = fut.wait_for(chrono::seconds(1));
    
    switch (status) {
        case future_status::timeout:
            cout << "超时！继续等待..." << endl;
            cout << "最终结果: " << fut.get() << endl;
            break;
        case future_status::ready:
            cout << "就绪！结果: " << fut.get() << endl;
            break;
        case future_status::deferred:
            cout << "延迟执行" << endl;
            break;
    }
}

// 7. 多个future组合
void multiple_futures() {
    cout << "\n=== 多个future ===" << endl;
    
    auto task1 = async(launch::async, []() {
        this_thread::sleep_for(chrono::milliseconds(300));
        return 10;
    });
    
    auto task2 = async(launch::async, []() {
        this_thread::sleep_for(chrono::milliseconds(500));
        return 20;
    });
    
    auto task3 = async(launch::async, []() {
        this_thread::sleep_for(chrono::milliseconds(200));
        return 30;
    });
    
    // 等待所有结果
    cout << "等待所有任务完成..." << endl;
    int sum = task1.get() + task2.get() + task3.get();
    cout << "总和: " << sum << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 Future和Promise" << endl;
    cout << "======================================" << endl;
    
    // 1. 基本用法
    basic_future_promise();
    
    // 2. 异常传递
    promise_exception();
    
    // 3. shared_future
    shared_future_demo();
    
    // 4. packaged_task
    packaged_task_demo();
    
    // 5. async
    async_demo();
    
    // 6. 超时等待
    wait_for_demo();
    
    // 7. 多个future
    multiple_futures();
    
    cout << "\n======================================" << endl;
    cout << "  Future/Promise示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
