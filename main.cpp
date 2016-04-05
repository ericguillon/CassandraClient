/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: eric
 *
 * Created on 21 mars 2016, 10:30
 */

#include <iostream>
#include <cstdlib>
#include <cassandra.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/atomic.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid//uuid_io.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Logger.h"
#include "Decimal.h"
#include "Client.h"
#include "ClientDAO.h"
#include "CassandraSession.h"
#include "XMLParser.h"
#include "OperationStatus.h"
#include "SCTHandler.h"
#include "LockFreeQueue.hpp"

int producer_count(0);
int consumer_count(0);

const int nb_iterations = 50000000;

template <typename T>
class MessageQueue
{
public:
    bool push(const T& value)
    {
        boost::mutex::scoped_lock slock(lock);
        container.push_back(value);
        return true;
    }
    
    bool pop(T& value)
    {
        boost::mutex::scoped_lock slock(lock);
        bool result = !container.empty();
        if (result)
        {
            value = container.front();
            container.pop_front();
        }
        return result;
    }
private:
    std::deque<T> container;
    boost::mutex lock;
    
};


boost::atomic<bool> done(false);
boost::lockfree::spsc_queue<int, boost::lockfree::capacity<1024> > queue;

//MessageQueue<int> queue;
//LockFreeQueue<int> queue;

void consumer()
{
    int value;
    while (!done)
    {
        while (queue.pop(value))
        {
            ++consumer_count;
        }
    }
    while (queue.pop(value))
    {
        ++consumer_count;
    }
}

void producer()
{
    for (int i = 0; i < nb_iterations; ++i)
    {
        int value = ++producer_count;
        while (!queue.push(value))
        {
        }
    }
}
/*
 * 
 */
int main(int argc, char** argv) 
{
    Logger * logger = Logger::getInstance();
    logger->init();
    
    BOOST_LOG_TRIVIAL(info) << "Info Log";
    
    std::cout << "Hello world!" << std::endl;
    const char* contact_point = "127.0.0.1";
    
//    CassFuture* connect_future = NULL;
//    CassCluster* cluster = cass_cluster_new();
//    CassSession* session = cass_session_new();
//    
//    cass_cluster_set_contact_points(cluster, contact_point);
//    
//    connect_future = cass_session_connect(session, cluster);
//    
//    if (cass_future_error_code(connect_future) == CASS_OK)
//    {
//        std::cout << "Cassandra successfully connected.." << std::endl;
//        const char * client_iban = "FR7616598000010035896000105";
//        CassFuture* close_future = NULL;
//        CassStatement* statement = cass_statement_new("SELECT * FROM fpe.clients WHERE iban=?", 1);
//        cass_statement_bind_string(statement, 0, "FR7616598000010035896000105");
//        
//        CassFuture* result_future = cass_session_execute(session, statement);
//        if (cass_future_error_code(result_future) == CASS_OK)
//        {
//            const CassResult* result = cass_future_get_result(result_future);
//            const CassRow* row = cass_result_first_row(result);
//            const CassValue* balance_value = cass_row_get_column_by_name(row, "balance");
//            const CassValue* balance_erp_value = cass_row_get_column_by_name(row, "balance_erp");
//            const CassValue* status_value = cass_row_get_column_by_name(row, "status");
//            
//            const char* status;
//            size_t status_length;
//            cass_value_get_string(status_value, &status, &status_length);
//            
//            const cass_byte_t* balance;
//            const cass_byte_t* balance_erp;
//            size_t balance_size, balance_erp_size;
//            cass_int32_t balance_scale, balance_erp_scale;
//            
//            cass_value_get_decimal(balance_value, &balance, &balance_size, &balance_scale);
//            cass_value_get_decimal(balance_erp_value, &balance_erp, &balance_erp_size, &balance_erp_scale);
//            
//            std::cout << "Client " << client_iban << " status " << std::string(status, status_length) 
//                 << " balance " << std::string((const char*)balance, balance_size)
//                 << " balance erp " << std::string((const char*)balance_erp, balance_erp_size) << std::endl;
//            
//            cass_result_free(result);
//        }
//        else
//        {
//            const char* message;
//            size_t message_length;
//            cass_future_error_message(result_future, &message, &message_length);
//            std::cerr << "Unable to run query " << message << std::endl;
//        }
// 
//        cass_future_free(result_future);
//        
//        const char * new_client_iban = "FR76165980000100358960008898";
//        CassStatement* insert_statement = cass_statement_new("INSERT INTO fpe.clients (iban, revision_id, balance, balance_erp, status) values (?,?,?,?,?);", 5);
//        cass_statement_bind_string(insert_statement, 0, new_client_iban);
//        boost::uuids::uuid tag = boost::uuids::random_generator()();
//        std::string revision_id = boost::lexical_cast<std::string>(tag);
//
//        CassUuidGen* gen = cass_uuid_gen_new();
//        CassUuid uuid;
//        cass_uuid_gen_random(gen, &uuid);
//        cass_uuid_gen_free(gen);
//        
//        cass_statement_bind_string(insert_statement, 1, revision_id.c_str());
//        cass_int32_t decimal_scale = 5;
//        cass_byte_t client_balance[] = "1245";
//        cass_byte_t client_balance_erp[] = "7575";
//        size_t client_balance_length = 4;
//        size_t client_balance_erp_length = 4;
//        
//        cass_statement_bind_decimal(insert_statement, 2, client_balance, client_balance_length, decimal_scale);
//        cass_statement_bind_decimal(insert_statement, 3, client_balance_erp, client_balance_erp_length, decimal_scale);
//        
//        cass_statement_bind_string(insert_statement, 4, "compte_ouvert");
//        cass_session_execute(session, insert_statement);
//        cass_statement_free(insert_statement);
//        
//        cass_statement_bind_string(statement, 0, new_client_iban);
//        
//        result_future = cass_session_execute(session, statement);
//        if (cass_future_error_code(result_future) == CASS_OK)
//        {
//            const CassResult* result = cass_future_get_result(result_future);
//            const CassRow* row = cass_result_first_row(result);
//            const CassValue* balance_value = cass_row_get_column_by_name(row, "balance");
//            const CassValue* balance_erp_value = cass_row_get_column_by_name(row, "balance_erp");
//            const CassValue* status_value = cass_row_get_column_by_name(row, "status");
//            
//            const char* status;
//            size_t status_length;
//            cass_value_get_string(status_value, &status, &status_length);
//            
//            const cass_byte_t* balance;
//            const cass_byte_t* balance_erp;
//            size_t balance_size, balance_erp_size;
//            cass_int32_t balance_scale, balance_erp_scale;
//            
//            cass_value_get_decimal(balance_value, &balance, &balance_size, &balance_scale);
//            cass_value_get_decimal(balance_erp_value, &balance_erp, &balance_erp_size, &balance_erp_scale);
//            
//            std::cout << "Client " << client_iban << " status " << std::string(status, status_length) 
//                 << " balance " << std::string((const char*)balance, balance_size)
//                 << " balance erp " << std::string((const char*)balance_erp, balance_erp_size) << std::endl;
//            
//            cass_result_free(result);
//        }
//        else
//        {
//            const char* message;
//            size_t message_length;
//            cass_future_error_message(result_future, &message, &message_length);
//            std::cerr << "Unable to run query " << message << std::endl;
//        }
//        
//        cass_statement_free(statement);
//        cass_future_free(result_future);
//        
//        //cass_statement_bind_string(insert_statement, 1, boost::lexical_cast<std::std::string>(tag).c_str());
//        close_future = cass_session_close(session);
//        cass_future_wait(close_future);
//        cass_future_free(close_future);
//    }
//    else
//    {
//        const char* message;
//        size_t message_length;
//        cass_future_error_message(connect_future, &message, &message_length);
//        std::cerr << "Unable to connect " << message << std::endl;
//    }
//    
//    cass_future_free(connect_future);
//    cass_cluster_free(cluster);
//    cass_session_free(session);
    
    CassandraSession* cassandraSession = CassandraSession::getInstance();
    cassandraSession->connect(contact_point);
    
    const char* new_client_iban = "FR76165980000100358960008898";
    ClientDAO clientDAO;
    BOOST_LOG_TRIVIAL(info) << "Getting client " << new_client_iban;
    if (Client* client = clientDAO.getClient(new_client_iban))
    {
        client->display();
        client->authorizedCorrespondentIban("FR76165980000100358960008898");
        clientDAO.updateClientCorrespondentWhitelist(client);
        client->authorizedCorrespondentIban("FR76165980000100358960008899");
        client->authorizedCorrespondentIban("FR76165980000100358960008999");
        client->authorizedCorrespondentIban("FR76165980000100358960009899");
        clientDAO.updateClientCorrespondentWhitelist(client);
        
        client->updateBalance(75.15);
        clientDAO.updateClientBalance(client);
        
        client->display();
        clientDAO.release(client);
    }
    
    if (Client* client2 = clientDAO.getClient(new_client_iban))
    {
        client2->display();
        clientDAO.release(client2);
    }

    boost::posix_time::ptime startTime = boost::posix_time::second_clock::local_time();
    const char* sctFilename = "/home/eric/NetBeansProjects/nickel/echantillon/Arkea/Arkea Sepa fichiers entrants/SCTSE_20160304T054638.XML";
    XMLParser xmlParser;
    SCTHandler sctHandler;
//    xmlParser.docCreated.connect(boost::bind(&SCTHandler::onDocCreated, sctHandler, _1));
    xmlParser.docCreated.connect(sctHandler);
    xmlParser.readFile(sctFilename);
    
    sctHandler.processOnHoldOperations();
    sctHandler.processRejectedOperations();
    sctHandler.processProvisionedOperations();

    boost::posix_time::time_duration diff = boost::posix_time::second_clock::local_time() - startTime;
    std::cout << "SCT file processed in " << diff.total_milliseconds() << " millisecs" << std::endl;
    
    startTime = boost::posix_time::second_clock::local_time();
    boost::thread producer_thread(producer);
    boost::thread consumer_thread(consumer);
    
    producer_thread.join();
    done = true;
    consumer_thread.join();
    
    diff = boost::posix_time::second_clock::local_time() - startTime;
    std::cout << "producer count " << producer_count << " consumer count " << consumer_count << " milliSec " << diff.total_milliseconds() << std::endl;
    
    return 0;
}

