//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_FILENAMEPROMPT_H
#define XRPG_FILENAMEPROMPT_H

#include <Graphics/Border.h>
#include <Graphics/Coords.h>
#include <Graphics/Input.h>
#include <Graphics/OutputBuffer.h>
#include <Storage/Storage.h>
#include <Util/String.h>

namespace Run
{
	template<typename Self>
	struct FileNamePrompt {
		static void render();
		static void update(int c);
		static void transit();

		enum Index {
			FileName,

			Accept,
			Cancel,

			Size
		};
		static constexpr auto First = FileName, Last = Cancel, Error = Size;

		static constexpr Coords InputSize = {24, 3};
		static constexpr size_t PromptSize = 12, MaxSize = 11;

		static constexpr char Prompts[][PromptSize + 1] = {
				" File name: ",

				"   Accept   ",
				"   Cancel   "
		};

		static int s_activeIndex;

		static void handle(int input);
	};
}

#include "FileNamePrompt.tcc"

#endif //XRPG_FILENAMEPROMPT_H
