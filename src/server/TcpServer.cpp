//
// Created by shenk on 31.03.23.
//

#include "TcpServer.h"

void TcpServer::startAccept() {
    auto connection = boost::make_shared<TcpConnection>(_io_context, _data_base);
    _acceptor.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error) {
        handleAccept(connection, error);
    });
}

void TcpServer::handleAccept(boost::shared_ptr<TcpConnection> new_connection, const boost::system::error_code &error) {
    if (!error) {
        BOOST_LOG_TRIVIAL(info) << "Founded new connection";
        new_connection->start();
    } else {
        BOOST_LOG_TRIVIAL(error) << error << "-" << error.message();
    }
    startAccept();
}
