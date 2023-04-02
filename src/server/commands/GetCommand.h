//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_GETCOMMAND_H
#define PROTEI_TURNIP_DB_GETCOMMAND_H

#include "Command.h"

#include <utility>

class GetCommand: public Command {

public:

    explicit GetCommand(std::string key): _key(std::move(key)) {}

    std::string execute(hash_map_t &data) override {

        hash_map_t::const_accessor accessor;
        auto key_exist = data.find(accessor, _key);
        if (key_exist) {
            return "OK " + accessor->second;
        } else {
            return "NE";
        }
    }

private:

    std::string _key;

};

#endif //PROTEI_TURNIP_DB_GETCOMMAND_H
