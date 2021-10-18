#include <gtest/gtest.h>

#include <barthes/config.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>

TEST(ScreenHandlerTest, adjust_view__no_adjustment) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), false);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_up__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .view=std::make_pair(1, 0),
        .cursor=std::make_pair(-1, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), true);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_up__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(50, 50),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(-1, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), false);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_down__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 50),
        .view=std::make_pair(1, 0),
        .cursor=std::make_pair(5, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane",
            "Nina Simone",
            "Roberta Flack",
            "Charles Mingus",
            "Herbie Hancock",
            "Max Roach"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), true);
    EXPECT_EQ(tc.view.first, 2);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 4);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_down__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 50),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(5, 0),
        .file_buffer=std::vector<std::string>{
            "Miles Davis",
            "John Coltrane",
            "Nina Simone"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), false);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 2);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_right__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 5),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 5),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), true);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 1);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 4);
}

TEST(ScreenHandlerTest, adjust_view__scroll_right__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 12),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 12),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), false);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 11);
}

TEST(ScreenHandlerTest, adjust_view__scroll_left__in_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 50),
        .view=std::make_pair(0, 2),
        .cursor=std::make_pair(0, -1),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), true);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 1);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, adjust_view__scroll_left__out_of_bounds) {
    barthes::TermConfig tc = {
        .window_size=std::make_pair(5, 50),
        .view=std::make_pair(0, 0),
        .cursor=std::make_pair(0, -1),
        .file_buffer=std::vector<std::string>{
            "Miles Davis"
        }
    };
    EXPECT_EQ(barthes::adjust_view(&tc), false);
    EXPECT_EQ(tc.view.first, 0);
    EXPECT_EQ(tc.view.second, 0);
    EXPECT_EQ(tc.cursor.first, 0);
    EXPECT_EQ(tc.cursor.second, 0);
}

TEST(ScreenHandlerTest, move_cursor__nowhere) {
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

TEST(ScreenHandlerTest, move_cursor__up__in_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__up__out_of_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__down__in_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__down__out_of_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__right__in_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__right__out_of_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__left__in_bounds) {
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

TEST(ScreenHandlerTest, move_cursor__left__out_of_bounds) {
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
