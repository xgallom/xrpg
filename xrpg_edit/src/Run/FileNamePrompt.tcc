//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_FILENAMEPROMPT_TCC
#define XRPG_FILENAMEPROMPT_TCC

#include "FileNamePrompt.h"

#include "Context/GlobalContext.h"
#include "Editor.h"

namespace Run
{
	template<typename Self>
	int FileNamePrompt<Self>::s_activeIndex = FileNamePrompt<Self>::First;

	template<typename Self>
	void FileNamePrompt<Self>::render()
	{
		const auto tl = center(InputSize);
		const auto ctr = tl + Coords{PromptSize, 0};
		const auto region = Region{tl - Coords{1, 1}, tl + InputSize + Coords{2, 3}};

		OutputBuffer::clear(region);
		border(region);

		const auto &fileName = GlobalContext::fileName();

		if(s_activeIndex == Error) {
			static constexpr auto error = Self::ErrorText;
			static constexpr auto size = String::strlen(error);
			write(center(Coords{size, 0}), Color::LRed, error, size);
		}
		else {
			Input::text(
					tl + Coords{0, 1},
					Color::White,
					s_activeIndex == FileName ? Color::LWhite : Color::White,
					Prompts[FileName],
					PromptSize,
					fileName
			);
			write(
					ctr + Coords{static_cast<Coords::value_type>(fileName.size()), 1},
					Character(' ', ColorAttribute::Background(s_activeIndex == FileName ? Color::LWhite : Color::Black))
			);

			Input::button(
					tl + Coords{0, 3},
					s_activeIndex == Accept ? Color::LWhite : Color::White,
					Prompts[Accept],
					PromptSize
			);
			Input::button(
					ctr + Coords{0, 3},
					s_activeIndex == Cancel ? Color::LWhite : Color::White,
					Prompts[Cancel],
					PromptSize
			);
		}
	}

	template<typename Self>
	void FileNamePrompt<Self>::update(int c)
	{
		switch(c) {
			case '>':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			case '<':
				if(s_activeIndex > First && s_activeIndex <= Last)
					--s_activeIndex;
				break;

			default:
				handle(c);
				break;
		}
	}

	template<typename Self>
	void FileNamePrompt<Self>::transit()
	{
		s_activeIndex = First;
	}

	template<typename Self>
	void FileNamePrompt<Self>::handle(int input)
	{
		auto &fileName = GlobalContext::fileName();

		switch(s_activeIndex) {
			case FileName:
				String::update<MaxSize, String::isFile>(fileName, input);
				break;

			case Accept:
				if(!Self::handleAccept(fileName)) {
					s_activeIndex = Error;
					break;
				}
				[[fallthrough]];

			case Error:
			case Cancel:
				Editor::transit();
		}
	}
}

#endif //XRPG_FILENAMEPROMPT_TCC
