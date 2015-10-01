//
//  ThreadPool.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/4/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "ThreadPool.hpp"
#include "Thread.hpp"

ThreadPool::ThreadPool(int maxThread)
{
	_maxThread = maxThread;
	_running = false;
}

ThreadPool::~ThreadPool()
{}

void ThreadPool::init()
{
	_running = true;
	for (int i = 0; i < _maxThread; ++i) {
		Thread * trythread = new Thread();
		trythread->setDelegate(this);
		trythread->start();
		if (trythread->isRunning()) {
			_threads.push_back(trythread);
		}
		else{
			delete trythread;
			break;
		}
	}
}

void ThreadPool::release()
{
	_running = false;
	Task * deltask;
	Thread * delthread;

	while (!_threads.empty()) {
		delthread = _threads.back();
		_threads.pop_back();
		delthread->stop();
		delete delthread;
	}
	while (!_tasks.empty()) {
		deltask = _tasks.pop();
		delete deltask;
	}
}

void ThreadPool::addTask(Task * task)
{
	_tasks.push(task);
}

bool ThreadPool::isRunning() const
{
	return _running;
}

Task * ThreadPool::getTask()
{
	return _tasks.pop();
}