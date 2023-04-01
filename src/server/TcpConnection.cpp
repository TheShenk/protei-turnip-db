//
// Created by shenk on 31.03.23.
//

#include <boost/asio/read.hpp>
#include "TcpConnection.h"

void TcpConnection::start() {
    std::string message = "Hello World!\n";
    boost::asio::async_write(_socket, boost::asio::buffer(message), &TcpConnection::handleWrite);
    readCommand();
}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return _socket;
}

void TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytes_transferred) {
    std::cout << error.to_string() << " " << bytes_transferred << std::endl;
}

void TcpConnection::readCommand() {

    BOOST_LOG_TRIVIAL(debug) << "readCommand()";
    auto command_data_buffer = boost::asio::buffer(command_data, MAX_COMMAND_LENGTH);
    boost::asio::async_read(_socket, command_data_buffer,
                            boost::asio::transfer_at_least(1),
                            boost::bind(&TcpConnection::onCommandHandler,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::onCommandHandler(const boost::system::error_code &error, size_t bytes_transferred) {

    if (!error) {
        BOOST_LOG_TRIVIAL(debug) << "Received new command - " << command_data;
        Command command(command_data);
        auto result = _data_base.runCommand(command);
        result += "\n";
        writeResult(result);
        readCommand();
    } else {
        BOOST_LOG_TRIVIAL(error) << "Error on receive command: " << error << "-" << error.message();
    }

}

void TcpConnection::writeResult(std::string result) {
    BOOST_LOG_TRIVIAL(debug) << "writeResult()";
    auto result_buffer = boost::asio::buffer(result);
    boost::asio::async_write(_socket, result_buffer,
                            boost::bind(&TcpConnection::onResultHandler,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::onResultHandler(const boost::system::error_code &error, size_t bytes_transferred) {
    if (!error) {
        BOOST_LOG_TRIVIAL(debug) << "Result bytes transferred: " << bytes_transferred;
    } else {
        BOOST_LOG_TRIVIAL(error) << "Error on transfer result: " << error << "-" << error.message();
    }
}
