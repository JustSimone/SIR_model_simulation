cmake_minimum_required(VERSION 3.16)
project(simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)

include_directories("include")

add_executable(simulation pandemic_simulation_no_perlin/ball_main.cpp pandemic_simulation_no_perlin/balls.cpp pandemic_simulation_no_perlin/elements.cpp)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(simulation PRIVATE sfml-graphics)
target_compile_options(simulation PRIVATE -Wall -Wextra)

add_executable(simulation_perlin pandemic_simulation_perlin/ball_main.cpp pandemic_simulation_perlin/balls.cpp pandemic_simulation_perlin/elements.cpp pandemic_simulation_perlin/PerlinNoise.cpp)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(simulation_perlin PRIVATE sfml-graphics)
target_compile_options(simulation_perlin PRIVATE -Wall -Wextra)
