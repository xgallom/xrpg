# xrpg
# Copyright (C) 2021 Milan Gallo <gallo.milan.jr@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 2.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.21)
project(xrpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wall -Wextra -Wnon-virtual-dtor -pedantic \
-Wold-style-cast -Wcast-align -Wunused -Wpedantic \
-Wconversion -Wsign-conversion -Wformat=2 \
-fno-exceptions -fno-rtti \
-march=native -finline-functions -m64 -funroll-loops \
")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
-Og \
")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
-O3 \
")

add_definitions(-DSDL_MAIN_HANDLED)

add_subdirectory(sdl2)
add_subdirectory(sdl2-image)
add_subdirectory(sdl2-mixer)
add_subdirectory(cereal)
add_subdirectory(xrpg-assets)
add_subdirectory(xrpg-shared)
add_subdirectory(xrpg)
