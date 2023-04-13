//
// Created by shenk on 01.04.23.
//

#ifndef PROTEI_TURNIP_DB_DELETECOMMAND_H
#define PROTEI_TURNIP_DB_DELETECOMMAND_H

#include "Command.h"

#include <utility>

/**
 * Command to delete given key and corresponding value from database
 */
class DeleteCommand: public Command {

public:

    /**
     *
     * @param key - key to delete from database
     */
    explicit DeleteCommand(std::string key): _key(std::move(key)) {}

    /**
     * Delete key from given database
     * @param data - reference to database for which need to delete key
     * @return "OK <previous value" if operation successful, "NE" otherwise
     */
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
