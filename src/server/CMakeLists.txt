cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(turnip-server
        main.cpp
        TcpServer.h
        TcpServer.cpp
        TcpConnection.cpp
        TcpConnection.h Command.cpp Command.h)
target_link_libraries(turnip-server ${Boost_LIBRARIES})