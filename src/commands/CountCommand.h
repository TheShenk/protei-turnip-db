//
// Created by shenk on 02.04.23.
//

#ifndef PROTEI_TURNIP_DB_COUNTCOMMAND_H
#define PROTEI_TURNIP_DB_COUNTCOMMAND_H


#include "Command.h"

class CountCommand: public Command {

    std::string execute(hash_map_t &data_base) override {
        auto keys_count = data_base.size();
        return "OK " + std::to_string(keys_count);
    }

};


#endif //PROTEI_TURNIP_DB_COUNTCOMMAND_H
