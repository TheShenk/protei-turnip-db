//
// Created by shenk on 31.03.23.
//

#include <boost/asio/read.hpp>
#include "TcpConnection.h"

void TcpConnection::start() {
    std::string message = "Hello World!\n";
    boost::asio::async_write(_socket, boost::asio::buffer(message), &TcpConnection::handle_write);
    read_command();
}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return _socket;
}

void TcpConnection::handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
    std::cout << error.to_string() << " " << bytes_transferred << std::endl;
}

void TcpConnection::read_command() {

    BOOST_LOG_TRIVIAL(debug) << "read_command()";
    auto command_data_buffer = boost::asio::buffer(command_data, MAX_COMMAND_LENGTH);
    auto shared_self = shared_from_this();
    boost::asio::async_read(_socket, command_data_buffer,
                            boost::asio::transfer_at_least(1),
                            boost::bind(&TcpConnection::on_command_handler,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::on_command_handler(const boost::system::error_code &error, size_t bytes_transferred) {

    if (!error) {
        BOOST_LOG_TRIVIAL(debug) << "Received new command - " << command_data;
        read_command();
    } else {
        BOOST_LOG_TRIVIAL(error) << error << "-" << error.message();
    }

}
