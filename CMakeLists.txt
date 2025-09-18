cmake_minimum_required(VERSION 3.26)
project(testgame)

set(CMAKE_CXX_STANDARD 17)

add_executable(testgame main.cpp)
set(SFML_DIR "C:/Users/Admin/CLionProjects/lib/sfml/GCC 13.1.0 MinGW (SEH) - 64-bit/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics audio REQUIRED)
target_link_libraries(testgame PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)