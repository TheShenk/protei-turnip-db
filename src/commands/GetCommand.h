//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_GETCOMMAND_H
#define PROTEI_TURNIP_DB_GETCOMMAND_H

#include "Command.h"

#include <utility>

/**
 * Command to get value corresponding to given key
 */
class GetCommand: public Command {

public:

    /**
     *
     * @param key - key for which value is needed
     */
    explicit GetCommand(std::string key): _key(std::move(key)) {}

    /**
     * Search value for given key in database
     * @param data_base - reference to database for which need to get keys count
     * @return "OK <value>" if key exist, "NE" otherwise
     */
    std::string execute(hash_map_t &data_base) override {

        hash_map_t::const_accessor accessor;
        auto key_exist = data_base.find(accessor, _key);
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
