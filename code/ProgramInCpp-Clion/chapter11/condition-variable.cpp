#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ===================================
// Demo 3: 条件变量
// ===================================

// 1. 生产者-消费者模型
class ProducerConsumer {
    queue<int> buffer;
    mutex mtx;
    condition_variable cv;
    const size_t max_size = 10;
    bool done = false;
    
public:
    void producer(int id, int count) {
        for (int i = 0; i < count; ++i) {
            unique_lock<mutex> lock(mtx);
            
            // 等待缓冲区有空间
            cv.wait(lock, [this]() {
                return buffer.size() < max_size;
            });
            
            buffer.push(i);
            cout << "生产者" << id << " 生产: " << i 
                 << " (缓冲区大小: " << buffer.size() << ")" << endl;
            
            lock.unlock();
            cv.notify_all();  // 通知消费者
            
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        unique_lock<mutex> lock(mtx);
        done = true;
        cv.notify_all();
    }
    
    void consumer(int id) {
        while (true) {
            unique_lock<mutex> lock(mtx);
            
            // 等待有数据或生产完成
            cv.wait(lock, [this]() {
                return !buffer.empty() || done;
            });
            
            if (buffer.empty() && done) {
                break;
            }
            
            if (!buffer.empty()) {
                int value = buffer.front();
                buffer.pop();
                cout << "消费者" << id << " 消费: " << value
                     << " (缓冲区大小: " << buffer.size() << ")" << endl;
                
                lock.unlock();
                cv.notify_all();  // 通知生产者
                
                this_thread::sleep_for(chrono::milliseconds(150));
            }
        }
        
        cout << "消费者" << id << " 退出" << endl;
    }
};

// 2. 简单的等待/通知
mutex simple_mtx;
condition_variable simple_cv;
bool ready = false;

void waiter() {
    unique_lock<mutex> lock(simple_mtx);
    cout << "等待中..." << endl;
    
    // 等待条件满足
    simple_cv.wait(lock, []() { return ready; });
    
    cout << "条件满足，继续执行" << endl;
}

void notifier() {
    this_thread::sleep_for(chrono::milliseconds(500));
    
    {
        lock_guard<mutex> lock(simple_mtx);
       ready = true;
        cout << "设置条件为true" << endl;
    }
    
    simple_cv.notify_one();  // 通知一个等待的线程
}

// 3. 超时等待
void timeout_wait_demo() {
    cout << "\n=== 超时等待示例 ===" << endl;
    
    mutex mtx;
    condition_variable cv;
    bool data_ready = false;
    
    thread worker([&]() {
        unique_lock<mutex> lock(mtx);
        
        cout << "等待数据（最多2秒）..." << endl;
        
        // wait_for: 等待一段时间
        if (cv.wait_for(lock, chrono::seconds(2), 
            [&data_ready]() { return data_ready; })) {
            cout << "数据已就绪" << endl;
        } else {
            cout << "超时！数据未就绪" << endl;
        }
    });
    
    // 不发送通知，让其超时
    worker.join();
}

// 4. 多线程屏障（使用CV实现）
class Barrier {
    mutex mtx;
    condition_variable cv;
    size_t count;
    size_t waiting = 0;
    size_t generation = 0;
    
public:
    explicit Barrier(size_t cnt) : count(cnt) {}
    
    void wait() {
        unique_lock<mutex> lock(mtx);
        size_t gen = generation;
        
        if (++waiting == count) {
            // 最后一个到达
            generation++;
            waiting = 0;
            cv.notify_all();
        } else {
            // 等待其他线程
            cv.wait(lock, [this, gen]() {
                return gen != generation;
            });
        }
    }
};

void barrier_demo() {
    cout << "\n=== 屏障示例 ===" << endl;
    
    const int thread_count = 5;
    Barrier barrier(thread_count);
    
    vector<thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([i, &barrier]() {
            cout << "线程" << i << " 准备阶段..." << endl;
            this_thread::sleep_for(chrono::milliseconds(100 * (i + 1)));
            
            cout << "线程" << i << " 到达屏障" << endl;
            barrier.wait();  // 等待所有线程
            
            cout << "线程" << i << " 继续执行" << endl;
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "======================================" << endl;
    cout << "  C++17 条件变量" << endl;
    cout << "======================================" << endl;
    
    // 1. 生产者-消费者
    cout << "\n=== 生产者-消费者模型 ===" << endl;
    ProducerConsumer pc;
    
    thread producer1(&ProducerConsumer::producer, &pc, 1, 10);
    thread consumer1(&ProducerConsumer::consumer, &pc, 1);
    thread consumer2(&ProducerConsumer::consumer, &pc, 2);
    
    producer1.join();
    consumer1.join();
    consumer2.join();
    
    // 2. 简单等待/通知
    cout << "\n=== 简单等待/通知 ===" << endl;
    thread t1(waiter);
    thread t2(notifier);
    t1.join();
    t2.join();
    
    // 3. 超时等待
    timeout_wait_demo();
    
    // 4. 屏障
    barrier_demo();
    
    cout << "\n======================================" << endl;
    cout << "  条件变量示例完成" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
