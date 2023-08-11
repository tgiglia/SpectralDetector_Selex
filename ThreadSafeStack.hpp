#ifndef THREADSAFESTACK_HPP
#define THREADSAVESTACK_HPP 

#include <iostream>
#include <stack>
#include <mutex>
#include <thread>

template <typename T>
class ThreadSafeStack {
private:
    std::stack<T> data;
    std::mutex mutex;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex);
        data.push(value);
    }

    bool pop(T& value) {
        std::lock_guard<std::mutex> lock(mutex);
        if (data.empty()) {
            return false;
        }
        value = data.top();
        data.pop();
        return true;
    }

    bool empty()  {
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }
};

class SingletonStack {
    public:
        ThreadSafeStack<time_t> *theStack;
        static SingletonStack& getInstance() {
            static SingletonStack instance;
            return instance;
        }
    private:
        SingletonStack() {
            theStack = new ThreadSafeStack<time_t>();
        }
        ~SingletonStack() {
            delete theStack;
        }

};


#endif