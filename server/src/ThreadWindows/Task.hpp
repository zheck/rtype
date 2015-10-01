//
//  Task.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Task__
#define __R_TypeServer__Task__

typedef void(*taskFunc)(void *);

class Task
{
private:
	taskFunc _task;
	void * _data;

public:
	Task(taskFunc task, void * data)
	{
		_task = task;
		_data = data;
	}

	~Task()
	{
		_data = NULL;
		_task = NULL;
	}

	void run() {
		_task(_data);
	}
};

#endif /* defined(__R_TypeServer__Task__) */
