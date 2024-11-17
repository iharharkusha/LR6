#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include "../src/header-files/funcs.h"

TEST(ReadLineTest, InputWithSpaces) {
    const char* input = "Hello, this is a test.";
    std::istringstream input_stream(input);

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "Hello, this is a test.");
    delete[] result;
}

TEST(ReadLineTest, InputWithNumbers) {
    const char* input = "123 456 789";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "123 456 789");
    delete[] result;
}

TEST(ReadLineTest, InputWithSpecialChars) {
    const char* input = "#$%^&*()_+";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "#$%^&*()_+");
    delete[] result;
}

TEST(ReadLineTest, EmptyInput) {
    const char* input = "";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "");
    delete[] result;
}

TEST(ReadLineTest, MaxLengthInput) {
    const char* input = "A long line that should be exactly 127 characters long.......................................................................................";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, input);
    delete[] result;
}

TEST(ReadLineTest, InputWithNewline) {
    const char* input = "Hello\nWorld";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "Hello");
    delete[] result;
}

TEST(ReadLineTest, InputWithTab) {
    const char* input = "Hello\tWorld";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "Hello\tWorld");
    delete[] result;
}

TEST(ReadLineTest, InputWithCarriageReturn) {
    const char* input = "Hello\rWorld";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, "Hello\rWorld");
    delete[] result;
}

TEST(ReadLineTest, InputExceedingBufferSize) {
    const char* input = "This is a long string that exceeds the initial buffer size and should trigger a reallocation processsgmrfklewfklweklfjewkjlfjerwjfhkjfhhfjfrjfjkfewkjewkj";
    std::istringstream input_stream(input);
    std::cin.rdbuf(input_stream.rdbuf());

    char* result = readLine(input_stream);
    EXPECT_STREQ(result, input);
    delete[] result;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();  
}