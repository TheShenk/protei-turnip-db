//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_COMMAND_H
#define PROTEI_TURNIP_DB_COMMAND_H

#include <string>
#include <tbb/concurrent_hash_map.h>
#include <boost/log/trivial.hpp>

using hash_map_t = tbb::concurrent_hash_map<std::string, std::string>;

class Command {

public:
    virtual std::string execute(hash_map_t &data_base)=0;

};


#endif //PROTEI_TURNIP_DB_COMMAND_H
