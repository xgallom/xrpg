//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_MENU_TCC
#define XRPG_MENU_TCC

#include "Menu.h"

template<size_t M, size_t N>
void Menu<M, N>::renderCenter(int activeIndex) const
{
	constexpr Coords size = {EntrySize, Size};

	const auto tl = center(size);

	Coords::value_type i = 0;
	for(const auto &menuEntry : *this) {
		Character ch[EntryBufSize];

		int n = 0;
		for(const auto c : menuEntry)
			ch[n++] = Character(c, activeIndex == i ? Color::LWhite : Color::White);

		write(tl + Coords{0, i}, ch, EntrySize);

		++i;
	}
}

template<size_t M, size_t N>
void Menu<M, N>::renderHorizontal(Coords pos, int activeIndex) const
{
	Coords::value_type i = 0;
	for(const auto &menuEntry : *this) {
		Character ch[EntryBufSize];

		int n = 0;
		for(const auto c : menuEntry)
			ch[n++] = Character(c, activeIndex == i ? Color::LBlue : Color::White);

		write(pos + Coords{static_cast<Coords::value_type>(i * EntrySize), 0}, ch, EntrySize);

		++i;
	}
}


#endif //XRPG_MENU_TCC
