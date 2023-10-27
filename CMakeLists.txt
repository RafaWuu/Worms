cmake_minimum_required(VERSION 3.0)

project(hello_world)

set(CMAKE_CXX_STANDARD 17)

set(BOX2D_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libbox2d.a")  
set(BOX2D_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/Box2D")      

set(SRC_FILES hello_world.cpp doctest.h)

add_executable(hello_world ${SRC_FILES})

target_include_directories(hello_world PRIVATE ${BOX2D_INCLUDE_PATH})

target_link_libraries(hello_world PRIVATE ${BOX2D_LIBRARY_PATH} SDL2)

