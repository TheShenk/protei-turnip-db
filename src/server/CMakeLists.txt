cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(turnip-server
        main.cpp
        TcpServer.h TcpServer.cpp
        TcpConnection.h TcpConnection.cpp
        DataBase.h DataBase.cpp
        commands/Command.h
        commands/PutCommand.h commands/GetCommand.h commands/CommandFactory.h commands/DeleteCommand.h commands/CountCommand.h commands/DumpCommand.h)
target_link_libraries(turnip-server ${Boost_LIBRARIES} TBB::tbb)