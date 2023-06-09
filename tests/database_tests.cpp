//
// Created by shenk on 03.04.23.
//

#include "gtest/gtest.h"
#include "../src/DataBase.h"
#include "../src/commands/CommandFactory.h"

class DataBaseTests: public ::testing::Test {

public:
    DataBase db;
};

TEST_F(DataBaseTests, PutReturnOK)
{
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);
}

TEST_F(DataBaseTests, PutReturnOKWithPrevValue)
{
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("put testkey testvalue2");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);
}

TEST_F(DataBaseTests, GetReturnOKWithValue)
{
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("get testkey");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);
}

TEST_F(DataBaseTests, GetReturnNE)
{
    auto command = CommandFactory::fromString("get testkey");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("NE", result);
}

TEST_F(DataBaseTests, CountReturnOKZero)
{
    auto command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 0", result);
}

TEST_F(DataBaseTests, CountReturnOKOne)
{
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 1", result);
}

TEST_F(DataBaseTests, DeleteReturnNEWhenKeyDontExist) {

    auto command = CommandFactory::fromString("del testkey");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("NE", result);
}

TEST_F(DataBaseTests, DeleteReturnOKWhenKeyExist) {
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("del testkey");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);
}

TEST_F(DataBaseTests, GetReturnNEAfterDelete) {
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("del testkey");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);

    command = CommandFactory::fromString("get testkey");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("NE", result);
}

TEST_F(DataBaseTests, CountDecrementAfterDelete) {
    auto command = CommandFactory::fromString("put testkey testvalue");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK", result);

    command = CommandFactory::fromString("del testkey");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);

    command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 0", result);
}

TEST_F(DataBaseTests, LoadAndGetValue) {

    std::stringstream stream;
    stream << "testkey testvalue" << std::endl;
    db.load(stream);

    auto command = CommandFactory::fromString("get testkey");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK testvalue", result);

}

TEST_F(DataBaseTests, LoadAndCount3) {

    std::stringstream stream;
    stream << "testkey1 testvalue1" << std::endl;
    stream << "testkey2 testvalue2" << std::endl;
    stream << "testkey3 testvalue3" << std::endl;
    db.load(stream);

    auto command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 3", result);

}

TEST_F(DataBaseTests, LoadEmptyFileCount0) {

    std::stringstream stream;
    db.load(stream);

    auto command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 0", result);

}

TEST_F(DataBaseTests, LoadFileWithNewLinesCount0) {

    std::stringstream stream;
    stream << std::endl << std::endl << std::endl << std::endl;
    db.load(stream);

    auto command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());

    auto result = db.runCommand(std::move(*command));
    ASSERT_EQ("OK 0", result);

}