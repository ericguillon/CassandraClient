/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OperationFactory.h
 * Author: eric
 *
 * Created on 22 mars 2016, 11:21
 */

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "Factory.h"

class Operation;
class OperationStatusFactory;

class OperationFactory : public Factory<Operation>
{
protected:
    OperationFactory(OperationStatusFactory* operationStatusFactory);

protected:
    OperationStatusFactory* operationStatusFactory;
};

#endif /* OPERATIONFACTORY_H */

