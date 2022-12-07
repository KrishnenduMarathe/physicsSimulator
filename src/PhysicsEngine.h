// AUTHOR: Krishnendu Marathe
// PROGRAM: physicsSimulator

/*
** 							TICTACTOE
** 							---------
** 	  A Physics Simulation Engine for Terminal for Windows and Linux Platform.
**
** 					 	  	 License
** 	  						 -------
**
** 	  This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "PhysicsObject.h"
#include "pixel.h"
#include "map.h"


// Default Object Code
#define DEFAULT_OBJECT 1

// Defualt Map
#define DEFAULT_MAP 1

// Default Object Length
#define DEFAULT_LENGTH 12

// Object Density in mass(Kg)/unit^3 (meter^3)
// Ave. of Oak wood
#define DENSITY 1000

// In-elastic Collision Coefficient of Restitution
#define collisionCoefficient static_cast<float>(0.65)

// Refresh Time in Microseconds
#define REFRESH_TIME 10000

class ENGINE
{
private:
	bool INIT = false;

	int terminalWidth = 0;
	int terminalHeight = 0;

	PIXEL **FrameBuffer{};
	PhysicObject *object{};

	MAP00 *map{};
	int *map_notice{};

	bool insert_MapNotice(int MAP);
	void empty_MapNotice();

	void get_terminal_dimension();
	bool is_object(int pixelX, int pixelY);

public:

	// Input Buffer
	std::string INPUT_BUFFER = "--NULL--";
	bool BufferLock = false;

	// Debug Screen
	std::string debug = "";

	// Signal Shutdown
	bool thread_exit = false;

	bool modeSwitch = false;
	bool debugWindow = false;

	// Initiate Object: Pipe = 1
	void initiate_engine(int OCode, int MCode);

	bool refresh_object();

	bool update_frame();

	bool draw_frame();

	void terminate_engine();
};

#endif // PHYSICS_ENGINE_H
