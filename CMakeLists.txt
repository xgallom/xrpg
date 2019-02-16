cmake_minimum_required(VERSION 3.12)
project(xrpg)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wall \
-Wextra \
-Wshadow \
-Wnon-virtual-dtor \
-Wold-style-cast \
-Wcast-align \
-Wunused \
-Woverloaded-virtual \
-Wpedantic \
-Wsign-conversion \
-Wmisleading-indentation \
-Wduplicated-cond \
-Wlogical-op \
-Wnull-dereference \
-Wuseless-cast \
-Wdouble-promotion \
-Wformat=2 \
-Weffc++ \
-pedantic \
")


add_subdirectory(external)
add_subdirectory(xrpg_shared)
add_subdirectory(xrpg_edit)
add_subdirectory(xrpg)
