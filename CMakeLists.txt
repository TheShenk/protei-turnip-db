cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.81 REQUIRED system program_options log)
find_package(TBB REQUIRED)
if(Boost_FOUND AND TBB_FOUND)
    add_subdirectory(src/server)
endif()
