//
// Created by xgallom on 2/16/19.
//

#include "NewMap.h"

#include "Context/GlobalContext.h"
#include "Editor.h"

#include <Data/Map.h>
#include <Graphics/Border.h>
#include <Graphics/Coords.h>
#include <Graphics/Input.h>
#include <Graphics/OutputBuffer.h>
#include <Util/Numeric.h>

namespace Run
{
	enum Index {
		Width,
		Height,

		Accept,
		Cancel,

		Size
	};
	static constexpr auto First = Width, Last = Cancel;

	static constexpr Coords InputSize = {24, 4};
	static constexpr size_t PromptSize = 12, MaxSize = 12;

	static constexpr char Prompts[][PromptSize + 1] = {
			"     Width: ",
			"    Height: ",

			"   Accept   ",
			"   Cancel   "
	};

	static int s_activeIndex = First;
	static auto s_mapSize = Coords{};

	static void handle(int input);

	void NewMap::render()
	{
		const auto tl = center(InputSize);
		const auto ctr = tl + Coords{PromptSize, 0};
		const auto region = Region{tl - Coords{1, 1}, tl + InputSize + Coords{1, 3}};

		OutputBuffer::clear(region);
		border(region);

		Input::integer(
				tl + Coords{0, 1},
				Color::White,
				s_activeIndex == Width ? Color::LWhite : Color::White,
				Prompts[Width],
				PromptSize,
				s_mapSize.x
		);
		Input::integer(
				tl + Coords{0, 2},
				Color::White,
				s_activeIndex == Height ? Color::LWhite : Color::White,
				Prompts[Height],
				PromptSize,
				s_mapSize.y
		);

		Input::button(
			tl + Coords{0, 4},
			s_activeIndex == Accept ? Color::LWhite : Color::White,
			Prompts[Accept],
			PromptSize
		);
		Input::button(
			ctr + Coords{0, 4},
			s_activeIndex == Cancel ? Color::LWhite : Color::White,
			Prompts[Cancel],
			PromptSize
		);
	}

	void NewMap::update(int c)
	{
		switch(c) {
			case 's':
			case 'd':
			case '<':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			case 'w':
			case 'a':
			case '>':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			default:
				handle(c);
				break;
		}
	}

	void NewMap::transit()
	{
		GlobalContext::state() = GlobalState::NewMap;
		s_activeIndex = First;
		s_mapSize = GlobalContext::map().size;
	}

	static void handle(int input)
	{
		switch(s_activeIndex) {
			case Width:
				Numeric::update<Coords::value_type, 0, 1024>(s_mapSize.x, input);
				break;

			case Height:
				Numeric::update<Coords::value_type, 0, 1024>(s_mapSize.y, input);
				break;

			case Accept:
				GlobalContext::map() = Map(s_mapSize);
				[[fallthrough]];

			case Cancel:
				Editor::transit();
				break;
		}
	}
}
