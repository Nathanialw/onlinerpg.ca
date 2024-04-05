cmake_minimum_required(VERSION 3.28)
project(BrowserRPG)

set(CMAKE_CXX_STANDARD 23)

include_directories(lib)
include_directories(src/networking)
include_directories(src/map)
include_directories(src/objects/units)

add_executable(BrowserRPG

        src/server/main.cpp

        src/networking/receiving.cpp


        src/map/map.cpp
        src/objects/units/units.cpp
        src/utils/utils.cpp
)
