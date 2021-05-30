cmake_minimum_required(VERSION 3.2)
project(grassland)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(grassland
    src/grid.cpp
    src/main.cpp
    src/math.cpp
    src/player.cpp
    src/sprite.cpp
    src/tilemap.cpp
    src/tileset.cpp
    src/world.cpp
)

target_link_libraries(grassland ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

target_include_directories(grassland PRIVATE ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR})

