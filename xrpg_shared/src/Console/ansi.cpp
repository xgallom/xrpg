//
// Created by xgallom on 2/13/19.
//

#include "Console/Console.h"

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <iostream>

namespace Console
{
	static const char
		AnsiPrefix[]     = "\033[",
		AnsiCursorHide[] = "?25l",
		AnsiCursorShow[] = "?25h",
		AnsiSep[]        = ";",
		AnsiEnd[]        = "m",
		AnsiPos[]		 = "H",
		AnsiFgNormal[]   = "22;3",
		AnsiFgBright[]   = "01;3",
		AnsiBgNormal[]   = "4",
		AnsiBgBright[]   = "10";

	static Coords s_pos = {};
	static termios s_default;

	bool init(bool enableDebug)
	{
		static bool isInit = false;

		if(isInit)
			return false;

		tcgetattr(STDIN_FILENO, &s_default);

		auto ios = s_default;

		ios.c_lflag &= ~static_cast<tcflag_t>(ICANON | ECHO);
		ios.c_cc[VMIN] = 1;

		tcsetattr(STDIN_FILENO, TCSANOW, &ios);

		std::cout << AnsiPrefix << AnsiCursorHide;

		cls();

		if(!enableDebug)
			fclose(stderr);
		else
			get();

		isInit = true;

		return true;
	}

	void deinit()
	{
		cls();

		std::cout << AnsiPrefix << AnsiCursorShow;

		tcsetattr(STDIN_FILENO, TCSANOW, &s_default);
	}

	Coords size()
	{
#if defined(TIOCGWINSZ)
		winsize ws = {};
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
		return {ws.ws_col, ws.ws_row};
#elif defined(TIOCGSIZE)
		ttysize ts;
		ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
		return {ts.ts_col, ts.ts_row};
#else
		return {};
#endif
	}

	Coords pos()
	{
		return s_pos;
	}

	void setPos(Coords coords)
	{
		s_pos = coords;
		std::cout << AnsiPrefix << (coords.y + 1) << AnsiSep << (coords.x + 1) << AnsiPos;
	}

	void write(const char *str, size_t size)
	{
		printf("%.*s", static_cast<int>(size), str);
	}

	void color(ColorAttribute colorAttribute)
	{
		std::cout << AnsiPrefix <<
			(colorAttribute.brightBg() ? AnsiBgBright : AnsiBgNormal) <<
				static_cast<uint>(colorAttribute.bg()) << AnsiSep <<
			(colorAttribute.brightFg() ? AnsiFgBright : AnsiFgNormal) <<
				static_cast<uint>(colorAttribute.fg()) << AnsiEnd;
	}

	void cls()
	{
		Coords coords;
		const auto size = ::Console::size();

		color(Color::Black);
		for(coords.y = 0; coords.y < size.y; ++coords.y) {
			for(coords.x = 0; coords.x < size.x; ++coords.x) {
				setPos(coords);
				write(' ');
			}
		}
	}

	void flush()
	{
		std::cout.flush();
	}

	int get()
	{
		/*
		color(Color::LBlue);
		auto c = getchar();
		std::cout << c << std::endl;
		return c;
		*/

		return getchar();
	}

	int getAsync()
	{
		auto count = 0;
		ioctl(STDIN_FILENO, FIONREAD, &count);

		if(count)
			return get();

		return 0;
	}
}
