//
//  ThreadPool.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/4/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "ThreadPool.hpp"
#include "Exception.hpp"

ThreadPool::ThreadPool(int size) :
_poolSize(size)
{}

ThreadPool::~ThreadPool()
{}

void ThreadPool::init()
{
    _started = true;
    int ret;
    std::cout << "initializing threads" << std::endl;
    for (int i = 0; i < _poolSize; ++i) {
        pthread_t id;
        ret = pthread_create(&id, NULL, startThread, (void *)this);
        if (ret != 0) {
            throw Exception("Canoot create thread");
            release();
        }
        _threads.push_back(id);
    }
}

int ThreadPool::release()
{
    int ret;
    void * result;
    
    _mutex.lock();
    _started = false;
    _mutex.unlock();
    _condVar.broadcast();
    for (size_t i = 0; i < _threads.size(); ++i) {
        ret = pthread_join(_threads[i], &result);
        if (ret != 0) {
            std::cerr << "thread join failed" << std::endl;
        }
        _condVar.broadcast();
    }
    return 0;
}

void * ThreadPool::executeThread()
{
    Task * task;
    while (true) {
        _mutex.lock();
        while (_started != false && (_tasks.empty())) {
            _condVar.wait(_mutex.getMutex());
        }
        if (_started == false) {
            _mutex.unlock();
            pthread_exit(NULL);
        }
        task = _tasks.front();
        _tasks.pop_front();
        _mutex.unlock();
        (*task)();
    }
    return NULL;
}

void ThreadPool::addTask(Task *task)
{
    _mutex.lock();
    _tasks.push_back(task);
    _condVar.signal();
    _mutex.unlock();
}

void * startThread(void* arg)
{
    ThreadPool* tp = (ThreadPool*) arg;
    tp->executeThread();
    return NULL;
}

