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

/**
 * Class to work with connection from one user
 */
class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {

public:

    /**
     *
     * @param io_context - object to communicate with OS I/O functions
     * @param data_base - database on which execute commands from user
     * @param limit - object that count current connections number. It passed to connection to decrement his
     * value in TcpConnection destructor
     */
    TcpConnection(boost::asio::io_context& io_context, DataBase &data_base, MaxConnectionsLimit limit):
    _socket(io_context),
    _data_base(data_base),
    _limit(std::move(limit)){}

    /**
     * Used for locate situations when user disconnected but connection is not freed
     */
    ~TcpConnection() {
        BOOST_LOG_TRIVIAL(debug) << "~TcpConnection()";
    }

    /**
     * Start communication with user
     */
    void start();

    /**
     *
     * @return socket which is used by connection
     */
    boost::asio::ip::tcp::socket &socket();

private:
    boost::asio::ip::tcp::socket _socket;
    boost::asio::streambuf command_buffer;
    DataBase &_data_base;
    MaxConnectionsLimit _limit;

    /**
     * Callback for write greetings
     * @param error
     * @param bytes_transferred
     */
    static void handleWrite(const boost::system::error_code& error,
                            size_t bytes_transferred);

    /**
     * Read next command from user
     */
    void readCommand();
    /**
     * Sent result to user
     * @param result - result of command execution
     */
    void writeResult(std::string result);

    /**
     * Callback for reading command
     * @param error
     * @param bytes_transferred
     */
    void onCommandHandler(const boost::system::error_code& error,
                          size_t bytes_transferred);
    /**
     * Callback for writing result
     * @param error
     * @param bytes_transferred
     */
    void onResultHandler(const boost::system::error_code& error,
                          size_t bytes_transferred);
};


#endif //PROTEI_TURNIP_DB_TCPCONNECTION_H
