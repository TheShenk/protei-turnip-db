//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_TCPCONNECTION_H
#define PROTEI_TURNIP_DB_TCPCONNECTION_H


#include <memory>
#include <iostream>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/log/trivial.hpp>
#include <utility>

#include "DataBase.h"

using MaxConnectionsLimit = std::shared_ptr<int>;

class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {

public:
    TcpConnection(boost::asio::io_context& io_context, DataBase &data_base, MaxConnectionsLimit limit):
    _socket(io_context),
    _data_base(data_base),
    _limit(std::move(limit)){}

    ~TcpConnection() {
        BOOST_LOG_TRIVIAL(debug) << "~TcpConnection()";
    }

    void start();

    boost::asio::ip::tcp::socket &socket();

private:
    boost::asio::ip::tcp::socket _socket;
    boost::asio::streambuf command_buffer;
    DataBase &_data_base;
    MaxConnectionsLimit _limit;

    static void handleWrite(const boost::system::error_code& error,
                            size_t bytes_transferred);

    void readCommand();
    void writeResult(std::string result);

    void onCommandHandler(const boost::system::error_code& error,
                          size_t bytes_transferred);
    void onResultHandler(const boost::system::error_code& error,
                          size_t bytes_transferred);
};


#endif //PROTEI_TURNIP_DB_TCPCONNECTION_H
