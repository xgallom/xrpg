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


find_package(SDL2 REQUIRED)

add_library(xrpg-sdl2 INTERFACE)
target_include_directories(xrpg-sdl2 INTERFACE ${SDL2_INCLUDE_DIRS})
target_link_libraries(xrpg-sdl2 INTERFACE ${SDL2_LIBRARIES})

add_definitions(-DSDL_MAIN_HANDLED)
