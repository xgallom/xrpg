//
// Created by xgallom on 2/15/19.
//

#include "Editor.h"

#include "Context/GlobalContext.h"
#include "EditorBody.h"
#include "EditorMenu.h"
#include "NewMap.h"
#include "SaveMap.h"
#include "OpenMap.h"
#include "Quit.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Border.h>

namespace Run
{
	void Editor::render()
	{
		border();

		if(GlobalContext::state() == GlobalState::Editor) {
			EditorMenu::render();
			EditorBody::render();
		}
		else {
			EditorBody::render();
			EditorMenu::render();
		}

		switch(GlobalContext::state()) {
			case GlobalState::Editor:
				break;
			case GlobalState::Menu:
				break;

			case GlobalState::NewMap:
				NewMap::render();
				break;

			case GlobalState::SaveMap:
				SaveMap::render();
				break;

			case GlobalState::OpenMap:
				OpenMap::render();
				break;

			case GlobalState::Quit:
				break;
		}
	}

	void Editor::update()
	{
		const auto c = Console::get();

		switch(GlobalContext::state()) {
			case GlobalState::Editor:
				EditorBody::update(c);
				break;

			case GlobalState::Menu:
				EditorMenu::update(c);
				break;

			case GlobalState::NewMap:
				NewMap::update(c);
				break;

			case GlobalState::SaveMap:
				SaveMap::update(c);
				break;

			case GlobalState::OpenMap:
				OpenMap::update(c);
				break;

			case GlobalState::Quit:
				break;
		}
	}

	void Editor::transit()
	{
		GlobalContext::state() = GlobalState::Editor;
	}
}
