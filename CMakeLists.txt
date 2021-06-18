cmake_minimum_required(VERSION 3.2)
project(grassland)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # useful for tools like Clang-Tidy

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_program(NODE node)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(grassland
  src/entity.cpp
  src/game.cpp
  src/input.cpp
  src/main.cpp
  src/math.cpp
  src/grid.cpp
  src/sprite.cpp
  src/tilemap.cpp
  src/tileset.cpp
  src/world.cpp
)

set_target_properties(grassland
  PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

target_link_libraries(grassland ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

target_include_directories(grassland PRIVATE ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR})

add_custom_command(
  OUTPUT tilemaps
  COMMAND ${NODE} ${PROJECT_SOURCE_DIR}/tools/export-tilemaps.js
    --output-folder ${PROJECT_BINARY_DIR}
  DEPENDS ${PROJECT_SOURCE_DIR}/assets/Tiled
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Exporting Tiled maps to CSV files"
  VERBATIM)

add_custom_command(
  OUTPUT tilesets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/tilesets
    ${PROJECT_BINARY_DIR}/tilesets
  DEPENDS ${CMAKE_SOURCE_DIR}/assets/tilesets
  COMMENT "Copying tilesets"
  VERBATIM)

add_custom_target(grassland_assets
  DEPENDS ${PROJECT_BINARY_DIR}/tilemaps ${PROJECT_BINARY_DIR}/tilesets)

add_dependencies(grassland grassland_assets)
