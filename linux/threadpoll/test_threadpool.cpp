// g++ threadpoll.cpp -std=c++11 -lpthread -o pool
#include <iostream>
#include <pthread.h>
#include <deque>

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
private:
    Mutex _mutex;
    pthread_cond_t _cond;
};
void* run_in_thread(void* arg);
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
            pthread_t tid;
            //pthread_create(&tid, nullptr, run_in_thread, static_cast<void*>(this));
            pthread_create(&tid, nullptr, run_in_thread, this);
        }
    }
    void* run_thread(void* arg) {
        std::cout << "asdadstest hahh" << std::endl;
        pthread_detach(pthread_self());
        ThreadPool* thread_pool = static_cast<ThreadPool*>(arg);
        std::deque<Task> task_que = thread_pool->_task_que;
        std::cout << "test hahh" << std::endl;
        while(1) {
            _mutex.lock();
            while(task_que.empty() && thread_pool->_running) {
                _not_empty.condition_wait();
            }
            Task task = task_que.front();
            task_que.pop_front();
            task.task_func(task.arg);
            _not_full.condition_signal();
            _mutex.unlock();
        }
    }
    void is_full() {

    }
private:
    int _thread_size;
    int _max_deque_size;
    std::deque<Task> _task_que;
    Mutex _mutex;
    Condition _not_full;
    Condition _not_empty;
    bool _running;
};

void* run_in_thread(void* arg) {
        std::cout << "asdadstest hahh" << std::endl;
    ThreadPool* thread_pool = static_cast<ThreadPool*>(arg);
    thread_pool->run_thread(arg);
}

void* test_func(void* arg) {

}

int main() {
    ThreadPool thread_pool(10, 100);
    thread_pool.run();
}
