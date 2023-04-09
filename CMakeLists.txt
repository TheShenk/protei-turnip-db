cmake_minimum_required(VERSION 3.0)
project(protei-turnip-db)

set(CMAKE_CXX_STANDARD 20)

include(CMakeFindDependencyMacro)
include(FetchContent)

find_package(Boost 1.81 REQUIRED system program_options log)
find_package(TBB REQUIRED)
if(Boost_FOUND AND TBB_FOUND)

    set(SRC src/TcpServer.h
            src/TcpConnection.h
            src/DataBase.h src/DataBase.cpp
            src/commands/Command.h src/commands/CommandFactory.h
            src/commands/PutCommand.h src/commands/GetCommand.h
            src/commands/DeleteCommand.h src/commands/CountCommand.h
            src/commands/DumpCommand.h
            )

    add_executable(turnip-server src/main.cpp ${SRC})
    target_link_libraries(turnip-server ${Boost_LIBRARIES} TBB::tbb)

    enable_testing()
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            SOURCE_DIR ${CMAKE_SOURCE_DIR}/google/googletest
            GIT_TAG main)
    FetchContent_MakeAvailable(googletest)

    add_executable(tests
            tests/database_tests.cpp
            tests/command_factory_tests.cpp
            ${SRC})
    target_link_libraries(tests
            ${Boost_LIBRARIES} TBB::tbb GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(tests)

    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs ${PROJECT_SOURCE_DIR})
endif()
