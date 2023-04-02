//
// Created by shenk on 31.03.23.
//

#include "TcpConnection.h"
#include "commands/CommandFactory.h"

void TcpConnection::start() {
    std::string message = "Welcome to TurnipDB!\n";
    boost::asio::async_write(_socket, boost::asio::buffer(message), &TcpConnection::handleWrite);
    readCommand();
}

void TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytes_transferred) {}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return _socket;
}

void TcpConnection::readCommand() {

    boost::asio::async_read(_socket, command_buffer,
                            boost::asio::transfer_at_least(1),
                            boost::bind(&TcpConnection::onCommandHandler,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::onCommandHandler(const boost::system::error_code &error, size_t bytes_transferred) {

    if (!error) {
        std::istream is(&command_buffer);
        std::string command_data;
        std::getline(is, command_data);

        BOOST_LOG_TRIVIAL(debug) << "Received new command - " << command_data;
        auto command = CommandFactory::fromString(command_data);

        if (command.has_value()) {
            auto result = _data_base.runCommand(std::move(command.value()));
            result += "\n";
            writeResult(result);
        } else {
            BOOST_LOG_TRIVIAL(debug) << "Can't parse command: " << command_data;
        }

        readCommand();
    } else {
        BOOST_LOG_TRIVIAL(error) << "Error on receive command: " << error << "-" << error.message();
    }

}

void TcpConnection::writeResult(std::string result) {
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
