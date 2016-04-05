/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlobalConfig.cpp
 * Author: eric
 * 
 * Created on 1 avril 2016, 16:52
 */

#include "GlobalConfig.h"

bool GlobalConfig::isBlacklisted(const std::string& value, const std::set<std::string>& container) const
{
    return container.find(value) != container.end();
}

