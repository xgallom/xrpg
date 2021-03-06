//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_COLOR_H
#define XRPG_COLOR_H

struct Color
{
	using value_type = unsigned char;

	enum Enum : unsigned char {
		Black = 0,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,
		LBlack,
		LRed,
		LGreen,
		LYellow,
		LBlue,
		LMagenta,
		LCyan,
		LWhite,
	};

	static const value_type Bright = LBlack;
	static const value_type Bits = 4;

	value_type value;

	constexpr Color(Enum v) : value(v) {}
	constexpr Color(Enum hue, bool bright)
			: value(static_cast<value_type>(hue | (bright ? Bright : 0)))
	{}
};

struct ColorAttribute
{
	using value_type = unsigned char;

	value_type value = 0;

	constexpr ColorAttribute() = default;
	constexpr ColorAttribute(value_type v) : value(v) {}

	constexpr ColorAttribute(Color fg, Color bg = Color::Black)
			: value(static_cast<value_type>(fg.value | (bg.value << Color::Bits)))
	{}

	static constexpr ColorAttribute Background(Color bg) { return ColorAttribute(bg, bg); }
	constexpr ColorAttribute toBg() const { return wholeFg() | (wholeFg() << 4); }

	constexpr value_type wholeFg() const { return value & static_cast<value_type>(0x0f); }
	constexpr value_type fg() const { return value & static_cast<value_type>(0x07); }
	constexpr value_type bg() const { return (value >> 4) & static_cast<value_type>(0x07); }

	constexpr bool brightFg() const { return (value & 0x08) != 0; }
	constexpr bool brightBg() const { return (value & 0x80) != 0; }
};

#endif //XRPG_COLOR_H
