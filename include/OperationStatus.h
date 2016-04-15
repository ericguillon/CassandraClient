/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OperationStatus.h
 * Author: eric
 *
 * Created on 31 mars 2016, 10:35
 */

#ifndef OPERATIONSTATUS_H
#define OPERATIONSTATUS_H
#include <string>
#include "OperationDAO.h"
#include "OperationStatusFactory.h"

class Operation;

class OperationStatus
{
public:
    virtual ~OperationStatus(){}
    virtual void update(OperationDAO* operationDAO) = 0;
    virtual void initialize(OperationStatusFactory* factory, const CassRow* row) = 0;

    OperationStatus()
    : operation(0)
    {}

    Operation* getOperation() const
    {
        return operation;
    }

    void setOperation(Operation* operation)
    {
        this->operation = operation;
    }

    cassandra_exemple::OperationStatus getStatus() const
    {
        return status;
    }
protected:
    Operation* operation;
    cassandra_exemple::OperationStatus status;
};

template <typename T>
class BaseOperationStatus: public OperationStatus
{
public:
    void update(OperationDAO* operationDAO)
    {
        operationDAO->updateOperationStatus(static_cast<T*>(this));
    }

    void initialize(OperationStatusFactory* factory, const CassRow* row)
    {
        factory->initializeOperationStatus(static_cast<T*>(this), row);
    }
};

class ReservedStatus : public BaseOperationStatus<ReservedStatus>
{
public:
    ReservedStatus()
    {
        status = cassandra_exemple::reserved;
    }
};

class RejectedStatus : public BaseOperationStatus<RejectedStatus>
{
public:
    RejectedStatus()
    : sabRejected(false)
    , fpeRejected(false)
    , notifySab(false)
    {
        status = cassandra_exemple::rejected;
    }

    const std::string& getCause() const
    {
        return cause;
    }

    void setCause(const std::string& cause)
    {
        this->cause = cause;
    }

    cassandra_exemple::RejectionCode getCode() const
    {
        return code;
    }

    void setCode(cassandra_exemple::RejectionCode code)
    {
        this->code = code;
    }

    bool isFpeRejected() const
    {
        return fpeRejected;
    }

    void setFpeRejected(bool fpeRejected)
    {
        this->fpeRejected = fpeRejected;
    }

    bool isNotifySab() const
    {
        return notifySab;
    }

    void setNotifySab(bool notifySab)
    {
        this->notifySab = notifySab;
    }

    bool isSabRejected() const
    {
        return sabRejected;
    }

    void setSabRejected(bool sabRejected)
    {
        this->sabRejected = sabRejected;
    }
    friend class OperationDAO;
    friend class OperationStatusFactory;

private:
    bool sabRejected;
    bool fpeRejected;
    bool notifySab;
    cassandra_exemple::RejectionCode code;
    std::string cause;
};

class OnHoldStatus: public BaseOperationStatus<OnHoldStatus>
{
public:
    OnHoldStatus()
    {

    }
};

class ProvisionedStatus: public BaseOperationStatus<ProvisionedStatus>
{
public:
    ProvisionedStatus()
    {
        status = cassandra_exemple::provisioned;
    }
};

class AccountedStatus : public BaseOperationStatus<AccountedStatus>
{
public:
    AccountedStatus()
    {
        status = cassandra_exemple::accounted;
    }
};

class CancelledStatus : public BaseOperationStatus<CancelledStatus>
{
public:
    CancelledStatus()
    {
        status = cassandra_exemple::cancelled;
    }
};

#endif /* OPERATIONSTATUS_H */

