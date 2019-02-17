//
// Created by xgallom on 10. 2. 2019.
//

#include "Graphics/OutputBuffer.h"

#include "Console/Console.h"

#include <vector>
#include <cmath>

namespace OutputBuffer
{
	static Coords s_size = {}, s_targetSize;
	static std::vector<Character> s_buffer, s_real;

	static void resize();

	bool init(Coords size, bool enableDebug)
	{
		if(!Console::init(enableDebug))
			return false;

		s_targetSize = size;

		resize();

		return true;
	}

	void deinit()
	{
		Console::deinit();
	}

	void clear()
	{
		for(auto &buf : s_buffer)
			buf = Character{};
	}

	void clear(Region region)
	{
		for(auto y = region.tl.y; y < region.br.y; ++y) {
			for(auto x = region.tl.x; x < region.br.x; ++x)
				at({x, y}) = Character{};
		}
	}

	void update()
	{
		resize();

		Coords coords;

		auto buf = s_buffer.cbegin();
		auto real = s_real.begin();

		const auto tl = center(Console::size(), s_size);
		const auto br = tl + s_size;

		bool modified = false;

		for(coords.y = tl.y; coords.y < br.y; ++coords.y) {
			for(coords.x = tl.x; coords.x < br.x; ++coords.x) {
				if(*real != *buf) {
					modified = true;
					*real = *buf;

					const auto value = static_cast<char>(buf->value & 0xff);

					Console::setPos(coords);
					Console::color(static_cast<ColorAttribute::value_type>(buf->value >> 8));
					Console::write(value ? value : ' ');
				}

				++real;
				++buf;
			}
		}

		if(modified)
			Console::flush();
	}

	Coords size()
	{
		return s_size;
	}

	Character &at(size_t index)
	{
		return s_buffer[index];
	}

	Character &at(Coords coords)
	{
		return at(static_cast<size_t>(coords.y * s_size.x + coords.x));
	}

	static void resize()
	{
		static Coords oldConsoleSize;
		const auto consoleSize = Console::size();

		Coords size = s_targetSize;

		if(!size)
			size = consoleSize;
		else if(size.x > consoleSize.x || size.y > consoleSize.y) {
			const auto aspect = size.aspect();
			const auto consoleAspect = consoleSize.aspect();

			if(aspect >= consoleAspect) {
				size.x = consoleSize.x;
				size.y = static_cast<Coords::value_type>(std::round(size.x / aspect));
			}
			else {
				size.y = consoleSize.y;
				size.x = static_cast<Coords::value_type>(std::round(size.y * aspect));
			}
		}

		static const auto refresh = []() {
			Console::cls();

			for(auto &real : s_real)
				real = Character{};
		};

		if(size != s_size) {
			s_size = size;

			const auto total = size.area();

			s_buffer.resize(total, Character{});
			s_real.resize(total, Character{});

			refresh();
		}
		else if(consoleSize != oldConsoleSize)
			refresh();

		oldConsoleSize = consoleSize;
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
