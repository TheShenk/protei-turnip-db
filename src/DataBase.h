//
// Created by shenk on 31.03.23.
//

#ifndef PROTEI_TURNIP_DB_DATABASE_H
#define PROTEI_TURNIP_DB_DATABASE_H

#include <fstream>
#include <boost/log/trivial.hpp>
#include "commands/Command.h"

/**
 * Class containing functions for working with the database
 */
class DataBase {

public:

    /**
     * Run command on current database
     * @param command - command to execute
     * @return Result of command execution, described in Command subclasses
     */
    std::string runCommand(std::unique_ptr<Command> command);
    /**
     * Load database content from file
     * @param filepath - path to file from which load data
     */
    void load(const std::string &filepath);

    /**
     * Load database content from given stream. Used for testing.
     * @param stream - stream from which data is read
     */
    void load(std::istream &stream);

private:

    hash_map_t _data;

};


#endif //PROTEI_TURNIP_DB_DATABASE_H
