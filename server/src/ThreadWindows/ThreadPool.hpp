//
//  ThreadPool.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/4/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__ThreadPool__
#define __R_TypeServer__ThreadPool__

#include <windows.h>
#include<iostream>
#include<queue>
#include<vector>

#include"Task.hpp"
#include "SafeQueue.hpp"

class Thread;

class ThreadPool
{
	std::vector<Thread *> _threads;
	SafeQueue<Task *> _tasks;
	volatile bool _running;
	int _maxThread;

public:
	ThreadPool(int maxThread);
	ThreadPool(const ThreadPool& rhs);
	~ThreadPool();

	ThreadPool& operator = (const ThreadPool& rhs);

	void init();
	void release();
	void addTask(Task * task);
	bool isRunning() const;
	Task * getTask();
};

#endif /* defined(__R_TypeServer__ThreadPool__) */
