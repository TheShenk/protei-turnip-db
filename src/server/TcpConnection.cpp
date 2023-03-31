//
// Created by shenk on 31.03.23.
//

#include "TcpConnection.h"

void TcpConnection::start() {
    std::string message = "Hello World!\n";
    boost::asio::async_write(_socket, boost::asio::buffer(message), &TcpConnection::handle_write);
}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return _socket;
}

void TcpConnection::handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
    std::cout << error.to_string() << " " << bytes_transferred << std::endl;
}
