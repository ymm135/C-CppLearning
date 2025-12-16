#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 6: 线程池实现
// ===================================

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        // 创建工作线程
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this, i]() {
                cout << "工作线程" << i << " 启动" << endl;
                while (true) {
                    function<void()> task;
                    
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        
                        // 等待任务或停止信号
                        this->condition.wait(lock, [this]() {
                            return this->stop || !this->tasks.empty();
                        });
                        
                        if (this->stop && this->tasks.empty()) {
                            cout << "工作线程" << i << " 退出" << endl;
                            return;
                        }
                        
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    
                    task();  // 执行任务
                }
            });
        }
    }
    
    // 添加任务到队列
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> future<typename result_of<F(Args...)>::type>
    {
        using return_type = typename result_of<F(Args...)>::type;
        
        // 创建packaged_task
        auto task = make_shared<packaged_task<return_type()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        
        future<return_type> res = task->get_future();
        
        {
            unique_lock<mutex> lock(queue_mutex);
            
            if (stop) {
                throw runtime_error("线程池已停止");
            }
            
            tasks.emplace([task]() { (*task)(); });
        }
        
        condition.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        
        condition.notify_all();
        
        for (thread& worker : workers) {
            worker.join();
        }
        
        cout << "线程池已关闭" << endl;
    }
    
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

// 测试函数
int compute_square(int x) {
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "计算 " << x << " 的平方" << endl;
    return x * x;
}

string process_string(const string& str) {
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "处理字符串: " << str << endl;
    return str + " (已处理)";
}

void simple_task(int id) {
    cout << "执行任务 " << id << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 线程池实现" << endl;
    cout << "======================================" << endl;
    
    // 创建包含4个线程的线程池
    ThreadPool pool(4);
    cout << "线程池已创建（4个工作线程）\n" << endl;
    
    // 1. 提交计算任务
    cout << "=== 提交计算任务 ===" << endl;
    vector<future<int>> results;
    
    for (int i = 1; i <= 8; ++i) {
        results.emplace_back(
            pool.enqueue(compute_square, i)
        );
    }
    
    // 获取结果
    cout << "\n计算结果:" << endl;
    for (size_t i = 0; i < results.size(); ++i) {
        cout << "  " << (i + 1) << "² = " << results[i].get() << endl;
    }
    
    // 2. 提交字符串处理任务
    cout << "\n=== 提交字符串任务 ===" << endl;
    vector<future<string>> string_results;
    
    string_results.emplace_back(pool.enqueue(process_string, "Hello"));
    string_results.emplace_back(pool.enqueue(process_string, "World"));
    string_results.emplace_back(pool.enqueue(process_string, "ThreadPool"));
    
    cout << "\n处理结果:" << endl;
    for (auto& result : string_results) {
        cout << "  " << result.get() << endl;
    }
    
    // 3. 提交无返回值任务
    cout << "\n=== 提交简单任务 ===" << endl;
    for (int i = 0; i < 5; ++i) {
        pool.enqueue(simple_task, i);
    }
    
    // 4. 使用Lambda
    cout << "\n=== Lambda任务 ===" << endl;
    auto lambda_future = pool.enqueue([](int x, int y) {
        this_thread::sleep_for(chrono::milliseconds(400));
        cout << "Lambda计算: " << x << " + " << y << endl;
        return x + y;
    }, 100, 200);
    
    cout << "Lambda结果: " << lambda_future.get() << endl;
    
    // 等待一段时间让任务完成
    this_thread::sleep_for(chrono::seconds(2));
    
    cout << "\n======================================" << endl;
    cout << "  线程池示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
