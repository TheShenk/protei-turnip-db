//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_TCPSERVER_H
#define PROTEI_TURNIP_DB_TCPSERVER_H

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/as_tuple.hpp>
#include <boost/make_shared.hpp>
#include <boost/log/trivial.hpp>

#include "TcpConnection.h"
#include "DataBase.h"

// +1 because server also owner of limit-object, +1 because always need connection to listen for next user
const int INNER_CONNECTION_COUNT = 2;

/**
 * Class for server that listening for new connection and refused in it if limit is overreached
 * @tparam Executor - Type of context object. Allow to use different types, such as boost::asio::thread_pool and
 * boost::asio::io_context. Can't just accept boost::asio::execution_context becouse can't create socket from it.
 */
template <typename Executor>
class TcpServer {
public:

    /**
     *
     * @param context - object to communicate with OS I/O functions
     * @param port - port for listening new connections
     * @param max_clients_count - Max number of connections
     * @param data_base - reference to database with which users will work
     */
    TcpServer(Executor &context, int port, int max_clients_count, DataBase &data_base):
    _context(context),
    _endpoint(boost::asio::ip::tcp::v4(), port),
    _acceptor(context, _endpoint),
    _data_base(data_base),
    _limit(std::make_shared<int>(0)),
    _max_connections_count(max_clients_count + INNER_CONNECTION_COUNT) {}

    /**
     * Start listening for new connections
     */
    boost::asio::awaitable<void> startAccept() {
        BOOST_LOG_TRIVIAL(info) << "Waiting for connection";

        while (true) {
            auto connection = boost::make_shared<TcpConnection<Executor>>(_context, _data_base, _limit);
            auto [error] = co_await _acceptor.async_accept(connection->socket(),
                                                           boost::asio::as_tuple(boost::asio::use_awaitable));
            if (!error) {
                BOOST_LOG_TRIVIAL(info) << "Founded new connection: "
                                        << connection->socket().remote_endpoint().address() << ":"
                                        << connection->socket().remote_endpoint().port();
                BOOST_LOG_TRIVIAL(debug) << "Current connections in use: " << _limit.use_count();
                if (_limit.use_count() < _max_connections_count) {
                    boost::asio::co_spawn(_context, connection->start(), boost::asio::detached);
                } else {
                    BOOST_LOG_TRIVIAL(info) << "Connection refused due to reaching the limit";
                }
            } else {
                BOOST_LOG_TRIVIAL(error) << error << "-" << error.message();
            }
        }
    }

private:
    Executor &_context;
    boost::asio::ip::tcp::endpoint _endpoint;
    boost::asio::ip::tcp::acceptor _acceptor;
    DataBase &_data_base;
    MaxConnectionsLimit _limit;
    int _max_connections_count;

};


#endif //PROTEI_TURNIP_DB_TCPSERVER_H
