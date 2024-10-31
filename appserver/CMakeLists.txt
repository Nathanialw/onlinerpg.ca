cmake_minimum_required(VERSION 3.17)
project(BrowserRPG)

#websocketpp will currently only compile with C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(libs/sqlite3)
include_directories(libs/websocketpp)
include_directories(libs)

include_directories(src/db)
include_directories(src/networking)
include_directories(src/map)
include_directories(src/game)
include_directories(src/procgen)
include_directories(src/server)
include_directories(src/utils)
include_directories(src/objects)
include_directories(src/objects/units)
include_directories(src/objects/actions)
include_directories(src/objects/collision)
include_directories(src/objects/movement)
include_directories(src/objects/items)
include_directories(src/objects/movement/pathing)
include_directories(src/objects/units/class)
include_directories(src/objects/units/species)
include_directories(src/objects/units/classes)
include_directories(src/objects/items/use_effects)



set(SOURCES
        libs/sqlite3/sqlite3.c

        src/server/main.cpp
        src/server/server.cpp

        src/db/db.cpp
        src/game/game.cpp

        src/utils/utils.cpp
        src/utils/files.cpp

        src/networking/receiving.cpp
        src/networking/send.cpp

        src/camera/camera.cpp

        src/map/map.cpp
        src/map/labyrinth.cpp
        src/map/chunk.cpp

        src/objects/movement/movement.cpp
        src/objects/movement/pathing.cpp

        src/objects/units/class/warrior.cpp
        src/objects/units/player.cpp
        src/objects/units/units.cpp
        src/objects/units/update.cpp
        src/objects/units/species/goblin.cpp
        src/objects/units/spawn.cpp

        src/objects/items/loot.cpp
        src/objects/items/items.cpp
        src/objects/items/inventory.cpp
        src/objects/items/equipment.cpp
        src/objects/items/backpack.cpp
        src/objects/items/update_items.cpp
        src/objects/items/modifiers.cpp
        src/objects/items/use.cpp

        src/objects/actions/attack.cpp
        src/objects/actions/death.cpp
        src/objects/components.cpp
        src/objects/collision/collision.cpp

        src/abilities/debuffs/Disease.cpp

        src/procgen/procgen.cpp
        src/objects/units/classes/unit.cpp
        src/objects/items/use_effects/use_effects.cpp
)

add_executable(BrowserRPG ${SOURCES})

target_include_directories(BrowserRPG PRIVATE
        libs/sqlite3
        libs/websocketpp
        libs/websocketpp/config
)