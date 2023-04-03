//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_TCPSERVER_H
#define PROTEI_TURNIP_DB_TCPSERVER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/make_shared.hpp>
#include <boost/log/trivial.hpp>

#include "TcpConnection.h"
#include "DataBase.h"

// +1 because server also owner of limit-object, +1 because always need connection to listen for next
const int INNER_CONNECTION_COUNT = 2;

class TcpServer {
public:
    TcpServer(boost::asio::io_context& io_context, int port, int max_clients_count, DataBase &data_base):
    _io_context(io_context),
    _endpoint(boost::asio::ip::tcp::v4(), port),
    _acceptor(io_context, _endpoint),
    _data_base(data_base),
    _limit(std::make_shared<int>(0)),
    _max_connections_count(max_clients_count + INNER_CONNECTION_COUNT) {
        startAccept();
        BOOST_LOG_TRIVIAL(info) << "Waiting for connection";
    }

private:
    boost::asio::io_context &_io_context;
    boost::asio::ip::tcp::endpoint _endpoint;
    boost::asio::ip::tcp::acceptor _acceptor;
    DataBase &_data_base;
    MaxConnectionsLimit _limit;
    int _max_connections_count;

    void startAccept();

    void handleAccept(const boost::shared_ptr<TcpConnection>& new_connection,
                      const boost::system::error_code& error);

};


#endif //PROTEI_TURNIP_DB_TCPSERVER_H
