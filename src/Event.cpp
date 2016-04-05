/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.cpp
 * Author: eric
 * 
 * Created on 30 mars 2016, 17:23
 */
#include "Operation.h"
#include "Event.h"

Event::Event()
: operation(0)
{
}

Event::~Event()
{
}

const std::string& Event::getIban() const
{
    return operation->getClientCompte().iban;
}

const std::string& Event::getOperationId() const
{
    return operation->getId();
}

const std::string& Event::getTechnicalLabel() const
{
    return operation->getTechnicalLabel();
}

cassandra_exemple::OperationSubCanal Event::getOperationSubCanal() const
{
    return operation->getSubCanal();
}

cassandra_exemple::OperationType Event::getOperationType() const
{
    return operation->getType();
}

cassandra_exemple::OperationCanal Event::getOperationCanal() const
{
    return operation->getCanal();
}

cassandra_exemple::OperationStatus StatusEvent::getNewStatus() const
{
    return (operation ? operation->getStatus()->getStatus() : oldStatus);
}
