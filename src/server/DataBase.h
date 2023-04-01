//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_DATABASE_H
#define PROTEI_TURNIP_DB_DATABASE_H

#include <tbb/concurrent_hash_map.h>
#include "Command.h"

class DataBase {

public:

    std::string runCommand(Command &command);

private:

    tbb::concurrent_hash_map<std::string, std::string> _data;

};


#endif //PROTEI_TURNIP_DB_DATABASE_H
