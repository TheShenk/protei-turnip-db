//
// Created by shenk on 03.04.23.
//

#include "gtest/gtest.h"
#include "../src/commands/CommandFactory.h"

TEST(CommandFactoryTests, PutCommandExist) {
    auto command = CommandFactory::fromString("put key value");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, PutCapitalizedExist) {
    auto command = CommandFactory::fromString("PUT key value");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, PutWithThreeArgumentDontExist) {
    auto command = CommandFactory::fromString("put key value value");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, PutWithOneArgumentDontExist) {
    auto command = CommandFactory::fromString("put key");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, PutWithZeroArgumentsDontExist) {
    auto command = CommandFactory::fromString("put");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, PutWithALotOfSpacesExist) {
    auto command = CommandFactory::fromString("put            key              value");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, GetCommandExist) {
    auto command = CommandFactory::fromString("get key");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, GetWithoutArgumentsDontExist) {
    auto command = CommandFactory::fromString("get");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, GetWithTwoArgumentsDontExist) {
    auto command = CommandFactory::fromString("get key value");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, DeleteCommandExist) {
    auto command = CommandFactory::fromString("del key");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, DeleteWithoutArgumentsDontExist) {
    auto command = CommandFactory::fromString("del");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, DeleteWithTwoArgumentsDontExist) {
    auto command = CommandFactory::fromString("del key value");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, CountCommandExist) {
    auto command = CommandFactory::fromString("count");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, CountWithOneArgumentDontExist) {
    auto command = CommandFactory::fromString("count key");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, DumpCommandExist) {
    auto command = CommandFactory::fromString("dump filename.dump");
    ASSERT_TRUE(command.has_value());
}

TEST(CommandFactoryTests, DumpWithTwoArgumentsDontExist) {
    auto command = CommandFactory::fromString("dump key value");
    ASSERT_TRUE(!command.has_value());
}

TEST(CommandFactoryTests, DumpWithoutArgumentsDontExist) {
    auto command = CommandFactory::fromString("dump");
    ASSERT_TRUE(!command.has_value());
}