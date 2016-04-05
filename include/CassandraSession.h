/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CassandraSession.h
 * Author: eric
 *
 * Created on 22 mars 2016, 16:27
 */

#ifndef CASSANDRASESSION_H
#define CASSANDRASESSION_H

#include "Singleton.h"
#include <cassandra.h>

class CassandraSession: public Singleton<CassandraSession>
{
public:
    ~CassandraSession();
    
    friend class Singleton<CassandraSession>;
    bool connect(const char * contactPoint);
    void disconnect();
    void closeSession();
    CassSession* getSession() const
    {
        return session;
    }
private:
    CassandraSession();
    CassandraSession(const CassandraSession& orig);

private:
    CassFuture* connect_future;
    CassSession* session;
    CassCluster* cluster;
    
};

#endif /* CASSANDRASESSION_H */

