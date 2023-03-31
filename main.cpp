//
// Created by shenk on 31.03.23.
//

#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Produce help message")
            ("max-clients", boost::program_options::value<int>(), "Set maximum allowed clients number")
            ;

    boost::program_options::variables_map vm;
    auto parsed_options = boost::program_options::parse_command_line(argc, argv, desc);
    boost::program_options::store(parsed_options, vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
}