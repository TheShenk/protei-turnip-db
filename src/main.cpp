//
// Created by shenk on 31.03.23.
//

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include "TcpServer.h"

int main(int argc, char *argv[]) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Produce help message")
            ("max-clients", boost::program_options::value<int>()->default_value(1), "Set maximum allowed clients number")
            ("port", boost::program_options::value<int>()->default_value(31415), "Port to listen")
            ("threads", boost::program_options::value<int>()->default_value(4), "Threads count to use")
            ("dump", boost::program_options::value<std::string>(), "Path to dump file to load")
            ;

    boost::program_options::variables_map vm;
    auto parsed_options = boost::program_options::parse_command_line(argc, argv, desc);
    boost::program_options::store(parsed_options, vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    auto port = vm["port"].as<int>();
    auto threads_count = vm["threads"].as<int>();

    DataBase data_base;
    if (vm.count("dump")) {
        auto filepath = vm["dump"].as<std::string>();
        BOOST_LOG_TRIVIAL(info) << "Load dump from " << filepath;
        data_base.load(filepath);
    }

    boost::asio::thread_pool pool(threads_count);
    boost::asio::io_context io_context;
    TcpServer server(io_context, port, data_base);

    for (int i=0; i<threads_count; i++) {
        boost::asio::post(pool, [&io_context](){io_context.run();});
    }

    BOOST_LOG_TRIVIAL(info) << "TurnipDB started at port " << port << " with " << threads_count << " threads";

    pool.join();

}