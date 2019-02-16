//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_MENU_H
#define XRPG_MENU_H

#include "OutputBuffer.h"
#include "Border.h"

template<size_t N>
using MenuEntry = char[N];

template<size_t _Size, size_t _EntrySize>
struct Menu {
	static constexpr auto Size = _Size, EntrySize = _EntrySize, EntryBufSize = _EntrySize + 1;

	using const_iterator = const MenuEntry<EntryBufSize> *;

	const MenuEntry<EntryBufSize> entries[Size];

	constexpr const_iterator begin() const { return entries; }
	constexpr const_iterator end() const { return entries + Size; }

	constexpr size_t index(const_iterator i) const { return i - begin(); }

	void renderCenter(int activeIndex) const;
	void renderHorizontal(Coords pos, int activeIndex) const;
};

#include "Menu.tcc"

#endif //XRPG_MENU_H
