CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(barthes)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

SET(source_files
    config.cpp
    exceptions.cpp
    handlers/file.cpp
    handlers/input.cpp
    handlers/screen.cpp
    handlers/terminal.cpp
    main.cpp
)

# Create libbarthes to be used by tests
ADD_LIBRARY(libbarthes ${source_files})
TARGET_INCLUDE_DIRECTORIES(libbarthes PRIVATE "${PROJECT_SOURCE_DIR}/../include")

# Create executable to be used by cli
ADD_EXECUTABLE(barthes ${source_files})
TARGET_INCLUDE_DIRECTORIES(barthes PRIVATE "${PROJECT_SOURCE_DIR}/../include")
