/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerManager.cpp
 * Author: eric
 * 
 * Created on 4 avril 2016, 10:20
 */
#include "boost/date_time/posix_time/posix_time.hpp"
#include "TimerManager.h"

TimerManager::TimerManager()
{
}

TimerManager::TimerManager(const TimerManager& orig)
{
}

TimerManager::~TimerManager()
{
}

void TimerManager::addTimer(void (*callback)(const boost::system::error_code&), int secondsToWait)
{
    boost::asio::deadline_timer t(ioService, boost::posix_time::seconds(secondsToWait));
    t.async_wait(callback);
}

