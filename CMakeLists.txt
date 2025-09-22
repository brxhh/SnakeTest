cmake_minimum_required(VERSION 3.16)
project(SnakeTest)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/opt/homebrew/include")
set(SFML_LIB_DIR "/opt/homebrew/lib")
include_directories(${SFML_INCLUDE_DIR})
add_executable(SnakeTest main.cpp)
target_link_libraries(SnakeTest
        ${SFML_LIB_DIR}/libsfml-graphics.dylib
        ${SFML_LIB_DIR}/libsfml-window.dylib
        ${SFML_LIB_DIR}/libsfml-system.dylib
)