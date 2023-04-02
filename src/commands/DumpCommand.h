//
// Created by shenk on 02.04.23.
//

#ifndef PROTEI_TURNIP_DB_DUMPCOMMAND_H
#define PROTEI_TURNIP_DB_DUMPCOMMAND_H


#include <fstream>
#include "Command.h"

class DumpCommand: public Command{

public:
    DumpCommand(std::string filename): _filename(std::move(filename)) {}

    std::string execute(hash_map_t &data_base) override {
        std::ofstream ofstream(_filename);
        if (!ofstream.is_open()) {
            return "NF";
        }
        for (const auto &[key, value]: data_base) {
            ofstream << key << " " << value << std::endl;
        }
        BOOST_LOG_TRIVIAL(info) << "Database dumped in file " << _filename;
        return "OK";
    }

private:
    std::string _filename;
};


#endif //PROTEI_TURNIP_DB_DUMPCOMMAND_H
