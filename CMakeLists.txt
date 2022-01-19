cmake_minimum_required(VERSION 3.21)
project(xrpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

find_package(SDL2 REQUIRED)

message(${SDL2_LIBRARIES})
#include_directories("../SDL2-2.0.20/x86_64-w64-mingw32/include")
#link_directories("../SDL2-2.0.20/x86_64-w64-mingw32/lib")

add_executable(xrpg main.cpp)
target_link_libraries(xrpg ${SDL2_LIBRARIES})
add_definitions(-DSDL_MAIN_HANDLED)
