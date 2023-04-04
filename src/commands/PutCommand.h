//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_PUTCOMMAND_H
#define PROTEI_TURNIP_DB_PUTCOMMAND_H

#include "Command.h"

#include <utility>

/**
 * Command to add value with given key to database
 */
class PutCommand: public Command {

public:

    /**
     *
     * @param key - key to link with value
     * @param value - value to save in database
     */
    PutCommand(std::string key, std::string value): _key(std::move(key)), _value(std::move(value)) {}

    /**
     * Add given key-value pair in databse
     * @param data_base - reference to database for which need to get keys count
     * @return "OK <previous value>" if key already existed, "OK" otherwise
     */
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
