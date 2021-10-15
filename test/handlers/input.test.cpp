#include <gtest/gtest.h>

#include <barthes/config.h>
#include <barthes/handlers/input.h>

TEST(InputHandlerTest, handle_keypress__empty) {
  EXPECT_EQ(barthes::handle_keypress((int)'\0'), barthes::KeypressResponse::Continue);
}

TEST(InputHandlerTest, handle_keypress__Q) {
  EXPECT_EQ(barthes::handle_keypress((int)CTRL_KEY('q')), barthes::KeypressResponse::Exit);
}
