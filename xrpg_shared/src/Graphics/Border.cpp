//
// Created by xgallom on 11. 2. 2019.
//

#include "Graphics/Border.h"

#include "Graphics/OutputBuffer.h"

static void row(Coords tl, Coords::value_type length, Character ch)
{
	while(length--) {
		write(tl, ch);

		++tl.x;
	}
}

static void cols(Coords tl, Coords::value_type length, Character ch)
{
	write(tl, ch);
	write(tl + Coords{static_cast<Coords::value_type>(length - 1), 0}, ch);
}

void border(ColorAttribute colorAttribute)
{
	border({{0, 0}, OutputBuffer::Size - Coords{0, 0}}, colorAttribute);
}

void border(Region region, ColorAttribute colorAttribute)
{
	const Coords size = region.size();
	const Character ch(' ', colorAttribute);

	row(region.tl, size.x, ch);

	while(region.tl.y < region.br.y - 1) {
		region.tl.y++;

		cols(region.tl, size.x, ch);
	}

	row(region.tl, size.x, ch);
}

