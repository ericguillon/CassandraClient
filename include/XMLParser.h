/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XMLParser.h
 * Author: eric
 *
 * Created on 22 mars 2016, 10:18
 */

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <rapidxml.hpp>
#include <boost/signals2.hpp>

class XMLParser {
public:
    XMLParser();
    XMLParser(const XMLParser& orig);
    ~XMLParser();
    void readFile(const char * filename);
    boost::signals2::signal<void (const rapidxml::xml_document<>&)> docCreated;
private:

};

#endif /* XMLPARSER_H */

