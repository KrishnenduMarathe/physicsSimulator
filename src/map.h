#pragma once
#ifndef MAP_H
#define MAP_H

#include "PhysicsObject.h"

#if defined(_WIN32)
#include <windows.h>
#include <conio.h>
#define CLEAR "cls"
#elif __linux__
#include <sys/ioctl.h>
#include <termios.h>
#define CLEAR "clear"
#endif

class MAP00
{
public:

	int terminalWidth = 0;
	int terminalHeight = 0;

	 int numberOfObjects = 0;

	PhysicObject *map_objects;

	#if defined(_WIN32)
	void get_terminal_dimension()
	{
		// FROM: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
		CONSOLE_SCREEN_BUFFER_INFO terminalWindow;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminalWindow);
		this->terminalWidth = terminalWindow.srWindow.Right-terminalWindow.srWindow.Left+1;
		this->terminalHeight = terminalWindow.srWindow.Bottom-terminalWindow.srWindow.Top+1;

	}
	#elif __linux__
	void get_terminal_dimension()
	{
		// FROM: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
		struct winsize terminalWindow{};
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalWindow);
		this->terminalWidth = terminalWindow.ws_col;
		this->terminalHeight = terminalWindow.ws_row;

	}
	#endif

	virtual int is_map_object(int pixelX, int pixelY) = 0;

	virtual void update_map() = 0;
};

class MAP01: public MAP00
{
public:

	MAP01()
	{
		this->numberOfObjects = 4;
		this->map_objects = new PIPE[this->numberOfObjects];
		this->update_map();
	}

	void update_map() override
	{

		this->get_terminal_dimension();

		// NOTE: Collision with map elements to be vertical should be a horizontal object with a 90 degree angle
		//       Otherwise it would misbehave.

		// 1: horizontal up
		this->map_objects[0].width = this->terminalWidth - 1;
		this->map_objects[0].height = 1;
		this->map_objects[0].center_x = static_cast<float>(this->terminalWidth) / 2;
		this->map_objects[0].center_y = 0.5f;
		this->map_objects[0].angle = 0.0f;
		this->map_objects[0].update_dimensions();

		// 2: vertical left
		this->map_objects[1].width = this->terminalHeight - 2;
		this->map_objects[1].height = 1;
		this->map_objects[1].center_x = 0.5f;
		this->map_objects[1].center_y = static_cast<float>(this->terminalHeight) / 2;
		this->map_objects[1].angle = 90.0f;
		this->map_objects[1].update_dimensions();

		// 3: horizontal right
		this->map_objects[2].width = this->terminalWidth - 1;
		this->map_objects[2].height = 1;
		this->map_objects[2].center_x = static_cast<float>(this->terminalWidth) / 2;
		this->map_objects[2].center_y = static_cast<float>(this->terminalHeight) - 1;
		this->map_objects[2].angle = 0.0f;
		this->map_objects[2].update_dimensions();

		// 4: vertical right
		this->map_objects[3].width = this->terminalHeight - 2;
		this->map_objects[3].height = 1;
		this->map_objects[3].center_x = static_cast<float>(this->terminalWidth) - 1;
		this->map_objects[3].center_y = static_cast<float>(this->terminalHeight) / 2;
		this->map_objects[3].angle = 90.0f;
		this->map_objects[3].update_dimensions();

	}

	int is_map_object(int pixelX, int pixelY) override
	{
		int Mval = -1;

		float radians;
		float sinT;
		float cosT;
		float X, Y;
		float Xn, Yn;
		int Xc, Yc;

		// Detecting Object Pixel Conversion
		for (int m = 0; m < this->numberOfObjects; m++)
		{

			radians = (this->map_objects[m].angle * 22) / (180 * 7);
			sinT = sinf(radians);
			cosT = cosf(radians);

			float use_center_x, use_center_y;
			use_center_x = this->map_objects[m].center_x;
			use_center_y = this->map_objects[m].center_y;

			if (this->map_objects[m].whoAmI == "pipe")
			{
				if (use_center_x < 1) { use_center_x = 0; }
				if (use_center_y < 1) { use_center_y = 0; }
			}

			// Correct Pixel Coordinate Space into Object Coordinate Space
			X = static_cast<float>(pixelX) - use_center_x;
			Y = use_center_y - static_cast<float>(pixelY);

			// Calculate in un-rotated domain
			Xn = (X*cosT) + (Y*sinT);
			Yn = (Y*cosT) - (X*sinT);

			// Correct for Window system coordinate space
			Xc = static_cast<int>(Xn + use_center_x);
			Yc = static_cast<int>(use_center_y - Yn);

			if (Xc <= this->map_objects[m].x2 && Xc >= this->map_objects[m].x1)
			{
				if (Yc <= this->map_objects[m].y3 && Yc >= this->map_objects[m].y1)
				{
					return m;
				}
			}
		}
		return Mval;
	}
};

#endif // MAP_H
