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

# YAML
add_subdirectory(third-party/yaml-cpp)
set(YAML_CPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/yaml-cpp/include")
include_directories(${YAML_CPP_INCLUDE_DIR})

set(BOX2D_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libbox2d.a")  
set(BOX2D_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/Box2D") 

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(PRIVATE ${BOX2D_INCLUDE_PATH})
# Find the QtWidgets library

include(FetchContent)
FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
)

FetchContent_MakeAvailable(googletest)

qt5_wrap_ui(UIS_HEADERS
  src/client/lobby/join_game_dialog.ui
  src/client/lobby/mainwindow.ui
  src/client/lobby/new_game_dialog.ui
  src/client/lobby/connectdialog.ui
)
# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)

# Source files del cliente menos el main
set(CLIENT_SOURCE
	src/client/client_client.cpp
	src/client/client_protocol.cpp
	src/client/client_sender.cpp
	src/client/client_receiver.cpp
	src/common/common_liberror.cpp
	src/common/common_resolver.cpp
	src/common/common_resolvererror.cpp
	src/common/common_socket.cpp
	src/common/common_baseprotocol_socket.cpp
	src/client/commands/client_move.cpp
	src/client/commands/client_command.cpp
	src/client/commands/client_stop_moving.cpp
	src/client/game/estado_juego.cpp
	src/client/game/worm.cpp
	src/client/game/beam.cpp
	src/client/game/scenario.cpp
	src/client/lobby/lobby_state.cpp
	# lobby QT
	src/client/lobby/join_game_dialog.cpp
	src/client/lobby/mainwindow.cpp
	src/client/lobby/new_game_dialog.cpp
	src/client/lobby/connectdialog.cpp
	# graphics
	src/client/graphics/animation.cpp
	src/client/graphics/player.cpp
	src/client/graphics/scenario_beam.cpp
	src/client/graphics/texture_controller.cpp
	src/client/graphics/worldview.cpp
	${UIS_HEADERS}
	src/common/common_log.cpp
	src/client/commands/client_jump.cpp
	src/client/commands/client_rollback.cpp
	src/client/game/ground.cpp
	src/client/graphics/entity.cpp
	src/client/game/entity_info.cpp
	src/client/game/ground.cpp
	src/client/graphics/entities_factory.cpp
		src/client/graphics/ground_entity.cpp
	src/client/client_event_handler.cpp
	src/client/commands/client_aim.cpp
	src/client/commands/client_stop_aim.cpp
	src/client/commands/client_fire.cpp
	src/client/game/proyectil.cpp
	src/client/graphics/proyectil_entity.cpp
	src/common/common_baseprotocol.cpp
	src/common/common_baseprotocol.h
	src/client/lobby/gameinfo.cpp
	src/client/lobby/gameinfo.h
	src/client/lobby/gameinfo_view.cpp
	src/client/lobby/gameinfo_view.h
	src/client/commands/client_power_attack.cpp
	src/client/commands/client_power_attack.h
	src/client/graphics/weapons/weapon.cpp
	src/client/graphics/weapons/bazooka.cpp
	src/client/graphics/weapons/weapon_factory.cpp
	src/client/graphics/crosshair.cpp
	configuration/configuration.cpp
	configuration/weapon_info.cpp
	)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable(client 
	src/client/client_main.cpp
	${CLIENT_SOURCE}
)

add_executable(server
	src/server/server_main.cpp
	src/server/server_server.cpp
	src/server/server_protocol.cpp
	src/server/server_client.cpp
	src/server/game/server_sender.cpp
	src/server/server_accepter.cpp
	src/common/common_liberror.cpp
	src/common/common_resolver.cpp
	src/common/common_resolvererror.cpp
	src/common/common_socket.cpp
	src/common/common_baseprotocol_socket.cpp
	src/server/game/server_game.cpp
	src/server/lobby/server_lobby.cpp
	src/server/server_clientstate.cpp
	src/server/game/server_clientstate_game.cpp
	src/server/lobby/server_clientstate_lobby.cpp
	src/server/lobby/server_lobby_request.cpp
	src/server/lobby/server_lobby_answer.cpp
	src/server/game/server_gameinfo.cpp
	src/server/game/server_gameevent.cpp
	src/server/game/server_statusbroadcast_monitor.cpp
	src/server/game/server_event_handler.cpp
	src/server/game/server_gamestatus.cpp
	src/server/game/entities/server_worm.cpp
	src/server/game/world/server_gameworld.cpp
	src/server/game/entities/server_beam.cpp
	src/server/game/entities/server_worm_info.cpp
	src/server/game/entities/server_beam_info.cpp
	src/common/common_log.cpp
	src/server/game/entities/server_gameobject.cpp
	src/server/game/listeners/server_onfloor_contactlistener.cpp
	src/server/game/entities/server_worm_sensor.cpp
	src/server/game/entities/server_ground.cpp
	src/server/game/states/server_state_manager.cpp
	src/server/game/states/server_states.cpp
	src/server/game/states/server_state.cpp
	src/server/game/entities/server_gameobject_info.cpp
	src/server/game/entities/server_ground_info.cpp
	src/server/game/entities/server_worm_sensor_info.cpp
	src/server/game/weapons/server_weapon.cpp
	src/server/game/weapons/server_bazooka_proyectil.cpp
	src/server/game/weapons/bazooka_proyectil_info.cpp
	src/server/server_game_reaper.cpp
	src/server/game/listeners/server_raycast_explosion_callback.cpp
	configuration/configuration.cpp
	configuration/weapon_info.cpp
		src/server/scenario_filehandler.cpp
		src/server/scenario_filehandler.h
)

target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client
	${CMAKE_CURRENT_SOURCE_DIR}/test

)

target_include_directories(server PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src/common
		${CMAKE_CURRENT_SOURCE_DIR}/src/server
		${CMAKE_CURRENT_SOURCE_DIR}/test

)


# define targets
target_link_libraries(client PUBLIC ${BOX2D_LIBRARY_PATH}
					SDL2pp::SDL2pp
					Qt5::Widgets
					Qt5::Core
					yaml-cpp)
target_link_libraries(server PUBLIC ${BOX2D_LIBRARY_PATH} yaml-cpp)

add_executable(hello_test
		test/hello_test.cc
		src/common/common_baseprotocol_mock.cpp

		src/server/server_protocol.cpp
		src/server/lobby/server_lobby_request.cpp
		src/server/server_server.cpp
		src/server/server_protocol.cpp
		src/server/server_client.cpp
		src/server/game/server_sender.cpp
		src/server/server_accepter.cpp
		src/common/common_liberror.cpp
		src/common/common_resolver.cpp
		src/common/common_resolvererror.cpp
		src/common/common_socket.cpp
		src/common/common_baseprotocol_socket.cpp
		src/server/game/server_game.cpp
		src/server/lobby/server_lobby.cpp
		src/server/server_clientstate.cpp
		src/server/game/server_clientstate_game.cpp
		src/server/lobby/server_clientstate_lobby.cpp
		src/server/lobby/server_lobby_request.cpp
		src/server/lobby/server_lobby_answer.cpp
		src/server/game/server_gameinfo.cpp
		src/server/game/server_gameevent.cpp
		src/server/game/server_statusbroadcast_monitor.cpp
		src/server/game/server_event_handler.cpp
		src/server/game/server_gamestatus.cpp
		src/server/game/entities/server_worm.cpp
		src/server/game/world/server_gameworld.cpp
		src/server/game/entities/server_beam.cpp
		src/server/game/entities/server_worm_info.cpp
		src/server/game/entities/server_beam_info.cpp
		src/common/common_log.cpp
		src/server/game/entities/server_gameobject.cpp
		src/server/game/listeners/server_onfloor_contactlistener.cpp
		src/server/game/entities/server_worm_sensor.cpp
		src/server/game/entities/server_ground.cpp
		src/server/game/states/server_state_manager.cpp
		src/server/game/states/server_states.cpp
		src/server/game/states/server_state.cpp
		src/server/game/entities/server_gameobject_info.cpp
		src/server/game/entities/server_ground_info.cpp
		src/server/game/entities/server_worm_sensor_info.cpp
		src/server/game/weapons/server_weapon.cpp
		src/server/game/weapons/server_bazooka_proyectil.cpp
		src/server/game/weapons/bazooka_proyectil_info.cpp
		src/server/server_game_reaper.cpp
		src/server/game/listeners/server_raycast_explosion_callback.cpp
		configuration/configuration.cpp
		configuration/weapon_info.cpp
)

target_link_libraries(hello_test GTest::gtest_main GTest::gmock ${BOX2D_LIBRARY_PATH} yaml-cpp)

target_include_directories(hello_test PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src/common
		${CMAKE_CURRENT_SOURCE_DIR}/src/server
		${CMAKE_CURRENT_SOURCE_DIR}/test
)
add_test(NAME asd COMMAND hello_test)


# Tests del cliente
add_executable(client_test
	test/client_test.cc
	${CLIENT_SOURCE}
)

target_include_directories(client_test PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src/common
		${CMAKE_CURRENT_SOURCE_DIR}/src/client
		${CMAKE_CURRENT_SOURCE_DIR}/test
)

target_link_libraries(client_test PUBLIC GTest::gtest_main GTest::gmock SDL2pp::SDL2pp Qt5::Widgets Qt5::Core yaml-cpp)

add_test(NAME ClientTest COMMAND client_test)