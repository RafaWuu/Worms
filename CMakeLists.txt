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
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(BOX2D_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libbox2d.a")  
set(BOX2D_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/Box2D") 

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(PRIVATE ${BOX2D_INCLUDE_PATH})
# Find the QtWidgets library

qt5_wrap_ui(UIS_HEADERS
  src/client/lobby/join_game_dialog.ui
  src/client/lobby/mainwindow.ui 
  src/client/lobby/new_game_dialog.ui
)
# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable(client 
	src/client/client_main.cpp
	src/client/client_client.cpp
	src/client/client_protocol.cpp
	src/client/client_sender.cpp
	src/client/client_receiver.cpp
	src/common/common_liberror.cpp
	src/common/common_resolver.cpp
	src/common/common_resolvererror.cpp
	src/common/common_socket.cpp
	src/common/common_baseprotocol.cpp
	src/client/commands/client_move.cpp
	src/client/commands/client_command.cpp
	# lobby QT
	src/client/lobby/join_game_dialog.cpp
	src/client/lobby/mainwindow.cpp
	src/client/lobby/new_game_dialog.cpp
	${UIS_HEADERS}
)

add_executable(server
	src/server/server_main.cpp
	src/server/server_server.cpp
	src/server/server_protocol.cpp
	src/server/server_clienthandler.cpp
	src/server/server_receiver.cpp
	src/server/server_sender.cpp
	src/server/server_lobby.cpp
	src/common/common_liberror.cpp
	src/common/common_resolver.cpp
	src/common/common_resolvererror.cpp
	src/common/common_socket.cpp
	src/common/common_baseprotocol.cpp
)

target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server

)

# define targets
target_link_libraries(client PUBLIC ${BOX2D_LIBRARY_PATH}  
					SDL2pp::SDL2pp 
					Qt5::Widgets
					Qt5::Core)
