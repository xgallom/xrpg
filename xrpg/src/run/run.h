// xrpg
// Copyright (C) 2022 Milan Gallo <gallo.milan.jr@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//
// Created by Milan Gallo on 20/01/2022.
//

#ifndef XRPG_XRPG_SRC_RUN_RUN_H
#define XRPG_XRPG_SRC_RUN_RUN_H

#include "init.h"

namespace run {
    static constexpr engine::RunHandler XrpgRunHandlers[] = {
            start,
            quit,
    };
}

#endif //XRPG_XRPG_SRC_RUN_RUN_H
