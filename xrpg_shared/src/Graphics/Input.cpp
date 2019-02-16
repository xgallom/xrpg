//
// Created by xgallom on 11. 2. 2019.
//

#include "Graphics/Input.h"

#include "Graphics/OutputBuffer.h"

#include <cmath>
#include <sstream>

namespace Input
{
	void text(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
			  size_t promptSize, const std::string &value, bool isActive)
	{
		write(pos, promptColor, prompt, promptSize);
		write(pos + Coords{static_cast<Coords::value_type>(promptSize), 0}, valueColor, value.c_str(), value.size());
		if(isActive) {
			write(
					pos + Coords{static_cast<Coords::value_type>(promptSize + value.size()), 0},
					Character(' ', valueColor.toBg())
			);
		}
	}

	void slider(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
				size_t promptSize, size_t strSize, int value, int min, int max)
	{
		const auto offset = 1 +
				static_cast<size_t>(std::round(static_cast<double>(strSize - 6) * (value - min) / (max - min)));

		std::string str(strSize, '-');
		str[0] = '(';
		str[strSize - 1] = static_cast<char>('0' + value % 10);
		str[strSize - 2] = static_cast<char>('0' + value / 10);
		str[strSize - 3] = ' ';
		str[strSize - 4] = ')';
		str[offset] = '#';

		write(pos, promptColor, prompt, promptSize);
		write(pos + Coords{static_cast<Coords::value_type>(promptSize), 0}, valueColor, str.c_str(), strSize);
	}

	void integer(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
				 size_t promptSize, int value, bool drawCursor)
	{
		std::stringstream ss;
		ss << value;

		auto str = ss.str();

		write(pos, promptColor, prompt, promptSize);
		write(pos + Coords{static_cast<Coords::value_type>(promptSize), 0}, valueColor, str.c_str(), str.size());
		if(drawCursor)
			write(pos + Coords{static_cast<Coords::value_type>(promptSize + str.size()), 0}, Character{' ', valueColor.toBg()});
	}

	void button(Coords pos, ColorAttribute color, const char text[], size_t textSize)
	{
		write(pos, color, text, textSize);
	}
}
