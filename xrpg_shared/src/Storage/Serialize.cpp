//
// Created by xgallom on 11. 2. 2019.
//

#include "Serialize.h"

void save(OArchive &ar, const Stat &d) { ar(d.val, d.max); }
void load(IArchive &ar, Stat &d) { ar(d.val, d.max); }

void save(OArchive &ar, const Player &d) { ar(d.name, d.pos, d.hp, d.xp); }
void load(IArchive &ar, Player &d) { ar(d.name, d.hp, d.xp); }

void save(OArchive &ar, const Save &d) { ar(d.player); }
void load(IArchive &ar, Save &d) { ar(d.player); }

void save(OArchive &ar, const Coords &d) { ar(d.x, d.y); }
void load(IArchive &ar, Coords &d) { ar(d.x, d.y); }

void save(OArchive &ar, const Character &d) { ar(d.value); }
void load(IArchive &ar, Character &d) { ar(d.value); }

void save(OArchive &ar, const Map &d) { ar(d.size, d.data); }
void load(IArchive &ar, Map &d) { ar(d.size, d.data); }

void save(OArchive &ar, const Level &d) { ar(d.map); }
void load(IArchive &ar, Level &d) { ar(d.map); }

void save(OArchive &ar, const Settings &d) { ar(d.audioLevelMaster, d.audioLevelMusic, d.audioLevelSound); }
void load(IArchive &ar, Settings &d) { ar(d.audioLevelMaster, d.audioLevelMusic, d.audioLevelSound); }

