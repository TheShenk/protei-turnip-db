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
#include <boost/enable_shared_from_this.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>

class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {

public:
    TcpConnection(boost::asio::io_context& io_context):
    _socket(io_context) {}

    ~TcpConnection() {
        BOOST_LOG_TRIVIAL(debug) << "~TcpConnection()";
    }

    void start();

    boost::asio::ip::tcp::socket &socket();

private:
    boost::asio::ip::tcp::socket _socket;
    static const int MAX_COMMAND_LENGTH = 1000;
    char command_data[MAX_COMMAND_LENGTH];

    static void handle_write(const boost::system::error_code& error,
                      size_t bytes_transferred);


    void read_command();
    void on_command_handler(const boost::system::error_code& error,
                            size_t bytes_transferred);
//    void sendResult();
};


#endif //PROTEI_TURNIP_DB_TCPCONNECTION_H
