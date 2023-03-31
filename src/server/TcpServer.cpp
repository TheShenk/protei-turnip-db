//
// Created by shenk on 31.03.23.
//

#include "TcpServer.h"

void TcpServer::start_accept() {
    auto connection = std::make_shared<TcpConnection>(_io_context);
    _acceptor.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error) {
        handle_accept(connection, error);
    });
}

void TcpServer::handle_accept(std::shared_ptr<TcpConnection> new_connection, const boost::system::error_code &error) {
    if (!error) {
        new_connection->start();
    }
    start_accept();
}
