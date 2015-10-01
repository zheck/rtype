#ifndef THREAD_HPP_
# define THREAD_HPP_

# include <windows.h>
# include<process.h>

# include<iostream>

# include "ThreadPool.hpp"
# include "Task.hpp"
# include "Lock.hpp"

class Thread
{
	ThreadPool * _threadpool;
	HANDLE _thread;
	bool _running;
	unsigned int _threadId;
	Lock _lock;

public:
	Thread();
	Thread(Thread const & rhs);
	~Thread();

	Thread & operator=(Thread const & rhs);

	void setDelegate(ThreadPool * delegate);
	void start();
	DWORD executeThread();
	void stop();
	bool isRunning() const;

protected:
	static unsigned __stdcall cThreadProc(LPVOID _pThis)
	{
		return ((Thread*)_pThis)->executeThread();
	}
};

#endif /* THREAD_HPP */