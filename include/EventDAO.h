/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   EventDAO.h
 * Author: eric
 *
 * Created on 30 mars 2016, 17:23
 */

#ifndef EVENTDAO_H
#define EVENTDAO_H
#include "BaseDAO.h"
#include "CassandraUtils.h"

class Event;
class BalanceEvent;
class StatusEvent;
class EventDAO : public BaseDAO,
                 public CassandraUtils
{
public:
    EventDAO();
    ~EventDAO();

    void insertEvent(StatusEvent* event);
    void insertBalanceEvent(BalanceEvent* event);
    void insertBalanceErpEvent(BalanceEvent* event);
private:
    void insertEvent(CassStatement* statement, BalanceEvent* event);
    void bindCommonParameters(CassStatement* statement, Event* event);
    void execute(CassStatement* statement, Event* event);
private:
    CassStatement* insertStatusEventStatement;
    CassStatement* insertBalanceEventStatement;
    CassStatement* insertBalanceErpEventStatement;
};

#endif /* EVENTDAO_H */

