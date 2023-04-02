//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_DELETECOMMAND_H
#define PROTEI_TURNIP_DB_DELETECOMMAND_H

#include "Command.h"

#include <utility>

class DeleteCommand: public Command {

public:

    explicit DeleteCommand(std::string key): _key(std::move(key)) {}

    std::string execute(hash_map_t &data) override {

        hash_map_t::accessor accessor;
        auto key_exist = data.find(accessor, _key);
        if (key_exist) {
            auto previous_value = accessor->second;
            auto successful = data.erase(accessor);

            if (successful) {
                return "OK " + previous_value;
            } else {
                return "NE";
            }
        }
        return "NE";
    }

private:

    std::string _key;

};


#endif //PROTEI_TURNIP_DB_DELETECOMMAND_H
