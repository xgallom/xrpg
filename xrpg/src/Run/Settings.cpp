//
// Created by xgallom on 2/19/19.
//

#include "Settings.h"
#include "MainMenu.h"

#include <Audio/AudioContext.h>
#include <Console/ConsoleInput.h>
#include <Context/GlobalContext.h>
#include <Graphics/Border.h>
#include <Graphics/OutputBuffer.h>
#include <Graphics/Input.h>
#include <Storage/Settings.h>
#include <Util/Numeric.h>
#include <Util/String.h>
#include <Storage/Storage.h>

namespace Run
{
	enum Index {
		Master = 0,
		Music,
		Sound,

		Accept,
		Cancel,

		Size
	};
	static constexpr auto First = Master, Last = Cancel;
	static constexpr auto
		Min  = Audio::AudioContext::AudioLevels::Min,
		Max  = Audio::AudioContext::AudioLevels::Max,
		Step = 5;

	static constexpr Coords InputSize = {30, 5};
	static constexpr size_t PromptSize = 15, MaxSize = 15;

	static constexpr char Prompts[][PromptSize + 1] = {
			"Master volume: ",
			"Music volume:  ",
			"Sound volume:  ",

			"   Accept   ",
			"   Cancel   ",
	};

	static int s_activeIndex = First;
	static ::Settings
		s_settings = {},
		s_oldSettings = {};

	static void handle(int input);
	static ColorAttribute color(bool primary);

	template<Index I>
	static void slider(int value, Coords tl)
	{
		const auto color = Color{
				Color::White,
				s_activeIndex == I
		};

		Input::slider(
				tl + Coords{0, static_cast<Coords::value_type>(I)},
				Color::White,
				color,
				Prompts[I],
				PromptSize,
				MaxSize,
				value,
				Min,
				Max
		);
	}

	void Settings::render()
	{
		border();

		const auto tl = center(InputSize);

		slider<Master>(s_settings.audioLevelMaster, tl);
		slider<Music> (s_settings.audioLevelMusic , tl);
		slider<Sound> (s_settings.audioLevelSound , tl);

		Input::button(
				tl + Coords{0, 4},
				color(s_activeIndex == Accept),
				Prompts[Accept],
				PromptSize
		);
		Input::button(
				tl + Coords{PromptSize, 4},
				color(s_activeIndex == Cancel),
				Prompts[Cancel],
				PromptSize
		);
	}

	void Settings::update()
	{
		const auto input = Console::getAsync();

		switch(input) {
			case 0: break;

			case 'w':
			case '8':
			case '<':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			case 's':
			case '2':
			case '>':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			default:
				handle(input);
				break;
		}
	}

	void Settings::transit()
	{
		GlobalContext::state() = GlobalState::Settings;
		s_activeIndex = First;
		s_oldSettings = s_settings = Storage::Settings::restore()();
	}

	static void handle(int input)
	{
		auto &levels = Audio::AudioContext::audioLevels();

		switch(s_activeIndex) {
			case Master:
				Numeric::updateWithStep<int, Min, Max, Step>(s_settings.audioLevelMaster, input);
				levels.master.store(s_settings.audioLevelMaster, std::memory_order_relaxed);
				break;

			case Music:
				Numeric::updateWithStep<int, Min, Max, Step>(s_settings.audioLevelMusic , input);
				levels.music .store(s_settings.audioLevelMusic , std::memory_order_relaxed);
				break;

			case Sound:
				Numeric::updateWithStep<int, Min, Max, Step>(s_settings.audioLevelSound , input);
				levels.sound .store(s_settings.audioLevelSound , std::memory_order_relaxed);
				break;

			case Accept:
				Storage::Settings::store(s_settings);
				MainMenu::transit();
				break;

			case Cancel:
				levels.apply(s_oldSettings);
				MainMenu::transit();
				break;
		}
	}

	static ColorAttribute color(bool primary)
	{
		return primary ? Color::LWhite : Color::White;
	}
}
