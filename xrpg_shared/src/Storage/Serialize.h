//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_SERIALIZE_H
#define XRPG_SERIALIZE_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>

#include "Storage/Save.h"

using IArchive = cereal::BinaryInputArchive;
using OArchive = cereal::BinaryOutputArchive;

void save(OArchive &ar, const Stat &d) { ar(d.val, d.max); }
void load(IArchive &ar, Stat &d) { ar(d.val, d.max); }

void save(OArchive &ar, const Player &d) { ar(d.name, d.hp, d.xp); }
void load(IArchive &ar, Player &d) { ar(d.name, d.hp, d.xp); }

void save(OArchive &ar, const Save &d) { ar(d.player); }
void load(IArchive &ar, Save &d) { ar(d.player); }

#endif //XRPG_SERIALIZE_H
