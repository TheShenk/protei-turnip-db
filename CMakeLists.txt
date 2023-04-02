cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.81 REQUIRED system program_options log)
find_package(TBB REQUIRED)
if(Boost_FOUND AND TBB_FOUND)
    add_executable(turnip-server
            src/main.cpp
            src/TcpServer.h src/TcpServer.cpp
            src/TcpConnection.h src/TcpConnection.cpp
            src/DataBase.h src/DataBase.cpp
            src/commands/Command.h src/commands/CommandFactory.h
            src/commands/PutCommand.h src/commands/GetCommand.h
            src/commands/DeleteCommand.h src/commands/CountCommand.h
            src/commands/DumpCommand.h)
    target_link_libraries(turnip-server ${Boost_LIBRARIES} TBB::tbb)
endif()
