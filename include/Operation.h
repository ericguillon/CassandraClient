/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Operation.h
 * Author: eric
 *
 * Created on 22 mars 2016, 11:06
 */

#ifndef OPERATION_H
#define OPERATION_H
#include <boost/date_time/posix_time/ptime.hpp>
#include "Decimal.h"
#include "enums.h"

struct Compte
{
    std::string iban;
    std::string bic;
    std::string country;
};

struct Rejet
{
    cassandra_exemple::RejectionCode code;
    std::string cause;
    bool sabRejected;
};

class OperationStatus;

class Operation
{
public:
    Operation();
    Operation(const Operation& orig);
    ~Operation();

    Rejet* buildRejet(cassandra_exemple::RejectionCode rejectionCode, const std::string& cause, bool sabReject = false);
    const Decimal& getAmount() const
    {
        return amount;
    }

    const Decimal& getAuthorizedAmount() const
    {
        return authorizedAmount;
    }

    cassandra_exemple::OperationCanal getCanal() const
    {
        return canal;
    }

    Compte& getClientCompte()
    {
        return comptes[cassandra_exemple::CompteType::client];
    }

    const Compte& getClientCompte() const
    {
        return comptes[cassandra_exemple::CompteType::client];
    }

    Compte& getCorrespondentCompte()
    {
        return comptes[cassandra_exemple::CompteType::correspondent];
    }

    const Compte& getCorrespondentCompte() const
    {
        return comptes[cassandra_exemple::CompteType::correspondent];
    }

    cassandra_exemple::OperationDirection getDirection() const
    {
        return direction;
    }

    const Decimal& getFee() const
    {
        return fee;
    }

    const std::string& getId() const
    {
        return id;
    }

    const boost::posix_time::ptime& getInsertionDate() const
    {
        return insertionDate;
    }

    const Decimal& getLocalAmount() const
    {
        return localAmount;
    }

    const std::string& getMessageId() const
    {
        return messageId;
    }

    const std::string& getRealMessageId() const
    {
        return realMessageId;
    }

    const std::string& getRealTransactionId() const
    {
        return realTransactionId;
    }

    const boost::posix_time::ptime& getSettlementDate() const
    {
        return settlementDate;
    }

//    cassandra_exemple::OperationStatus getStatus() const
//    {
//        return status;
//    }

    cassandra_exemple::OperationSubCanal getSubCanal() const
    {
        return subCanal;
    }

    const std::string& getTechnicalLabel() const;

    const std::string& getTransactionId() const
    {
        return transactionId;
    }

    cassandra_exemple::OperationType getType() const
    {
        return type;
    }

    void setAmount(const Decimal& amount)
    {
        this->amount = amount;
    }

    void setAuthorizedAmount(const Decimal& authorizedAmount)
    {
        this->authorizedAmount = authorizedAmount;
    }

    void setCanal(cassandra_exemple::OperationCanal canal)
    {
        this->canal = canal;
    }

    void setDirection(cassandra_exemple::OperationDirection direction)
    {
        this->direction = direction;
    }

    void setFee(const Decimal& fee)
    {
        this->fee = fee;
    }

    void setId(const std::string& id)
    {
        this->id = id;
    }

    void setInsertionDate(const boost::posix_time::ptime& insertionDate)
    {
        this->insertionDate = insertionDate;
    }

    void setLocalAmount(const Decimal& localAmount)
    {
        this->localAmount = localAmount;
    }

    void setMessageId(const std::string& messageId)
    {
        this->messageId = messageId;
    }

    void setRealMessageId(const std::string& realMessageId)
    {
        this->realMessageId = realMessageId;
    }

    void setRealTransactionId(const std::string& realTransactionId)
    {
        this->realTransactionId = realTransactionId;
    }

    void setSettlementDate(const boost::posix_time::ptime& settlementDate)
    {
        this->settlementDate = settlementDate;
    }

//    void setStatus(cassandra_exemple::OperationStatus status)
//    {
//        this->status = status;
//    }

    void setSubCanal(cassandra_exemple::OperationSubCanal subCanal)
    {
        this->subCanal = subCanal;
    }

    void setTransactionId(const std::string& transactionId)
    {
        this->transactionId = transactionId;
    }

    void setType(cassandra_exemple::OperationType type)
    {
        this->type = type;
    }

    Rejet* getRejet() const
    {
        return rejet;
    }

    OperationStatus* getStatus() const
    {
        return status;
    }

    void setStatus(OperationStatus* status);
    friend class OperationDAO;
    friend class CassandraOperationFactory;
private:
    Decimal amount;
    Decimal localAmount;
    Decimal fee;
    Decimal authorizedAmount;

    std::string id;
    std::string transactionId;
    std::string messageId;
    std::string realMessageId;
    std::string realTransactionId;
    mutable std::string technicalLabel;

    cassandra_exemple::OperationCanal canal;
    cassandra_exemple::OperationSubCanal subCanal;
    cassandra_exemple::OperationType type;
//    cassandra_exemple::OperationStatus status;
    cassandra_exemple::OperationDirection direction;

    boost::posix_time::ptime insertionDate;
    boost::posix_time::ptime settlementDate;
    Compte comptes[cassandra_exemple::CompteType::end];
    Rejet* rejet;
    OperationStatus* status;
};

#endif /* OPERATION_H */

