/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Singleton.h
 * Author: eric
 *
 * Created on 22 mars 2016, 16:14
 */

#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
    public:
        static T* getInstance()
        {
            if (!instance)
            {
                static T theInstance;
                instance = &theInstance;
            }
            return instance;
        }
        
        ~Singleton()
        {
            instance = 0;
        }
    protected:
        static T* instance;
};

template<typename T>
T* Singleton<T>::instance = 0;

#endif /* SINGLETON_H */

