//
// Created by shenk on 31.03.23.
//

#include "DataBase.h"

std::string DataBase::runCommand(std::unique_ptr<Command> command) {
    return command->execute(_data);
}

void DataBase::load(const std::string &filepath) {
    std::ifstream ifstream(filepath);
    if (!ifstream.is_open()) {
        BOOST_LOG_TRIVIAL(error) << "Can't open dump file";
        return;
    }

    load(ifstream);
}

void DataBase::load(std::istream &stream) {
    hash_map_t::accessor accessor;
    while (!stream.eof()) {
        std::string key;
        std::string value;

        stream >> key >> value;

        // Last line of dump file is empty
        if (!key.empty() && !value.empty()) {
            BOOST_LOG_TRIVIAL(debug) << "Inserting: " << key << " " << value;

            _data.insert(accessor, key);
            if (!accessor.empty()) {
                accessor->second = value;
            } else {
                BOOST_LOG_TRIVIAL(error) << "Error in inserting: " << key << " " << value;
            }
        }
    }
}
