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

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Development")
endif()

set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/configuration/configuration.yaml")
set(SCENARIO_FILE "${CMAKE_SOURCE_DIR}/scenarios/scenarios.yaml")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets/")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CONFIG_FILE "/etc/worms/configuration.yaml")
	set(SCENARIO_FILE "/etc/worms/scenarios.yaml")
	set(ASSETS_DIR "/etc/worms/assets/")
endif()

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(worms LANGUAGES CXX)

find_package(SDL2pp REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# YAML
add_subdirectory(third-party/yaml-cpp)
set(YAML_CPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/yaml-cpp/include")
include_directories(${YAML_CPP_INCLUDE_DIR})

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${BOX2D_INCLUDE_PATH})
# Find the QtWidgets library

include(FetchContent)

FetchContent_Declare(
		box2d
		GIT_REPOSITORY https://github.com/erincatto/box2d.git
		GIT_TAG 411acc32eb6d4f2e96fc70ddbdf01fe5f9b16230
)
FetchContent_MakeAvailable(box2d)

if(CMAKE_BUILD_TYPE STREQUAL "Development")
	FetchContent_Declare(
			googletest
			URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
	)
	FetchContent_MakeAvailable(googletest)
endif()

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

# Source files

set(CLIENT_SOURCE_FILES
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
		src/client/lobby/resources.qrc
		# graphics
		src/client/graphics/animation.cpp
		src/client/graphics/player.cpp
		src/client/graphics/scenario_beam.cpp
		src/client/graphics/texture_controller.cpp
		src/client/graphics/worldview.cpp
		src/client/graphics/hud.cpp
		${UIS_HEADERS}
		src/common/common_log.cpp
		src/client/commands/client_jump.cpp
		src/client/commands/client_rollback.cpp
		src/client/game/ground.cpp
		src/client/graphics/entity.cpp
		src/client/game/entity_info.cpp
		src/client/game/explosion.cpp
		src/client/game/ground.cpp
		src/client/game/aim_info.cpp
		src/client/graphics/entities_factory.cpp
		src/client/graphics/ground_entity.cpp
		src/client/client_event_handler.cpp
		src/client/commands/client_aim.cpp
		src/client/commands/client_stop_aim.cpp
		src/client/commands/client_fire.cpp
		src/client/game/projectile.cpp
		src/client/graphics/projectile_entity.cpp
		src/client/graphics/explosion_entity.cpp
		src/common/common_baseprotocol.cpp
		src/client/lobby/gameinfo.cpp
		src/client/lobby/gameinfo.h
		src/client/lobby/gameinfo_view.cpp
		src/client/commands/client_power_attack.cpp
		src/client/commands/client_power_attack.h
		src/client/commands/change_weapon.cpp
		src/client/commands/change_countdown.cpp
		src/client/graphics/weapons/weapon.cpp
		src/client/graphics/weapons/bazooka.cpp
		src/client/graphics/weapons/red_grenade.cpp
		src/client/graphics/weapons/green_grenade.cpp
		src/client/graphics/weapons/holy_grenade.cpp
		src/client/graphics/weapons/mortar.cpp
		src/client/graphics/weapons/banana.cpp
		src/client/graphics/wind.cpp
		src/client/graphics/weapons/baseball_bat.cpp
		src/client/graphics/weapons/dynamite.cpp
		src/client/graphics/weapons/weapon_factory.cpp
		src/client/graphics/crosshair.cpp
		configuration/configuration.cpp
		configuration/weapon_info.cpp
		src/client/graphics/weapons/weapon_selector.cpp
		src/client/sound/sound_controller.cpp
		src/client/graphics/weapons/teleportation.cpp
		src/client/graphics/weapons/airstrike.cpp
		src/client/game/provision.cpp
		src/client/graphics/provision_entity.cpp
)

set(SERVER_SOURCE_FILES
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
		src/server/lobby/server_lobby_response.cpp
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
		src/server/game/listeners/server_contact_listener.cpp
		src/server/game/entities/server_worm_sensor.cpp
		src/server/game/entities/server_ground.cpp
		src/server/game/states/server_state_manager.cpp
		src/server/game/states/server_states.cpp
		src/server/game/states/server_state.cpp
		src/server/game/entities/server_gameobject_info.cpp
		src/server/game/entities/server_ground_info.cpp
		src/server/game/entities/server_worm_sensor_info.cpp
		src/server/game/entities/server_boundary.cpp
		src/server/game/weapons/server_weapon.cpp
		src/server/game/projectiles/server_projectile.cpp
		src/server/game/projectiles/server_projectile_info.cpp
		src/server/server_game_reaper.cpp
		src/server/game/listeners/server_explosion_callback.cpp
		configuration/configuration.cpp
		configuration/weapon_info.cpp
		src/server/scenario_filehandler.cpp
		src/server/game/weapons/server_weapon_bazooka.cpp
		src/server/game/weapons/server_weapon_grenade.cpp
		src/server/game/projectiles/server_projectile.cpp
		src/server/game/projectiles/server_projectile_effect.cpp
		src/server/game/projectiles/server_projectile_effect_defaultexplosion.cpp
		src/server/game/projectiles/server_projectile_effect_noeffect.cpp
		src/server/game/weapons/server_weapon_factory.cpp
		src/server/game/weapons/server_weapon_mortar.cpp
		src/server/game/projectiles/server_projectile_effect_fragmentedexplosion.cpp
		src/server/game/weapons/server_weapon_info.cpp
		src/server/game/weapons/server_weapon_info_bazooka.cpp
		src/server/game/weapons/server_weapon_mortar_info.cpp
		src/server/game/weapons/server_weapon_info_grenade.cpp
		src/server/game/weapons/server_weapon_redgrenade.cpp
		src/server/game/weapons/server_weapon_info_redgrenade.cpp
		src/server/game/weapons/server_weapon_banana.cpp
		src/server/game/weapons/server_weapon_info_banana.cpp
		src/server/game/weapons/server_weapon_factory.cpp
		src/server/game/projectiles/server_projectile_launch_parabolic.cpp
		src/server/game/projectiles/server_projectile_launch.cpp
		src/server/game/weapons/server_weapon_holygrenade.cpp
		src/server/game/weapons/server_weapon_info_holygrenade.cpp
		src/server/game/weapons/server_weapon_dynamite.cpp
		src/server/game/projectiles/server_projectile_launch_inplace.cpp
		src/server/game/weapons/server_weapon_info_dynamite.cpp
		src/server/game/world/server_gameworld_interactive_state.cpp
		src/server/game/world/server_gameworld_state.cpp
		src/server/game/world/server_gameworld_simulationstate.cpp
		src/server/game/entities/server_explosion.cpp
		src/server/game/entities/server_explosion_info.cpp
		src/server/game/weapons/server_weapon_bat.cpp
		src/server/game/projectiles/server_melee_impact.cpp
		src/server/game/weapons/server_weapon_info_bat.cpp
		src/server/game/projectiles/server_melee_impact_info.cpp
		src/server/game/weapons/server_weapon_teleportation.cpp
		src/server/game/weapons/server_weapon_info_teleportation.cpp
		src/server/game/provisions/server_provision.cpp
		src/server/game/provisions/server_provision_factory.cpp
		src/server/game/provisions/server_provision_effect.cpp
		src/server/game/provisions/server_provision_effect_health.cpp
		src/server/game/provisions/server_provision_info.cpp
		src/server/game/listeners/server_raycast_floor_calbback.cpp
		src/server/game/provisions/server_provision_effect_explosion.cpp
		src/server/game/provisions/server_provision_effect_ammo.cpp
		src/server/game/world/server_player_manager.cpp
		src/server/game/world/server_player.cpp
		src/server/game/world/server_gameworld_state_waiting.cpp
		src/server/game/world/server_wind.cpp
		src/server/game/weapons/server_weapon_airattack.cpp
		src/server/game/weapons/server_weapon_info_airattack.cpp
		src/server/game/world/server_gameworld_state_finished.cpp
		src/server/game/entities/server_worm_collision_manager.cpp
		src/server/game/listeners/server_intersection_callback.cpp
)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable(client
	src/client/client_main.cpp
	${CLIENT_SOURCE_FILES}
)
target_compile_definitions(client PUBLIC ASSETS_PATH="${ASSETS_DIR}"
										CONFIG_PATH="${CONFIG_FILE}")

add_executable(server
	src/server/server_main.cpp
	${SERVER_SOURCE_FILES}
)

target_compile_definitions(server PUBLIC CONFIG_PATH="${CONFIG_FILE}"
										SCENARIO_PATH="${SCENARIO_FILE}"
)

# define targets
target_link_libraries(client PUBLIC
					SDL2pp::SDL2pp
					Qt5::Widgets
					Qt5::Core
					yaml-cpp)

target_link_libraries(server PUBLIC box2d  yaml-cpp)

target_include_directories(client PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src/common
		${CMAKE_CURRENT_SOURCE_DIR}/src/client
)

target_include_directories(server PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src/common
		${CMAKE_CURRENT_SOURCE_DIR}/src/server
)


if (CMAKE_BUILD_TYPE STREQUAL "Development")
	add_executable(hello_test
			test/hello_test.cc
			${SERVER_SOURCE_FILES}
	)

	target_compile_definitions(hello_test PUBLIC CONFIG_PATH="${CONFIG_FILE}"
			SCENARIO_PATH="${SCENARIO_FILE}"
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
	)

	target_include_directories(client_test PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/common
			${CMAKE_CURRENT_SOURCE_DIR}/src/client
			${CMAKE_CURRENT_SOURCE_DIR}/test
			${CLIENT_SOURCE_FILES}
	)

	target_compile_definitions(client_test PUBLIC ASSETS_PATH="${ASSETS_DIR}"
			CONFIG_PATH="${CONFIG_FILE}" )
	target_link_libraries(client_test PUBLIC GTest::gtest_main GTest::gmock SDL2pp::SDL2pp Qt5::Widgets Qt5::Core yaml-cpp)

	add_test(NAME ClientTest COMMAND client_test)
endif ()

#installer
INSTALL(TARGETS server client DESTINATION /usr/bin)
INSTALL(DIRECTORY assets DESTINATION /etc/worms)
INSTALL(FILES configuration/configuration.yaml scenarios/scenarios.yaml DESTINATION /etc/worms)
