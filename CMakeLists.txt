# SDL2pp tutorial
#
# Written in 2015 by Dmitry Marakasiv <amdmi3@amdmi3.ru>
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(worms LANGUAGES CXX)

find_package(SDL2pp REQUIRED)

set(BOX2D_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libbox2d.a")  
set(BOX2D_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/Box2D") 

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(PRIVATE ${BOX2D_INCLUDE_PATH})

add_executable(worms 
	client/client_main.cpp
	client/client_client.cpp
	client/client_protocol.cpp
	client/client_sender.cpp
	common/common_liberror.cpp
	common/common_resolver.cpp
	common/common_resolvererror.cpp
	common/common_socket.cpp
)

target_include_directories(worms PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/client
    ${CMAKE_CURRENT_SOURCE_DIR}/server
)

# define targets
target_link_libraries(worms PUBLIC ${BOX2D_LIBRARY_PATH}  SDL2pp::SDL2pp)
