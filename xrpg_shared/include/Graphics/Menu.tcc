//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_MENU_TCC
#define XRPG_MENU_TCC

#include "Menu.h"

template<size_t M, size_t N>
void Menu<M, N>::render(int activeIndex) const
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

#endif //XRPG_MENU_TCC
