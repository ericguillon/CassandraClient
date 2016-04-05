/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SepaHeader.h
 * Author: eric
 *
 * Created on 24 mars 2016, 16:35
 */

#ifndef SEPAHEADER_H
#define SEPAHEADER_H

#include <string>
#include <boost/date_time/posix_time/ptime.hpp>

struct SepaHeader
{
    std::string messageId;
    std::string realMessageId;
    boost::posix_time::ptime creationDate;
    boost::posix_time::ptime settlementDate;
};

#endif /* SEPAHEADER_H */

