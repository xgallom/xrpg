//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_SERIALIZE_H
#define XRPG_SERIALIZE_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include "Storage/Level.h"
#include "Storage/Save.h"

using IArchive = cereal::BinaryInputArchive;
using OArchive = cereal::BinaryOutputArchive;

void save(OArchive &ar, const Stat &d);
void load(IArchive &ar, Stat &d);

void save(OArchive &ar, const Player &d);
void load(IArchive &ar, Player &d);

void save(OArchive &ar, const Save &d);
void load(IArchive &ar, Save &d);

void save(OArchive &ar, const Coords &d);
void load(IArchive &ar, Coords &d);

void save(OArchive &ar, const Character &d);
void load(IArchive &ar, Character &d);

void save(OArchive &ar, const Map &d);
void load(IArchive &ar, Map &d);

void save(OArchive &ar, const Level &d);
void load(IArchive &ar, Level &d);

#endif //XRPG_SERIALIZE_H
