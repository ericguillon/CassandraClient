/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.h
 * Author: eric
 *
 * Created on 30 mars 2016, 17:23
 */

#ifndef EVENT_H
#define EVENT_H
#include <boost/date_time/posix_time/posix_time.hpp>
#include "enums.h"
#include "Decimal.h"
#include "Operation.h"
#include "OperationStatus.h"

class Event
{
public:
    Event();
    ~Event();
    
    const boost::posix_time::ptime& getCreationDate() const
    {
        return creationDate;
    }

    void setCreationDate(const boost::posix_time::ptime& creationDate)
    {
        this->creationDate = creationDate;
    }

    const std::string& getDescription() const
    {
        return description;
    }

    void setDescription(const std::string& description)
    {
        this->description = description;
    }

    const std::string& getId() const
    {
        return id;
    }

    void setId(const std::string& id)
    {
        this->id = id;
    }

    cassandra_exemple::EventType getType() const
    {
        return type;
    }

    void setType(cassandra_exemple::EventType type)
    {
        this->type = type;
    }

    void setOperation(Operation* operation)
    {
        this->operation = operation;
    }

    const std::string& getIban() const;
    const std::string& getOperationId() const;
    const std::string& getTechnicalLabel() const;
    cassandra_exemple::OperationCanal getOperationCanal() const;
    cassandra_exemple::OperationSubCanal getOperationSubCanal() const;
    cassandra_exemple::OperationType getOperationType() const;

protected:
    std::string id;
    std::string description;
    cassandra_exemple::EventType type;
    boost::posix_time::ptime creationDate;
    Operation* operation;
};

class StatusEvent: public Event
{
public:
    StatusEvent()
    : oldStatus(cassandra_exemple::undefined)
    {
    }
    
    cassandra_exemple::OperationStatus getNewStatus() const;

    cassandra_exemple::OperationStatus getOldStatus() const
    {
        return oldStatus;
    }

    void setOldStatus(cassandra_exemple::OperationStatus oldStatus)
    {
        this->oldStatus = oldStatus;
    }
    
private:
    cassandra_exemple::OperationStatus oldStatus;
};

class BalanceEvent: public Event
{
public:
    const Decimal& getBalanceImpact() const
    {
        return balanceImpact;
    }

    void setBalanceImpact(const Decimal& balanceImpact)
    {
        this->balanceImpact = balanceImpact;
    }

    const Decimal& getNewBalance() const
    {
        return newBalance;
    }

    void setNewBalance(const Decimal& newBalance)
    {
        this->newBalance = newBalance;
    }

    const Decimal& getOldBalance() const
    {
        return oldBalance;
    }

    void setOldBalance(const Decimal& oldBalance)
    {
        this->oldBalance = oldBalance;
    }

private:
    Decimal balanceImpact;
    Decimal oldBalance;
    Decimal newBalance;
};
#endif /* EVENT_H */

