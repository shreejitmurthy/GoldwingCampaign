cmake_minimum_required(VERSION 3.28)
project(Main LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/raylib)

include_directories(vendor/)
include_directories(vendor/raylib/src/)
include_directories(src/Include)

add_executable(Main 
    src/main.cpp
    src/Source/AssetManager.cpp
    src/Source/Player.cpp
    src/Source/Game.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
