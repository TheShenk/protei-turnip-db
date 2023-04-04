//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_COMMAND_H
#define PROTEI_TURNIP_DB_COMMAND_H

#include <string>
#include <tbb/concurrent_hash_map.h>
#include <boost/log/trivial.hpp>

/**
 * Type of used key-value storage.
 */
using hash_map_t = tbb::concurrent_hash_map<std::string, std::string>;

/**
 * Interface for all commands
 */
class Command {

public:
    /**
     * Execute command on given database
     * @param data_base - reference to data_base on which action is to be taken
     * @return result of command execution - string with status and data if needed
     */
    virtual std::string execute(hash_map_t &data_base)=0;

};


#endif //PROTEI_TURNIP_DB_COMMAND_H
