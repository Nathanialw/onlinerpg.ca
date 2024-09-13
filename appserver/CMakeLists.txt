cmake_minimum_required(VERSION 3.17)
project(BrowserRPG)

#websocketpp will currently only compile with C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(src/networking)
include_directories(src/map)
include_directories(src/objects/units)
include_directories(src/objects/units/class)

add_executable(BrowserRPG

        src/server/main.cpp

        src/networking/receiving.cpp

        src/camera/camera.cpp
        src/map/map.cpp
        src/objects/units/units.cpp
        src/utils/utils.cpp
        src/objects/collision/collision.cpp

        src/objects/units/class/warrior.cpp
        src/objects/movement/movement.cpp
)
