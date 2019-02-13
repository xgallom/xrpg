//
// Created by xgallom on 11. 2. 2019.
//

#include "NewGame.h"

#include "Context/GlobalContext.h"

#include <Console/ConsoleInput.h>
#include <Data/Player.h>
#include <Graphics/Border.h>
#include <Graphics/OutputBuffer.h>
#include <Graphics/Input.h>
#include <Util/Numeric.h>
#include <Util/String.h>

namespace Run {
	enum Index {
		Name = 0,
		Strength,
		Agility,
		Stamina,

		Accept,
		Cancel,

		Size
	};
	static constexpr auto First = Name, Last = Cancel, Remaining = Size;

	static constexpr Coords InputSize = {24, 9};
	static constexpr size_t PromptSize = 12, MaxSize = 12;

	static constexpr char Prompts[][PromptSize + 1] = {
			"Name:       ",
			"Strength:   ",
			"Agility:    ",
			"Stamina:    ",

			"   Accept   ",
			"   Cancel   ",

			"Remaining:  "
	};

	static constexpr auto Total = 40, Initial = Total - 3 * AttribDefault, Max = Total - 3 * AttribMin;

	static int s_activeIndex = Name;
	static int s_remaining = Initial;

	static void handle(int input);
	static ColorAttribute color(bool primary);

	template<Index I>
	static void slider(attribute value, Coords tl)
	{
		const auto color = Color{
			value <= AttribWeak ? Color::Red : (value >= AttribStrong ? Color::Green : Color::White),
			s_activeIndex == I
		};

		Input::slider(
				tl + Coords{0, static_cast<Coords::value_type>(3 + I)},
				Color::White,
				color,
				Prompts[I],
				PromptSize,
				MaxSize,
				value,
				AttribMin,
				AttribMax
		);
	}

	void NewGame::render()
	{
		border();

		const auto tl = center(InputSize);
		const auto ctr = tl + Coords{PromptSize, 0};

		const auto &player = GlobalContext::player();
		const auto &name = player.name;
		const auto &attrib = player.attrib;

		Input::text(
				tl,
				Color::White,
				s_activeIndex == Name ? Color::LWhite : Color::White,
				Prompts[Name],
				PromptSize, name
		);
		write(
				ctr + Coords{static_cast<Coords::value_type>(name.size()), 0},
				Character(' ', ColorAttribute::Background(s_activeIndex == Name ? Color::LWhite : Color::Black))
		);

		Input::slider(
				tl + Coords{0, 2},
				Color::White,
				Color::White,
				Prompts[Remaining],
				PromptSize,
				MaxSize,
				s_remaining,
				0,
				Max
		);

		slider<Strength>(attrib.str, tl);
		slider<Agility> (attrib.agi, tl);
		slider<Stamina> (attrib.sta, tl);

		Input::button(
				tl + Coords{0, 8},
				Color{name.empty() ? Color::Red : Color::White, s_activeIndex == Accept},
				Prompts[Accept],
				PromptSize
		);
		Input::button(
				tl + Coords{PromptSize, 8},
				color(s_activeIndex == Cancel),
				Prompts[Cancel],
				PromptSize
		);
	}

	void NewGame::update()
	{
		const auto input = Console::get();

		switch(input) {
			case '8':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			case '2':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			default:
				handle(input);
				break;
		}
	}

	static void handle(int input)
	{
		auto &player = GlobalContext::player();
		auto &name = player.name;
		auto &attrib = player.attrib;

		switch(s_activeIndex) {
			case Name:
				String::update<MaxSize, String::isChar>(name, input);
				break;

			case Strength:
				Numeric::update<attribute, AttribMin, AttribMax>(attrib.str, input, s_remaining);
				break;

			case Agility:
				Numeric::update<attribute, AttribMin, AttribMax>(attrib.agi, input, s_remaining);
				break;

			case Stamina:
				Numeric::update<attribute, AttribMin, AttribMax>(attrib.sta, input, s_remaining);
				break;

			case Accept:
				if(!name.empty()) {
					GlobalContext::state() = GlobalState::LoadLevel;
				}
				break;

			case Cancel:
				GlobalContext::state() = GlobalState::MainMenu;
				break;
		}
	}

	static ColorAttribute color(bool primary)
	{
		return primary ? Color::LWhite : Color::White;
	}
}
