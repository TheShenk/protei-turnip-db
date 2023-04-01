//
// Created by shenk on 31.03.23.
//

#include "DataBase.h"

std::string DataBase::runCommand(Command &command) {
    if (command.correct()) {
        auto arguments = command.getArguments();
        switch (command.getType()) {
            case CommandType::PUT:
                return put(arguments[0], arguments[1]);
        }
    } else {
        return "Unknown command";
    }
}

std::string DataBase::put(std::string key, std::string value) {

    _data_base_t::accessor accessor;

    // insert return true if key don't exist
    auto key_exist = !_data.insert(accessor, key);
    auto previous_value = accessor->second;
    accessor->second = value;

    if (key_exist) {
        return "OK " + previous_value;
    } else {
        return "OK";
    }
}
