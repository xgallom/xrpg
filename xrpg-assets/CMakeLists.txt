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

add_custom_target(xrpg-assets ALL
        COMMAND ${CMAKE_COMMAND}
        -D XRPG_ASSETS_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
        -D XRPG_ASSETS_BINARY_DIR="${CMAKE_BINARY_DIR}/xrpg/"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/copy-assets.cmake"
        )
