/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeTraits.h
 * Author: eric
 *
 * Created on 4 avril 2016, 10:23
 */

#ifndef TYPETRAITS_H
#define TYPETRAITS_H

#include <iostream>

template <typename T>
struct CallTraits
{
    template <typename U, bool big> struct CallTraitsImpl;

    template <typename U>
    struct CallTraitsImpl<U, true>
    {
        typedef const U& Type;
    };

    template <typename U>
    struct CallTraitsImpl<U, false>
    {
        typedef U Type;
    };

    typedef typename CallTraitsImpl<T, (sizeof(T) > sizeof(void*))>::Type Type;
};

#endif /* TYPETRAITS_H */

