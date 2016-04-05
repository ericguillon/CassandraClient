/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Decimal.h
 * Author: eric
 *
 * Created on 22 mars 2016, 13:45
 */

#ifndef DECIMAL_H
#define DECIMAL_H
#include <cmath>
#include <iostream>
#include <cassandra.h>

class Decimal
{
public:
    const static int maxBytesSize = 10;
    const static int decimalScale = 2;
    
    Decimal(double value = NAN);
    Decimal(const Decimal& orig);
    ~Decimal();
//    Decimal& operator = (const Decimal& other);

    std::size_t getBytesSize() const
    {
        return bytesSize;
    }
    
    const unsigned char* getBytes() const
    {
        return bytes;
    }

    bool isSet() const
    {
        return !std::isnan(value);
    }

    double getValue() const
    {
        return value;
    }
    
    void decode();
    
    
    Decimal& operator += (const Decimal& other);
    Decimal& operator -= (const Decimal& other);
    bool operator < (const Decimal& other);
    bool operator > (const Decimal& other);
    
    friend Decimal operator * (const Decimal& lhs, int rhs);
    friend Decimal operator + (const Decimal& lhs, const Decimal& rhs);
    friend Decimal operator - (const Decimal& lhs, const Decimal& rhs);
    friend CassError cass_value_get_decimal(const CassValue* value, Decimal& decimal);
    friend CassError cass_statement_bind_decimal(CassStatement* statement, std::size_t index, const Decimal& decimal);

private:
    void encode();

    unsigned char bytes[maxBytesSize];
    std::size_t bytesSize;
    double value;
};

CassError cass_value_get(const CassValue* value, Decimal& decimal);
CassError cass_statement_bind(CassStatement* statement, std::size_t index, const Decimal& decimal);
CassError cass_value_get_decimal(const CassValue* value, Decimal& decimal);
CassError cass_statement_bind_decimal(CassStatement* statement, std::size_t index, const Decimal& decimal);
std::ostream& operator << (std::ostream& out, const Decimal& rhs);

        
#endif /* DECIMAL_H */

