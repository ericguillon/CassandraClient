/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerManager.h
 * Author: eric
 *
 * Created on 4 avril 2016, 10:20
 */

#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H
#include <boost/asio.hpp>
#include "Singleton.h"

class TimerManager : public Singleton<TimerManager>
{
public:
    ~TimerManager();
    friend class Singleton<TimerManager>;
    void addTimer(void (*callback)(const boost::system::error_code&), int secondsToWait);
    
protected:
    boost::asio::io_service ioService;

private:
    TimerManager();
    TimerManager(const TimerManager& orig);
};

#endif /* TIMERMANAGER_H */

