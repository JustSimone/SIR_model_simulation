cmake_minimum_required(VERSION 3.16)
project(ball)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
set(CMAKE_BUILD_TYPE Debug)


add_executable(ball ball_main.cpp balls.cpp)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(ball PRIVATE sfml-graphics)
target_compile_options(ball PRIVATE -Wall -Wextra)
