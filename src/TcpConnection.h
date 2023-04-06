//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_TCPCONNECTION_H
#define PROTEI_TURNIP_DB_TCPCONNECTION_H


#include <memory>
#include <iostream>
#include <utility>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/as_tuple.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/log/trivial.hpp>

#include "DataBase.h"
#include "commands/CommandFactory.h"

/* Need to calculate number of opened connections. Need type that increment his internal count when passed to connection
 * and decrement in destructor of connection. shared_ptr do exactly this. Used std::shared_ptr instead of boost version
 * because of information that std::shared_ptr is thread-safety when only copy: https://habr.com/ru/articles/311560/ */
using MaxConnectionsLimit = std::shared_ptr<int>;

/**
 * Class to work with connection from one user
 * @tparam Executor - Type of context object. Allow to use different types, such as boost::asio::thread_pool and
 * boost::asio::io_context. Can't just accept boost::asio::execution_context because can't create socket from it.
 */
template <typename Executor>
class TcpConnection: public boost::enable_shared_from_this<TcpConnection<Executor>> {

public:

    /**
     *
     * @param context - object to communicate with OS I/O functions
     * @param data_base - database on which execute commands from user
     * @param limit - object that count current connections number. It passed to connection to decrement his
     * value in TcpConnection destructor
     */
    TcpConnection(Executor& context, DataBase &data_base, MaxConnectionsLimit limit):
    _socket(context),
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
    boost::asio::awaitable<void> start() {
        // Needed to increase the lifetime of an object until the end of the function
        auto self(this->shared_from_this());

        std::string message = "Welcome to TurnipDB!\n";
        auto [error, bytes_transferred] = co_await _socket.async_write_some(boost::asio::buffer(message),
                                                                            boost::asio::as_tuple(boost::asio::use_awaitable));

        while (!error) {
            std::tie(error, bytes_transferred) = co_await boost::asio::async_read(_socket,
                                                     command_buffer,
                                                     boost::asio::transfer_at_least(1),
                                                     boost::asio::as_tuple(boost::asio::use_awaitable));
            if (!error) {
                auto result = processCommand();
                auto result_buffer = boost::asio::buffer(result);
                std::tie(error, bytes_transferred) = co_await boost::asio::async_write(_socket,
                                                                                       result_buffer,
                                                                                       boost::asio::as_tuple(boost::asio::use_awaitable));
                if (!error) {
                    BOOST_LOG_TRIVIAL(debug) << "Result bytes transferred: " << bytes_transferred;
                } else {
                    BOOST_LOG_TRIVIAL(error) << "Error on transfer result: " << error << "-" << error.message();
                }
            } else {
                BOOST_LOG_TRIVIAL(error) << "Error on receive command: " << error << "-" << error.message();
            }
        }
    }

    /**
     *
     * @return socket which is used by connection
     */
    boost::asio::ip::tcp::socket& socket() {
        return _socket;
    }

private:
    boost::asio::ip::tcp::socket _socket;
    boost::asio::streambuf command_buffer;
    DataBase &_data_base;
    MaxConnectionsLimit _limit;

    /**
     * Process command from user and return result that need to send back
     * @return String with command execution result
     */
    std::string processCommand() {
        std::istream is(&command_buffer);
        std::string command_data;
        std::getline(is, command_data);

        BOOST_LOG_TRIVIAL(debug) << "Received new command - " << command_data;
        auto command = CommandFactory::fromString(command_data);

        std::string result;
        if (command.has_value()) {
            result = _data_base.runCommand(std::move(command.value()));
        } else {
            result = "WC"; // Wrong command
            BOOST_LOG_TRIVIAL(debug) << "Can't parse command: " << command_data;
        }
        result += "\n";
        return result;
    }

};


#endif //PROTEI_TURNIP_DB_TCPCONNECTION_H
