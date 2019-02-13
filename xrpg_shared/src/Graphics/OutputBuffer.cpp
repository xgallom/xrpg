//
// Created by xgallom on 10. 2. 2019.
//

#include <cstring>
#include "Graphics/OutputBuffer.h"

#include "Console/Console.h"

namespace OutputBuffer
{
	static constexpr size_t Total = static_cast<size_t>(Size.x * Size.y);

	static Character s_buffer[Total], s_real[Total];

	bool init()
	{
		return Console::init();
	}

	void clear()
	{
		for(auto &buf : s_buffer)
			buf = Character{};
	}

	void update()
	{
		Coords coords;

		const auto *buf = s_buffer;
		auto *real = s_real;

		const auto tl = center(Console::size(), Size);
		const auto br = tl + Size;

		for(coords.y = tl.y; coords.y < br.y; ++coords.y) {
			for(coords.x = tl.x; coords.x < br.x; ++coords.x) {
				if(*real != *buf) {
					*real = *buf;

					Console::setPos(coords);
					Console::color(static_cast<ColorAttribute::value_type>(buf->value >> 8));
					Console::write(static_cast<char>(buf->value & 0xff));
				}

				++real;
				++buf;
			}
		}
	}

	Character &at(size_t index)
	{
		return s_buffer[index];
	}

	Character &at(Coords coords)
	{
		return at(static_cast<size_t>(coords.y * Size.x + coords.x));
	}
}

void write(Coords pos, Character ch)
{
	OutputBuffer::at(pos) = ch;
}

void write(Coords pos, Character *ch, size_t size)
{
	auto *i = &OutputBuffer::at(pos);

	while(size--)
		*i++ = *ch++;
}

void write(Coords pos, ColorAttribute ca, const char *str, size_t size)
{
	for(size_t n = 0; n < size; ++n)
		write(pos + Coords{static_cast<Coords::value_type >(n), 0}, Character(str[n], ca));
}
