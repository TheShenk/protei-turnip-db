//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_COMMANDFACTORY_H
#define PROTEI_TURNIP_DB_COMMANDFACTORY_H


#include <memory>
#include <vector>
#include <string>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <optional>

#include "Command.h"
#include "GetCommand.h"
#include "PutCommand.h"
#include "DeleteCommand.h"
#include "CountCommand.h"
#include "DumpCommand.h"

class CommandFactory {

public:
    static std::optional<std::unique_ptr<Command>> fromString(std::string command_data) {
        boost::trim(command_data);
        std::vector<std::string> command_parts;
        boost::split(command_parts, command_data, boost::is_any_of(" "), boost::token_compress_on);

        if (!command_parts.empty()) {
            boost::algorithm::to_lower(command_parts[0]);
            if (command_parts[0] == "put" && command_parts.size() == 3) {
                return std::make_unique<PutCommand>(command_parts[1], command_parts[2]);
            } else if (command_parts[0] == "get" && command_parts.size() == 2) {
                return std::make_unique<GetCommand>(command_parts[1]);
            } else if (command_parts[0] == "del" && command_parts.size() == 2) {
                return std::make_unique<DeleteCommand>(command_parts[1]);
            } else if (command_parts[0] == "count" && command_parts.size() == 1) {
                return std::make_unique<CountCommand>();
            } else if (command_parts[0] == "dump" && command_parts.size() == 2) {
                return std::make_unique<DumpCommand>(command_parts[1]);
            }
        }

        return std::nullopt;
    }

};


#endif //PROTEI_TURNIP_DB_COMMANDFACTORY_H
