cmake_minimum_required(VERSION 3.2)
project(grassland)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    src/grid.cpp
    src/main.cpp
    src/math.cpp
    src/player.cpp
    src/sprite.cpp
    src/tilemap.cpp
    src/tileset.cpp
    src/world.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra)
endif()