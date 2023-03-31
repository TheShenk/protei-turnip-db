//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_TCPCONNECTION_H
#define PROTEI_TURNIP_DB_TCPCONNECTION_H


#include <memory>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>

class TcpConnection {

public:
    TcpConnection(boost::asio::io_context& io_context):
    _socket(io_context) {}

    void start();

    boost::asio::ip::tcp::socket &socket();

private:
    boost::asio::ip::tcp::socket _socket;

    static void handle_write(const boost::system::error_code& error,
                      size_t bytes_transferred);
};


#endif //PROTEI_TURNIP_DB_TCPCONNECTION_H
