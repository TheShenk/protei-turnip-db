cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.67 REQUIRED system program_options)
if(Boost_FOUND)
    add_subdirectory(src/server)
endif()
