//
// Created by xgallom on 2/16/19.
//

#include "EditorBody.h"

#include "Context/GlobalContext.h"
#include "EditorMenu.h"

#include <Data/Map.h>
#include <Graphics/Coords.h>
#include <Graphics/OutputBuffer.h>
#include <Graphics/Border.h>
#include <Util/String.h>

namespace Run
{
	enum State {
		CharMode = 0,
		ColorMode
	};

	static auto s_state = CharMode;
	static ColorAttribute s_ca = Color::LWhite;

	static void handle(int c);

	void EditorBody::render()
	{
		const auto pos = transform<int>(GlobalContext::pos());
		const auto &map = GlobalContext::map();
		const auto mapSize = map.size;
		const auto isActive = GlobalContext::state() == GlobalState::Editor;

		const Region borderRegion = {{0, 2}, OutputBuffer::size()};
		const Region region = {borderRegion.tl + Coords{1, 1}, borderRegion.br - Coords{1, 1}};

		const auto regionSize   = transform<int>(region.size());
		const auto regionCenter = center(regionSize, {});

		Coords regionIndex;
		for(regionIndex.y = 0; regionIndex.y < regionSize.y; ++regionIndex.y) {
			for(regionIndex.x = 0; regionIndex.x < regionSize.x; ++regionIndex.x) {
				const auto index = pos - regionCenter + transform<int>(regionIndex);

				if(index.x < 0 || index.y < 0 || index.x >= mapSize.x || index.y >= mapSize.y) {
					write(region.tl + regionIndex, Character{' ', ColorAttribute::Background(isActive ? Color::Blue : Color::Black)});
					continue;
				}

				bool isFocused = index == pos;
				auto ch = map.at(transform<Coords::value_type>(index));

				if(isFocused) {
					ch = Character{
							ch.ch(),
							static_cast<ColorAttribute::value_type>(~ch.ca().value)
					};

					write(region.tl + regionIndex, ch);
				}
				else
					write(region.tl + regionIndex, ch);
			}
		}

		border(borderRegion, ColorAttribute::Background(isActive ? Color::LBlue : Color::White));
	}

	void EditorBody::update(int c)
	{
		auto &pos = GlobalContext::pos();
		const auto &mapSize = GlobalContext::map().size;

		switch(c) {
			case '`':
				EditorMenu::transit();
				break;

			case '\t':
				s_ca = (s_ca.value << 4) | (s_ca.value >> 4);
				break;

			case '2':
				if(pos.y < mapSize.y)
					++pos.y;
				break;

			case '4':
				if(pos.x > 0)
					--pos.x;
				break;

			case '6':
				if(pos.x < mapSize.x - 1)
					++pos.x;
				break;

			case '8':
				if(pos.y > 0)
					--pos.y;
				break;

			case '~':
				s_state = s_state == CharMode ? ColorMode : CharMode;
				break;

			default:
				handle(c);
				break;
		}
	}

	static void handle(int c)
	{
		switch(s_state) {
			case CharMode:
				GlobalContext::map().at(GlobalContext::pos()) = Character{static_cast<char>(c == ' ' ? 0 : c), s_ca};
				break;

			case ColorMode: {
				const auto v = c - 'a';
				if(v >= 0 && v <= 16)
					s_ca = v;
				break;
			}
		}
	}
}
