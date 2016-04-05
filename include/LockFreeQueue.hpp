#ifndef LOCK_FREE_QUEUE_HPP
#define LOCK_FREE_QUEUE_HPP

#include <list>
#include <iostream>
#include <boost/interprocess/detail/atomic.hpp>


template <typename T>
class LockFreeQueue
{
    LockFreeQueue(const LockFreeQueue &);
    LockFreeQueue & operator = (const LockFreeQueue &);

    struct Node
    {
        Node(T _value):
        value(_value),
        next(0)
        {
        }

        T value;
        Node * next;
    };

    Node * freeStack;
    Node * first;
    Node * current;
    Node * last;

    boost::atomic<Node*> head;
    boost::atomic<Node*> divider;
    boost::atomic<Node*> tail;

    Node * get(T _value)
    {
        if (freeStack)
        {
            Node * next = freeStack;
            freeStack = next->next;
            next->value = _value;
            return next;
        }
        return new Node(_value);
    }

    void release(Node * _node)
    {
        _node->value = 0;
        _node->next = freeStack;
        freeStack = _node;
    }

public:
    LockFreeQueue()
    {
        freeStack = 0;
        first = current = last = get(0);
        head = divider = tail = 0;
    }

    ~LockFreeQueue()
    {
        Node * node;
        while (freeStack)
        {
            node = freeStack->next;
            delete freeStack;
            freeStack = node;
        }

//        while (first)
//        {
//            node = first->next;
//            delete first;
//            first = node;
//        }
    }

    bool push( T _t )
    {
        last->next = get(_t);                            
        last = last->next;
        tail = last;

        while( head != divider) 
        {
            Node * vTemp = first;
            first = first->next;
            head = first;
            release(vTemp);
        }
        return true;
    }

    bool pop( T & _result ) 
    {
        if( divider != tail ) 
        {      	
            _result = current->next->value;
            current = current->next;
            divider = current;
            return true;          	
        }
        return false;
    }
};

#endif


