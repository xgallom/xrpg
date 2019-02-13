//
// Created by xgallom on 10. 2. 2019.
//

#include "Console/Console.h"

#include <windows.h>

namespace Console
{
	static constexpr COORD fromCoords(Coords coords);
	static constexpr Coords fromCoords(COORD coords);
	static constexpr WORD fromColor(WORD v);
	static constexpr WORD fromColor(ColorAttribute colorAttribute);

	static HANDLE
		s_input  = nullptr,
		s_output = nullptr;

	bool init()
	{
		if(s_input && s_output)
			return false;

		s_input = GetStdHandle(STD_INPUT_HANDLE);

		if(s_input) {
			DWORD inputMode;

			GetConsoleMode(s_input, &inputMode);
			SetConsoleMode(s_input, inputMode & static_cast<DWORD>(~ENABLE_LINE_INPUT));
		}

		s_output = GetStdHandle(STD_OUTPUT_HANDLE);

		if(s_output) {
			DWORD outputMode;

			GetConsoleMode(s_output, &outputMode);
			SetConsoleMode(s_output, outputMode & static_cast<DWORD>(~ENABLE_WRAP_AT_EOL_OUTPUT));

			const CONSOLE_CURSOR_INFO cursorInfo{1, false};
			SetConsoleCursorInfo(s_output, &cursorInfo);

			#if (_WIN32_WINNT >= 0x0501)
			SetConsoleDisplayMode(s_output, CONSOLE_FULLSCREEN_MODE, nullptr);
			#endif
		}

		return s_input && s_output;
	}

	Coords size()
	{
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

		GetConsoleScreenBufferInfo(s_output, &bufferInfo);

		const auto &rect = bufferInfo.srWindow;

		return Coords{
			static_cast<Coords::value_type>(rect.Right  - rect.Left + 1),
			static_cast<Coords::value_type>(rect.Bottom - rect.Top  + 1)
		};
	}

	Coords pos()
	{
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

		GetConsoleScreenBufferInfo(s_output, &bufferInfo);

		return fromCoords(bufferInfo.dwCursorPosition);
	}

	void setPos(Coords coords)
	{
		SetConsoleCursorPosition(s_output, fromCoords(coords));
	}

	void write(const char *str, size_t size)
	{
		DWORD written;

		WriteConsole(s_output, str, size, &written, nullptr);
	}

	void color(ColorAttribute colorAttribute)
	{
		SetConsoleTextAttribute(s_output, fromColor(colorAttribute));
	}

	int get()
	{
		char input;
		DWORD read;

		ReadConsole(s_input, &input, 1, &read, nullptr);

		return read ? input : 0;
	}

	static constexpr COORD fromCoords(Coords coords)
	{
		const auto x = static_cast<SHORT>(coords.x), y = static_cast<SHORT>(coords.y);

		return COORD{x, y};
	}

	static constexpr Coords fromCoords(COORD coords)
	{
		return Coords{
			static_cast<Coords::value_type>(coords.X),
			static_cast<Coords::value_type>(coords.Y)
		};
	}

	static constexpr WORD fromColor(WORD v)
	{
		return static_cast<WORD>(
				(v & Color::Red    ? FOREGROUND_RED       : 0) |
				(v & Color::Green  ? FOREGROUND_GREEN     : 0) |
				(v & Color::Blue   ? FOREGROUND_BLUE      : 0) |
				(v & Color::Bright ? FOREGROUND_INTENSITY : 0)
		);
	}

	static constexpr WORD fromColor(ColorAttribute colorAttribute)
	{
		return
			fromColor(colorAttribute.value) |
			fromColor(colorAttribute.value >> Color::Bits) << Color::Bits;
	}

}
