/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: eric
 *
 * Created on 30 mars 2016, 10:26
 */

#ifndef UTILS_H
#define UTILS_H
#include <boost/date_time/posix_time/posix_time.hpp>

class Utils
{
    static const int MAX_UUID_STRING_LENGTH = 100;
public:
    static std::string getMonth(const boost::posix_time::ptime& posixDate);
    static std::string getUUId();
private:

};

#endif /* UTILS_H */

