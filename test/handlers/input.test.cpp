#include <gtest/gtest.h>

#include <barthes/config.h>
#include <barthes/handlers/input.h>

TEST(InputHandlerTest, move_cursor__nowhere) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0)
    };
    barthes::move_cursor(&tc, 0, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__up__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0)
    };
    barthes::move_cursor(&tc, barthes::UP, 0);
    EXPECT_EQ(tc.cursor.first, 1);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__up__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(49, 0)
    };
    barthes::move_cursor(&tc, barthes::UP, 0);
    EXPECT_EQ(tc.cursor.first, 49);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__down__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(2, 0)
    };
    barthes::move_cursor(&tc, barthes::DOWN, 0);
    EXPECT_EQ(tc.cursor.first, 1);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__down__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0)
    };
    barthes::move_cursor(&tc, barthes::DOWN, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, move_cursor__right__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0)
    };
    barthes::move_cursor(&tc, 0, barthes::RIGHT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 1);
}

TEST(InputHandlerTest, move_cursor__right__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 49)
    };
    barthes::move_cursor(&tc, 0, barthes::RIGHT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 49);
}

TEST(InputHandlerTest, move_cursor__left__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 2)
    };
    barthes::move_cursor(&tc, 0, barthes::LEFT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 1);
}

TEST(InputHandlerTest, move_cursor__left__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .cursor=std::make_pair(0, 0)
    };
    barthes::move_cursor(&tc, 0, barthes::LEFT);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(InputHandlerTest, handle_keypress__empty) {
  EXPECT_EQ(barthes::handle_keypress('\0'), barthes::KeypressResponse::Continue);
}

TEST(InputHandlerTest, handle_keypress__Q) {
  EXPECT_EQ(barthes::handle_keypress(CTRL_KEY('q')), barthes::KeypressResponse::Exit);
}
