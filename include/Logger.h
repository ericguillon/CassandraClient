/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.h
 * Author: eric
 *
 * Created on 21 mars 2016, 15:24
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "Singleton.h"

class Logger: public Singleton<Logger>
{
public:
    ~Logger();
    
    void init();
    template <typename... Arguments>
    void trace_info(const Arguments&... params);

    friend class Singleton<Logger>;
private:
    Logger();
    Logger(const Logger& orig);
};

#endif /* LOGGER_H */

