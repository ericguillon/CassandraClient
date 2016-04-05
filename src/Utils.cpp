/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.cpp
 * Author: eric
 * 
 * Created on 30 mars 2016, 10:26
 */
#include <cassandra.h>
#include "constants.h"
#include "Utils.h"

std::string Utils::getMonth(const boost::posix_time::ptime& posixDate)
{
    const boost::posix_time::ptime& currentDate = posixDate.is_not_a_date_time() ? boost::posix_time::second_clock::local_time() : posixDate;
    return boost::posix_time::to_iso_extended_string(currentDate).substr(0, Constants::MONTH_STRING_FORMAT_SIZE);
}

std::string Utils::getUUId()
{
    CassUuidGen* gen = cass_uuid_gen_new();
    CassUuid uuid;
    cass_uuid_gen_random(gen, &uuid);
    cass_uuid_gen_free(gen);
    char uuidString[MAX_UUID_STRING_LENGTH];
    cass_uuid_string(uuid, uuidString);
    return uuidString;
}
