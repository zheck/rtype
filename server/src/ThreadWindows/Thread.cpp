#include "Thread.hpp"

Thread::Thread()
{
	_thread = NULL;
	_threadpool = NULL;
	_running = false;
	_threadId = 0;

}

Thread::~Thread()
{
	stop();
}

void Thread::stop()
{
	if (_thread != NULL) {
		_running = false;
		WaitForSingleObject(_thread, INFINITE);
		DWORD ExitCode;
		GetExitCodeThread(_thread, &ExitCode);
		CloseHandle(_thread);
		_thread = NULL;
	}
}

void Thread::start()
{
	_thread = (HANDLE)_beginthreadex(NULL, 0, &cThreadProc, (void*)this, 0, &_threadId);

	_running = true;
	if (_thread == NULL) {
		_running = false;
		// Exception
	}
}

void Thread::setDelegate(ThreadPool * delegate)
{
	_threadpool = delegate;
}

bool Thread::isRunning() const
{
	return _running;
}

DWORD Thread::executeThread()
{
	Task * task = NULL;

	while (_running) {
		Sleep(1);
		if (task != NULL) {
			_lock.lock();
			task->run();
			delete task;
			task = NULL;
			_lock.unLock();
		}
		if (task == NULL && _threadpool->isRunning() == true) {
			task = _threadpool->getTask();
		}
	}
	return 0;
}