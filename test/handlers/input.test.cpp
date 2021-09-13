#include <gtest/gtest.h>

#include <barthes/handlers/input.h>


TEST(InputHandlerDeathTest, HandleKeyPress__Q) {
  EXPECT_EXIT(barthes::handle_keypress('q'), testing::ExitedWithCode(EXIT_SUCCESS), "");
}
