//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_BORDER_H
#define XRPG_BORDER_H

#include "Color.h"
#include "Coords.h"

void border(ColorAttribute colorAttribute = ColorAttribute::Background(Color::White));
void border(Region region, ColorAttribute colorAttribute = ColorAttribute::Background(Color::White));

#endif //XRPG_BORDER_H
