/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OperationDAO.h
 * Author: eric
 *
 * Created on 29 mars 2016, 17:03
 */

#ifndef OPERATIONDAO_H
#define OPERATIONDAO_H
#include <cassandra.h>
#include "BaseDAO.h"
#include "CassandraUtils.h"

class Operation;
class OperationStatus;
class ReservedStatus;
class RejectedStatus;
class OnHoldStatus;
class ProvisionedStatus;
class CancelledStatus;
class AccountedStatus;
class OperationHandler;
class OperationFactory;
class OperationStatusFactory;

class OperationDAO: public BaseDAO,
                    public CassandraUtils
{
public:
    OperationDAO(OperationFactory* factory, OperationStatusFactory* statusFactory);
    ~OperationDAO();

    void getRejectedOperations(std::vector<Operation*>& operations);
    void getOperation(const std::string& month, const std::string& iban, std::vector<Operation*>& operations);
    void getOperation(const std::string& month, const std::string& iban, const std::string& transactionId, std::vector<Operation*>& operations);
    void getOperation(cassandra_exemple::OperationType type,
                      cassandra_exemple::OperationStatus status,
                      std::vector<Operation*>& operations);
    void getOperation(cassandra_exemple::OperationType type,
                      cassandra_exemple::OperationStatus status,
                      OperationHandler* operationHandler);

    void insertOperation(Operation* operation);
    void updateOperation(Operation* operation);

    bool isOperationInserted(Operation* operation);

    void updateOperationStatus(ReservedStatus* status);
    void updateOperationStatus(RejectedStatus* status);
    void updateOperationStatus(OnHoldStatus* status);
    void updateOperationStatus(ProvisionedStatus* status);
    void updateOperationStatus(AccountedStatus* status);
    void updateOperationStatus(CancelledStatus* status);

protected:
    CassStatement* insertOperationStatement;
    CassStatement* selectOperationStatement;
    CassStatement* selectOperationTypeStatusStatement;
    CassStatement* selectRejectedOperationStatement;
    CassStatement* rejectedOperationStatement;
    CassStatement* provisionedOperationStatement;
    CassStatement* accountedOperationStatement;
    OperationStatusFactory* statusFactory;
    OperationFactory* factory;
};

#endif /* OPERATIONDAO_H */

