//
//  Lock.hpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef LOCK_HPP_
# define LOCK_HPP_

# include <Windows.h>

class Lock
{
private:
	CRITICAL_SECTION _critsec;
    
public:
	Lock()
	{
		::InitializeCriticalSection(&_critsec);
	}
    
	~Lock()
	{
		::DeleteCriticalSection(&_critsec);
	}
    
	void lock()
	{
		::EnterCriticalSection(&_critsec);
	}
    
	void unLock()
	{
		::LeaveCriticalSection(&_critsec);
	}
};

#endif /* LOCK_HPP_ */