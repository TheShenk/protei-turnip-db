cmake_minimum_required(VERSION 3.25)
project(protei-turnip-db)

set(CMAKE_CXX_STANDARD 17)



find_package(Boost 1.81 REQUIRED system program_options log)
find_package(TBB REQUIRED)
if(Boost_FOUND AND TBB_FOUND)
    add_library(turnip-lib
            src/TcpServer.h src/TcpServer.cpp
            src/TcpConnection.h src/TcpConnection.cpp
            src/DataBase.h src/DataBase.cpp
            src/commands/Command.h src/commands/CommandFactory.h
            src/commands/PutCommand.h src/commands/GetCommand.h
            src/commands/DeleteCommand.h src/commands/CountCommand.h
            src/commands/DumpCommand.h)
    target_link_libraries(turnip-lib
            ${Boost_LIBRARIES}
            TBB::tbb)

    add_executable(turnip-server
            src/main.cpp)
    target_link_libraries(turnip-server turnip-lib)

    enable_testing()
    find_package(GTest)
    include(GoogleTest)

    add_executable(tests tests/database_tests.cpp tests/command_factory_tests.cpp)
    target_link_libraries(tests
            GTest::GTest GTest::Main
            turnip-lib)
    gtest_discover_tests(tests)

    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs ${PROJECT_SOURCE_DIR})
endif()
