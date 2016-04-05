/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CassandraSession.cpp
 * Author: eric
 * 
 * Created on 22 mars 2016, 16:27
 */
#include <Logger.h>
#include "CassandraSession.h"

CassandraSession::CassandraSession():
connect_future(0)
{
    cluster = cass_cluster_new();
    session = cass_session_new();
}

CassandraSession::~CassandraSession()
{
    closeSession();
    disconnect();
}

bool CassandraSession::connect(const char * contactPoint)
{
    bool result = false;
    cass_cluster_set_contact_points(cluster, contactPoint);
    connect_future = cass_session_connect(session, cluster);
    if (cass_future_error_code(connect_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Cassandra " << contactPoint << " successfully connected";
        result = true;
    }
    else
    {
        const char* message;
        size_t message_length;
        cass_future_error_message(connect_future, &message, &message_length);
        BOOST_LOG_TRIVIAL(error) << "Unable to connect " << message;
    }
    return result;
}

void CassandraSession::closeSession()
{
    CassFuture* close_future = cass_session_close(session);
    cass_future_wait(close_future);
    cass_future_free(close_future);
}

void CassandraSession::disconnect()
{
    cass_future_free(connect_future);
    cass_session_free(session);
    cass_cluster_free(cluster);
    session = 0;
}
