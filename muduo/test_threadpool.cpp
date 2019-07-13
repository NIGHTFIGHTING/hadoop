// g++ test_threadpool.cpp  -std=c++11 -lpthread -o pool
//线程池存在意义和价值；
// (1)用于执行大量相对短暂的任务
// (2)该线程池的实现本质也是生产者与消费者模型的应用。生产者线程向任务队列中添加任务，一旦队列有任务到来，如果有等待线程就唤醒来执行任务
// (3)实现创建好一堆线程，避免动态创建线程来执行任务，提高了程序的稳定性；有效的规避程序运行之中创建线程有可能失败的风险；
// (4)提高程序运行效率：线程池中的线程，反复循环再利用；
#include <iostream>
#include <pthread.h>
#include <deque>
#include <vector>

struct Task;
typedef void* (*TASK_FUNC)(void* arg);
struct Task {
    TASK_FUNC task_func;
    void* arg;
};

class Condition;
class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&_mutex, nullptr);
    }
    ~Mutex() {
        pthread_mutex_destroy(&_mutex);
    }
    void lock() {
        pthread_mutex_lock(&_mutex);
    }
    void unlock() {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t* get_thread_mutex() {
        return &_mutex;
    }
private:
    pthread_mutex_t _mutex;
};

class Condition {
public:
    Condition(const Mutex& mutex):_mutex(mutex) {
        condition_init();
    }
    void condition_init() {
        pthread_cond_init(&_cond, nullptr);
    }
    void condition_lock() {
        _mutex.lock();
    }
    void condition_unlock() {
        _mutex.unlock();
    }
    void condition_wait() {
        pthread_cond_wait(&_cond, _mutex.get_thread_mutex());
    }
    void condition_signal() {
        pthread_cond_signal(&_cond);
    }
    void condition_broadcast() {
        pthread_cond_broadcast(&_cond);
    }
private:
    Mutex _mutex;
    pthread_cond_t _cond;
};
class ThreadPool;
struct ThreadItem {
    pthread_t handle;
    ThreadPool* thread_pool;
};
class ThreadPool {
public:
    explicit ThreadPool(int thread_size, int max_deque_size):
            _thread_size(thread_size), _max_deque_size(max_deque_size),
            _mutex(),_not_full(_mutex),_not_empty(_mutex),_running(false) {
    }
    void add_task(Task task) {
        _mutex.lock();
        while(_task_que.size() >= _max_deque_size && _running) {
            _not_full.condition_wait();
        }
        _task_que.push_back(task);
        _not_empty.condition_signal();
        _mutex.unlock();
    }
    void run() {
        _running = true;
        for (int i = 0; i < _thread_size; ++i) {
            //pthread_create(&tid, nullptr, run_in_thread, static_cast<void*>(this));
            ThreadItem* item = new ThreadItem;
            item->thread_pool = this;
            _thread_items.push_back(item);
            pthread_create(&item->handle, nullptr, run_in_thread, item);
        }
    }
    void* run_thread(void* arg) {
        std::cout << "asdadstest hahh" << std::endl;
        ThreadItem* item = static_cast<ThreadItem*>(arg);
        ThreadPool* thread_pool = item->thread_pool;
        std::deque<Task> task_que = thread_pool->_task_que;
        std::cout << "test hahh" << std::endl;
        while(_running) {
            _mutex.lock();
            while(task_que.empty() && thread_pool->_running) {
                _not_empty.condition_wait();
            }
            Task task = task_que.front();
            task_que.pop_front();
            _mutex.unlock();
            task.task_func(task.arg);
            _not_full.condition_signal();
        }
    }
    void is_full() {
    }
    void stop() {
        _running = false;
        _mutex.lock();
        _not_empty.condition_broadcast();
        _mutex.unlock();
        for (const auto& ite : _thread_items) {
            pthread_join(ite->handle, nullptr);
        }
        for (const auto& ite : _thread_items) {
            delete ite;
        }
    }
    static void* run_in_thread(void* arg) {
        std::cout << "asdadstest hahh" << std::endl;
    ThreadItem* item = static_cast<ThreadItem*>(arg);
    item->thread_pool->run_thread(arg);
    }
private:
    int _thread_size;
    int _max_deque_size;
    std::deque<Task> _task_que;
    Mutex _mutex;
    Condition _not_full;
    Condition _not_empty;
    bool _running;
    std::vector<ThreadItem*> _thread_items;
};

void* test_func(void* arg) {

}

int main() {
    ThreadPool thread_pool(10, 100);
    thread_pool.run();
}
