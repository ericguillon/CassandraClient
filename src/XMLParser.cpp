/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XMLParser.cpp
 * Author: eric
 * 
 * Created on 22 mars 2016, 10:18
 */
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <istream>
#include <iostream>
#include "XMLParser.h"

XMLParser::XMLParser() {
}

XMLParser::XMLParser(const XMLParser& orig) {
}

XMLParser::~XMLParser() {
}

void XMLParser::readFile(const char * filename)
{
    boost::iostreams::stream<boost::iostreams::file_source> file(filename);
    std::string xmlFile;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("<?xml") != std::string::npos)
        {
            if (!xmlFile.empty())
            {
                rapidxml::xml_document<> doc;
                std::vector<char> xmlCopy(xmlFile.begin(), xmlFile.end());
                xmlCopy.push_back('\0');
                doc.parse<0>(&xmlCopy[0]);
                docCreated(doc);
                xmlFile.clear();
            }    
        }
        xmlFile += line;
    }

    if (!xmlFile.empty())
    {
        rapidxml::xml_document<> doc;
        std::vector<char> xmlCopy(xmlFile.begin(), xmlFile.end());
        xmlCopy.push_back('\0');
        doc.parse<0>(&xmlCopy[0]);
        docCreated(doc);
        xmlFile.clear();
    }
}
