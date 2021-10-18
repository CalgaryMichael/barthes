#include <gtest/gtest.h>

#include <barthes/config.h>


TEST(ConfigTest, get_row_max__no_buffer) {
    barthes::TermConfig tc = {
        .file_buffer=std::vector<std::string>{}
    };
    EXPECT_EQ(get_row_max(&tc), 0);
}

TEST(ConfigTest, get_row_max__single_line) {
    barthes::TermConfig tc = {
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(get_row_max(&tc), 0);
}

TEST(ConfigTest, get_row_max__multi_line) {
    barthes::TermConfig tc = {
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "Jone Coltrane"
        }
    };
    EXPECT_EQ(get_row_max(&tc), 1);
}

TEST(ConfigTest, get_col_max__no_buffer) {
    barthes::TermConfig tc = {
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{}
    };
    EXPECT_EQ(get_col_max(&tc), 0);
}

TEST(ConfigTest, get_col_max__no_letters) {
    barthes::TermConfig tc = {
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            ""
        }
    };
    EXPECT_EQ(get_col_max(&tc), 0);
}

TEST(ConfigTest, get_col_max__single_letter) {
    barthes::TermConfig tc = {
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "M"
        }
    };
    EXPECT_EQ(get_col_max(&tc), 1);
}

TEST(ConfigTest, get_col_max__multi_letter) {
    barthes::TermConfig tc = {
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(get_col_max(&tc), 11);
}

TEST(ConfigTest, get_file_loc__initial_view) {
    barthes::TermConfig tc = {
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(5, 10)
    };
    std::pair<int, int> file_loc = barthes::get_file_loc(&tc);
    EXPECT_EQ(file_loc.first, 5);
    EXPECT_EQ(file_loc.second, 10);
}

TEST(ConfigTest, get_file_loc__scrolled_view) {
    barthes::TermConfig tc = {
        .view=std::make_pair(5, 2),
        .cursor=std::make_pair(5, 10)
    };
    std::pair<int, int> file_loc = barthes::get_file_loc(&tc);
    EXPECT_EQ(file_loc.first, 10);
    EXPECT_EQ(file_loc.second, 12);
}
