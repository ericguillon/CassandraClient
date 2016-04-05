/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlobalConfig.h
 * Author: eric
 *
 * Created on 1 avril 2016, 16:52
 */

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <set>
#include <string>
#include "Singleton.h"

class GlobalConfig: public Singleton<GlobalConfig>
{
public:
    bool isIbanBlacklisted(const std::string& iban) const
    {
        return isBlacklisted(iban, blacklistedIbans);
    }

    bool isBicBlacklisted(const std::string& bic) const
    {
        return isBlacklisted(bic, blacklistedBics);
    }

    bool isCountryBlacklisted(const std::string& country) const
    {
        return isBlacklisted(country, blacklistedCountries);
    }

protected:
    bool isBlacklisted(const std::string& value, const std::set<std::string>& container) const;

private:
    std::set<std::string> blacklistedIbans;
    std::set<std::string> blacklistedBics;
    std::set<std::string> blacklistedCountries;
};

#endif /* GLOBALCONFIG_H */

