//
// Created by shenk on 31.03.23.
//

#include "TcpServer.h"

void TcpServer::start_accept() {
    auto connection = boost::make_shared<TcpConnection>(_io_context);
    _acceptor.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error) {
        handle_accept(connection, error);
    });
}

void TcpServer::handle_accept(boost::shared_ptr<TcpConnection> new_connection, const boost::system::error_code &error) {
    if (!error) {
        BOOST_LOG_TRIVIAL(info) << "Founded new connection";
        new_connection->start();
    } else {
        BOOST_LOG_TRIVIAL(error) << error << "-" << error.message();
    }
    start_accept();
}
