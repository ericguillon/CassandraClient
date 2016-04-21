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
#include <boost/shared_ptr.hpp>
#include "SepaHandler.h"
#include "ClientDAO.h"

class CommandFactory;
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
    void createClient(const std::string& iban);
    using SepaHandler::processRejectedOperations;
    using SepaHandler::processProvisionedOperations;

protected:
    boost::shared_ptr<CommandFactory> factory;
    ClientDAO clientDAO;
};

#endif /* SCTHANDLER_H */

