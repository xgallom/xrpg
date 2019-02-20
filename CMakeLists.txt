cmake_minimum_required(VERSION 3.11)
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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(data)

add_subdirectory(xrpg_edit)
add_subdirectory(xrpg)
