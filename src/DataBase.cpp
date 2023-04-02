//
// Created by shenk on 31.03.23.
//

#include "DataBase.h"

std::string DataBase::runCommand(std::unique_ptr<Command> command) {
    return command->execute(_data);
}
