/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.cpp
 * Author: eric
 * 
 * Created on 22 mars 2016, 13:59
 */
#include <boost/algorithm/string/join.hpp>
#include "Logger.h"
#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}
    
void Client::setBalanceLimit(const Decimal& balance_limit)
{
    this->balance_limit = balance_limit;
}

const Decimal& Client::getBalanceLimit() const 
{
    return balance_limit;
}

void Client::setBalanceErp(const Decimal& balance_erp)
{
    this->balance_erp = balance_erp;
}

const Decimal& Client::getBalanceErp() const
{
    return balance_erp;
}

void Client::setBalance(const Decimal& balance)
{
    this->balance = balance;
}

const Decimal& Client::getBalance() const
{
    return balance;
}

const std::set<std::string>& Client::getSepaWhitelistCorrespondents() const
{
    return sepa_whitelist_correspondents;
}

void Client::setStatus(const std::string& status)
{
    this->status = status;
}

const std::string& Client::getStatus() const
{
    return status;
}

const std::string& Client::getIban() const
{
    return iban;
}

const std::string& Client::getRevisionId() const
{
    return revision_id;
}


bool Client::isCorrespondentAuthorized(const std::string& iban) const
{
    return sepa_whitelist_correspondents.find(iban) != sepa_whitelist_correspondents.end();
}

void Client::authorizedCorrespondentIban(const std::string& iban)
{
    correspondentsToAuthorize.insert(iban);
}

void Client::updateBalanceErp(const Decimal& decimal)
{
    balance_erp += decimal;
}

void Client::updateBalance(const Decimal& decimal)
{
    balance += decimal;
}

void Client::display() const
{
    BOOST_LOG_TRIVIAL(info) << "Iban " << iban;
    BOOST_LOG_TRIVIAL(info) << "Revision Id " << revision_id;
    BOOST_LOG_TRIVIAL(info) << "Status " << status;
    BOOST_LOG_TRIVIAL(info) << "Balance limit " << balance_limit.getValue();
    BOOST_LOG_TRIVIAL(info) << "Balance " << balance.getValue();
    BOOST_LOG_TRIVIAL(info) << "Balance erp " << balance_erp.getValue();
    BOOST_LOG_TRIVIAL(info) << "Whitelist correspondents " << boost::algorithm::join(sepa_whitelist_correspondents, ",");
}
