//
//  Task.hpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/7/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef SAFEQUEUE_HPP
# define SAFEQUEUE_HPP

# include "Lock.hpp"

template<typename TYPE>
class SafeQueue
{
private:
	struct tNode
	{
		TYPE element;
		tNode * next;
        
		tNode(TYPE _elem, tNode* _next) : element(_elem), next(_next)
		{}
		tNode(TYPE _elem) : element(_elem), next(NULL)
		{}
	};
    
	tNode* _head;
	tNode* _tail;
	Lock _hLock;
	Lock _tLock;
    
	SafeQueue(SafeQueue&)
	{}
    
	SafeQueue& operator = (SafeQueue&)
	{}
    
    
public:
	SafeQueue()
	{
		tNode * dummy = new tNode(NULL, NULL);
		_head = _tail = dummy;
	}
    
	~SafeQueue()
	{
		while (pop());
		delete _head;
	}
    
	bool empty()
	{
		if (_head->next != NULL)
			return false;
		return true;
	}
    
	void push(TYPE item)
	{
		tNode* node = new tNode(item);
		_tLock.lock();
		{
			_tail->next = node;
			_tail = node;
		}
		_tLock.unLock();
	}
    
	TYPE pop()
	{
		tNode* node;
		TYPE value;
		_hLock.lock();
		{
			node = _head;
			tNode* newHead = node->next;
			if (newHead == NULL) {
				_hLock.unLock();
				return NULL;
			}
			value = newHead->element;
			_head = newHead;
		}
		_hLock.unLock();
		delete node;
		return value;
	}
};

#endif /* !SAFQUEUE_HPP */