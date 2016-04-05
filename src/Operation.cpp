/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operation.cpp
 * Author: eric
 * 
 * Created on 22 mars 2016, 11:06
 */
#include <string>
#include "OperationStatus.h"
#include "Operation.h"

Operation::Operation()
: rejet(0)
{
}

Operation::Operation(const Operation& orig) {
}

Operation::~Operation() {
}

Rejet* Operation::buildRejet(cassandra_exemple::RejectionCode rejectionCode, const std::string& cause, bool sabReject)
{
    
}

void Operation::setStatus(OperationStatus* status)
{
    status->setOperation(this);
    this->status = status;
}

const std::string& Operation::getTechnicalLabel() const
{
    if (technicalLabel.empty())
    {
        if (!realMessageId.empty() && !realTransactionId.empty())
        {
            technicalLabel = realMessageId + " | " + realTransactionId;
        }
        else
        {
            technicalLabel = messageId.empty() ? transactionId : messageId + " | " + transactionId;
        }
    }
    return technicalLabel;
}
    