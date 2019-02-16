//
// Created by xgallom on 2/15/19.
//

#include "EditorMenu.h"

#include "Context/GlobalContext.h"
#include "Editor.h"
#include "NewMap.h"
#include "OpenMap.h"
#include "Quit.h"
#include "SaveMap.h"

#include <Graphics/Border.h>
#include <Graphics/Coords.h>
#include <Graphics/Menu.h>
#include <Graphics/OutputBuffer.h>

namespace Run
{
	enum Index {
		New = 0,
		Save,
		Open,
		Exit,

		Size
	};
	static constexpr auto First = New, Last = Exit, Invalid = Size;

	static constexpr Menu<Size, 8> EditorMenuMenu = {
			"  New   ",
			"  Save  ",
			"  Open  ",
			"  Exit  ",
	};

	static int s_activeIndex = First;

	static void handle(int activeIndex);

	void EditorMenu::render()
	{
		static const auto
			tl = Coords{0, 0},
			br = Coords{OutputBuffer::size().x, 3};

		const auto isActive = GlobalContext::state() == GlobalState::Menu;

		border({tl, br}, ColorAttribute::Background(isActive ? Color::LBlue : Color::White));

		EditorMenuMenu.renderHorizontal(tl + Coords{1, 1}, isActive ? s_activeIndex : Invalid);
	}

	void EditorMenu::update(int c)
	{
		switch(c) {
			case '`':
			case '~':
				Editor::transit();
				break;

			case '4':
			case 'a':
			case '<':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			case '6':
			case 'd':
			case '>':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			case '5':
			case '\r':
			case '\n':
				handle(s_activeIndex);
				break;

			case 'n':
			case 'N':
				handle(New);
				break;

			case 's':
			case 'S':
				handle(Save);
				break;

			case 'o':
			case 'O':
				handle(Open);
				break;

			case 'x':
			case 'X':
			case 'q':
			case 'Q':
				handle(Exit);
				break;
		}
	}

	void EditorMenu::transit()
	{
		GlobalContext::state() = GlobalState::Menu;
		s_activeIndex = First;
	}

	static void handle(int activeIndex)
	{
		switch(activeIndex) {
			case New : NewMap::transit();  break;
			case Save: SaveMap::transit(); break;
			case Open: OpenMap::transit(); break;
			case Exit: quit();             break;
		}
	}
}
