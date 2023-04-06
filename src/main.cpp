//
// Created by shenk on 31.03.23.
//

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "TcpServer.h"

int main(int argc, char *argv[]) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Produce help message")
            ("max-clients", boost::program_options::value<int>()->default_value(1), "Set maximum allowed clients number")
            ("port", boost::program_options::value<int>()->default_value(31415), "Port to listen")
            ("threads", boost::program_options::value<int>()->default_value(4), "Threads count to use")
            ("dump", boost::program_options::value<std::string>(), "Path to dump file to load")
            ("log", boost::program_options::value<boost::log::trivial::severity_level>()->default_value(boost::log::trivial::info), "Minimum level of logs to output")
            ;

    boost::program_options::variables_map vm;
    auto parsed_options = boost::program_options::parse_command_line(argc, argv, desc);
    boost::program_options::store(parsed_options, vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    auto log_level = vm["log"].as<boost::log::trivial::severity_level>();
    boost::log::core::get()->set_filter (
            boost::log::trivial::severity >= log_level
    );


    auto port = vm["port"].as<int>();
    auto threads_count = vm["threads"].as<int>();
    auto max_clients_count = vm["max-clients"].as<int>();

    DataBase data_base;
    if (vm.count("dump")) {
        auto filepath = vm["dump"].as<std::string>();
        BOOST_LOG_TRIVIAL(info) << "Load dump from " << filepath;
        data_base.load(filepath);
    }

    boost::asio::thread_pool io_context(threads_count);

    BOOST_LOG_TRIVIAL(info) << "TurnipDB started at port " << port << " with " << threads_count << " threads";
    TcpServer server(io_context, port, max_clients_count, data_base);

    boost::asio::co_spawn(io_context, server.startAccept(), boost::asio::detached);

    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait([&io_context](auto, auto){ io_context.stop(); });

    io_context.join();

}