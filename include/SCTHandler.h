/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTHandler.h
 * Author: eric
 *
 * Created on 24 mars 2016, 16:13
 */

#ifndef SCTHANDLER_H
#define SCTHANDLER_H
#include <rapidxml.hpp>
#include "SepaHandler.h"

class SCTHandler: public SepaHandler
{
public:
    SCTHandler();
    ~SCTHandler();
    SCTHandler(const SCTHandler& orig);

    void operator()(const rapidxml::xml_document<>& document)
    {
        onDocCreated(document);
    }

    void onDocCreated(const rapidxml::xml_document<>& document);
    void processOnHoldOperations();
    void processRejectedOperations();
    void processProvisionedOperations();

    using SepaHandler::processRejectedOperations;
    using SepaHandler::processProvisionedOperations;
private:
    Operation* buildOperation(XmlNode* receivedTransferNode);
    void processOperation(Operation* operation);
private:
    
};

#endif /* SCTHANDLER_H */

