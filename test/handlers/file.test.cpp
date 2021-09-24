#include <limits.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <barthes/handlers/file.h>

/* Helpful way to get a file from the data folder */
std::string get_test_filepath(std::string filename) {
    // `TEST_DATA_FILEPATH` should be set during test setup
    std::string test_data_filepath = std::string(getenv("TEST_DATA_FILEPATH"));
    test_data_filepath += filename;
    return test_data_filepath;
}

/* TODO: This case is really hard to test due to how cmake handles building your tests.
 *       The tests are executed in a file that is different from where the test files live.
 *       Because of this, it is hard to accurately get test the relative path, since it will
 *       be relative to the execution of the tests, and not relative to the test file itself.
 */
//TEST(FileHandlerTest, get_filepath__relative) {
//    std::string expected = get_test_filepath((std::string)"example.txt");
//
//    char *argv[2] = {(char*)"", (char*)"../data/example.txt"};
//    EXPECT_EQ(barthes::get_filepath(sizeof(argv), argv), expected);
//}

TEST(FileHandlerTest, get_filepath__absolute) {
    std::string expected = get_test_filepath((std::string)"example.txt");

    char *expected_char = new char[expected.size() + 1];
    strcpy(expected_char, expected.c_str());

    char *argv[2] = {(char*)"", expected_char};
    EXPECT_EQ(barthes::get_filepath(sizeof(argv), argv), expected);

    delete [] expected_char;
}

TEST(FileHandlerTest, open_file__empty) {
    std::string filepath = get_test_filepath((std::string)"empty.txt");

    std::vector<std::string> expected = {};
    EXPECT_EQ(barthes::open_file(filepath), expected);
}

TEST(FileHandlerTest, open_file__non_empty) {
    std::string filepath = get_test_filepath((std::string)"example.txt");

    std::vector<std::string> expected = {
        "This is an example file",
        "",
        "This has many lines",
        "and\ttabs"
    };
    EXPECT_EQ(barthes::open_file(filepath), expected) << filepath;
}
