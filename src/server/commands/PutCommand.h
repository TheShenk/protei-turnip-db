//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_PUTCOMMAND_H
#define PROTEI_TURNIP_DB_PUTCOMMAND_H

#include "Command.h"

class PutCommand: public Command {

public:

    PutCommand(std::string key, std::string value): _key(key), _value(value) {}

    std::string execute(hash_map_t &data_base) override {
        hash_map_t::accessor accessor;

        // insert return true if key new
        auto key_exist = !data_base.insert(accessor, _key);
        auto previous_value = accessor->second;
        accessor->second = _value;

        if (key_exist) {
            return "OK " + previous_value;
        } else {
            return "OK";
        }
    }

private:

    std::string _key;
    std::string _value;
};


#endif //PROTEI_TURNIP_DB_PUTCOMMAND_H
