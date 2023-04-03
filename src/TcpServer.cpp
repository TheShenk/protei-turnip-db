//
// Created by shenk on 31.03.23.
//

#include "TcpServer.h"

void TcpServer::startAccept() {
    auto connection = boost::make_shared<TcpConnection>(_io_context, _data_base, _limit);
    _acceptor.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error) {
        handleAccept(connection, error);
    });
}

void TcpServer::handleAccept(const boost::shared_ptr<TcpConnection>& connection, const boost::system::error_code &error) {
    if (!error) {
        BOOST_LOG_TRIVIAL(info) << "Founded new connection: "
                                << connection->socket().remote_endpoint().address() << ":"
                                << connection->socket().remote_endpoint().port();
        BOOST_LOG_TRIVIAL(debug) << "Current connections in use: " << _limit.use_count();
        if (_limit.use_count() < _max_connections_count) {
            connection->start();
        } else {
            BOOST_LOG_TRIVIAL(info) << "Connection refused due to reaching the limit";
        }
    } else {
        BOOST_LOG_TRIVIAL(error) << error << "-" << error.message();
    }
    startAccept();
}
