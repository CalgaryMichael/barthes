#include <limits.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <barthes/handlers/file.h>

/* Helpful way to get a file from the data folder */
char *get_test_filepath(std::string filename) {
    // `TEST_DATA_FILEPATH` should be set during test setup
    std::string test_data_filepath = std::string(getenv("TEST_DATA_FILEPATH"));
    test_data_filepath += filename;

    char *result = new char[test_data_filepath.size() + 1];
    strcpy(result, test_data_filepath.c_str());
    return result;
}

TEST(FileHandlerTest, get_filepath__relaive) {
    char *expected = get_test_filepath((std::string)"example.txt");

    char *argv[2] = {(char*)"", (char*)"../data/example.txt"};
    EXPECT_EQ(*barthes::get_filepath(sizeof(argv), argv), *expected);
}

TEST(FileHandlerTest, get_filepath__absolute) {
    char *expected = get_test_filepath((std::string)"example.txt");

    char *argv[2] = {(char*)"", expected};
    EXPECT_EQ(*barthes::get_filepath(sizeof(argv), argv), *expected);
}

TEST(FileHandlerTest, open_file__empty) {
    char *filepath = get_test_filepath((std::string)"empty.txt");

    std::vector<std::string> expected = {};
    EXPECT_EQ(barthes::open_file(filepath), expected);
}

TEST(FileHandlerTest, open_file__non_empty) {
    char *filepath = get_test_filepath((std::string)"example.txt");

    std::vector<std::string> expected = {
        "This is an example file",
        "",
        "This has many lines",
        "and\ttabs"
    };
    EXPECT_EQ(barthes::open_file(filepath), expected) << filepath;

    delete [] filepath;
}
