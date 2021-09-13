#include <gtest/gtest.h>

#include <barthes/handlers/input.h>

TEST(InputHandlerTest, HandleKeyPress__empty) {
  EXPECT_EQ(barthes::handle_keypress('\0'), barthes::KeypressResponse::Continue);
}

TEST(InputHandlerTest, HandleKeyPress__Q) {
  EXPECT_EQ(barthes::handle_keypress('q'), barthes::KeypressResponse::Exit);
}
