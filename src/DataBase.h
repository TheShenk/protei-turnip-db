//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_DATABASE_H
#define PROTEI_TURNIP_DB_DATABASE_H

#include <fstream>
#include <boost/log/trivial.hpp>
#include "commands/Command.h"

class DataBase {

public:

    std::string runCommand(std::unique_ptr<Command> command);
    void load(std::string filepath);

private:

    hash_map_t _data;

};


#endif //PROTEI_TURNIP_DB_DATABASE_H
