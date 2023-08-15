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
    public:
        ~SingletonStack() {
            delete theStack;
        }

};

class MutexProtectedBoolean {
private:
    std::mutex mtx;
    bool value;

public:
    MutexProtectedBoolean() : value(false) {}

    void setTrue() {
        std::lock_guard<std::mutex> lock(mtx);
        value = true;
    }
    void setFalse() {
        std::lock_guard<std::mutex> lock(mtx);
        value = false;
    }

    bool getValue() {
        std::lock_guard<std::mutex> lock(mtx);
        return value;
    }
};

class SingletonBoolean {
    public:
        MutexProtectedBoolean *keepGoing;
        static SingletonBoolean& getInstance(){
            static SingletonBoolean instance;
            return instance;
        }
    private:
     SingletonBoolean() {
        keepGoing = new MutexProtectedBoolean();
    }
    public:
    ~SingletonBoolean() {
        delete keepGoing;
    }

};



#endif