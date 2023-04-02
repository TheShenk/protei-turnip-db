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

class TcpServer {
public:
    TcpServer(boost::asio::io_context& io_context, int port):
    _io_context(io_context),
    _endpoint(boost::asio::ip::tcp::v4(), port),
    _acceptor(io_context, _endpoint),
    _data_base() {
        startAccept();
        BOOST_LOG_TRIVIAL(info) << "Waiting for connection";
    }

private:
    boost::asio::io_context &_io_context;
    boost::asio::ip::tcp::endpoint _endpoint;
    boost::asio::ip::tcp::acceptor _acceptor;
    DataBase _data_base;

    void startAccept();

    void handleAccept(const boost::shared_ptr<TcpConnection>& new_connection,
                      const boost::system::error_code& error);

};


#endif //PROTEI_TURNIP_DB_TCPSERVER_H
