#include <gtest/gtest.h>

#include <barthes/config.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>

TEST(InputHandlerTest, move_cursor__nowhere) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, 0, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__up__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, barthes::UP, 0);
    EXPECT_EQ(tc.cursor.first, 1);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__up__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(1, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, barthes::UP, 0);
    EXPECT_EQ(tc.cursor.first, 1);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__down__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(2, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, barthes::DOWN, 0);
    EXPECT_EQ(tc.cursor.first, 1);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__down__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, barthes::DOWN, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__right__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, 0, barthes::RIGHT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 1);
}

TEST(InputHandlerTest, move_cursor__right__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 11),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, 0, barthes::RIGHT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 11);
}

TEST(InputHandlerTest, move_cursor__left__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 2),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, 0, barthes::LEFT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 1);
}

TEST(InputHandlerTest, move_cursor__left__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane"
        }
    };
    barthes::move_cursor(&tc, 0, barthes::LEFT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}
