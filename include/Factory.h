/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Factory.h
 * Author: eric
 *
 * Created on 1 avril 2016, 15:41
 */

#ifndef FACTORY_H
#define FACTORY_H
#include <vector>
#include <boost/foreach.hpp>
#include <typeinfo>
#include <iostream>
#include "Client.h"
#include "Operation.h"

template <typename T>
class Factory
{
public:
    ~Factory()
    {
        BOOST_FOREACH(T* value, values)
        {
            delete value;
        }
        values.clear();
    }
    
    T* get()
    {
        T* value;
        if (values.empty())
        {
            value = new T();
        }
        else
        {
            value = values.back();
            values.pop_back();
        }
        return value;
    }
    
    void release(T* value)
    {
        values.push_back(value);
    }
    
protected:
    std::vector<T*> values;
};

#endif /* FACTORY_H */

