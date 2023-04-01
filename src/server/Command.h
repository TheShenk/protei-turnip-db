//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_COMMAND_H
#define PROTEI_TURNIP_DB_COMMAND_H


#include <string>

#include <boost/algorithm/string.hpp>
#include <iostream>

enum CommandType {

    INVALID,
    PUT,
    GET,
    DELETE,
    COUNT

};

class Command {

public:

    explicit Command(std::string command_data);

    CommandType getType();
    const std::vector<std::string>& getArguments() const;
    bool correct() const;

private:

    CommandType type;
    std::vector<std::string> arguments;

};


#endif //PROTEI_TURNIP_DB_COMMAND_H
