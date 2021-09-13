CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(barthes_test)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

INCLUDE(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/955c7f837efad184ec63e771c42542d37545eaef.zip
)
FetchContent_MakeAvailable(googletest)

ENABLE_TESTING()

SET(test_files
  handlers/input.test.cpp
)

ADD_EXECUTABLE(barthes_test ${test_files})
TARGET_LINK_LIBRARIES(barthes_test gtest_main libbarthes)
TARGET_INCLUDE_DIRECTORIES(barthes_test PRIVATE "${PROJECT_SOURCE_DIR}/../include")

INCLUDE(GoogleTest)
gtest_discover_tests(barthes_test)
