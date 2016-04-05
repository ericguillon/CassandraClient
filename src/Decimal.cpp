/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Decimal.cpp
 * Author: eric
 * 
 * Created on 22 mars 2016, 13:45
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Decimal.h"

CassError cass_value_get(const CassValue* value, Decimal& decimal)
{
    return cass_value_get_decimal(value, decimal);
}

CassError cass_statement_bind(CassStatement* statement, std::size_t index, const Decimal& decimal)
{
    return cass_statement_bind_decimal(statement, index, decimal);
}

CassError cass_statement_bind_decimal(CassStatement* statement, std::size_t index, const Decimal& decimal)
{
    return cass_statement_bind_decimal(statement,
                                       index,
                                       decimal.getBytes(),
                                       decimal.getBytesSize(),
                                       decimal.decimalScale);
}

CassError cass_value_get_decimal(const CassValue* value, Decimal& decimal)
{
    const unsigned char * bytes;
    std::size_t bytesSize;
    int scale;
    CassError result = cass_value_get_decimal(value,
                                                &bytes,
                                                &bytesSize,
                                                &scale);
    if (result == CASS_OK)
    {
        if (bytesSize > Decimal::maxBytesSize - 1)
        {
            bytesSize = 0;
        }
        memcpy(decimal.bytes, bytes, bytesSize);
        decimal.bytesSize = bytesSize;
        decimal.decode();
    }
    return result;
}

Decimal::Decimal(double value)
{
    this->value = value;
    encode();
}

void Decimal::encode()
{
    int intValue = (value * 1000) / 10;
    bytesSize = snprintf((char*)bytes, maxBytesSize - 1, "%d", intValue); 
}

Decimal::Decimal(const Decimal& orig) {
}

Decimal::~Decimal() {
}

//Decimal& Decimal::operator = (const Decimal& other)
//{
//    bytesSize = other.bytesSize;
//    memcpy(bytes, other.bytes, other.bytesSize);
//    return *this;
//}

void Decimal::decode()
{
    bytes[bytesSize] = '\0';
    int intValue = atoi(reinterpret_cast<char*>(bytes));
    value = (double)intValue / 100;
}

Decimal& Decimal::operator += (const Decimal& other)
{
    value += other.value;
    encode();
}

Decimal& Decimal::operator -= (const Decimal& other)
{
    value -= other.value;
    encode();
}

bool Decimal::operator < (const Decimal& other)
{
    return value < other.value;
}

bool Decimal::operator > (const Decimal& other)
{
    return value > other.value;
}

Decimal operator * (const Decimal& lhs, int rhs)
{
    return Decimal(lhs.value * rhs);
}

Decimal operator + (const Decimal& lhs, const Decimal& rhs)
{
    Decimal decimal(lhs.value + rhs.value);
    return decimal;
}

Decimal operator - (const Decimal& lhs, const Decimal& rhs)
{
    Decimal decimal(lhs.value - rhs.value);
    return decimal;
}

std::ostream& operator << (std::ostream& out, const Decimal& rhs)
{
    return out << rhs.getValue();
}
