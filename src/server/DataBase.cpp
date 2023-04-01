//
// Created by shenk on 31.03.23.
//

#include "DataBase.h"

std::string DataBase::runCommand(Command &command) {
    if (command.correct()) {
        return "OK\n";
    } else {
        return "Unknown command\n";
    }
}
