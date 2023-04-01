//
// Created by shenk on 31.03.23.
//

#include "Command.h"

Command::Command(std::string command_data) {

    boost::trim(command_data);
    std::vector<std::string> command_parts;
    boost::split(command_parts, command_data, boost::is_any_of(" "), boost::token_compress_on);

    type = INVALID;
    if (command_parts.size() > 1) {
        if (command_parts[0] == "PUT" && command_parts.size() == 3) {
            type = PUT;
        } else if (command_parts[0] == "GET" && command_parts.size() == 2) {
            type = GET;
        } else if (command_parts[0] == "DEL" && command_parts.size() == 2) {
            type = DELETE;
        } else if (command_parts[0] == "COUNT" && command_parts.size() == 1) {
            type = COUNT;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    if (type != INVALID) {
        command_parts.erase(command_parts.begin());
        arguments = std::move(command_parts);
    }
}

CommandType Command::getType() { return type; }
const std::vector<std::string> &Command::getArguments() const { return arguments; }
bool Command::correct() const { return type != INVALID; }
