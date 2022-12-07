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
#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "std_libs.h"

// Abstract class
class PhysicObject
{
public:

	std::string whoAmI = "object";

	int x1 = -1, y1 = -1;
	int x2 = -1, y2 = -1;
	int x3 = -1, y3 = -1;
	int x4 = -1, y4 = -1;

	unsigned int width = 0, height = 0;
	float center_x = 0, center_y = 0;

	float mass = 0;
	float angle = 0;

	float velocity_x = 0, velocity_y = 0;
	float old_velocity_x = 0, old_velocity_y = 0;


	// Collision with Borders Detection
	bool collision = false;

	virtual void update_dimensions() = 0;
};

class PIPE: public PhysicObject
{
public:

	PIPE() { this->whoAmI.assign("pipe"); }

	void update_dimensions() override
	{
		float xDiff, yDiff;

    xDiff = static_cast<float>(this->width) / 2;
    yDiff = static_cast<float>(this->height) / 2;

		// Special for PIPE
		if (xDiff < 1) { xDiff = 0.0f; }
		if (yDiff < 1) { yDiff = 0.0f; }

    this->x1 = static_cast<int>(this->center_x - xDiff);
    this->y1 = static_cast<int>(this->center_y - yDiff);

    this->x2 = static_cast<int>(this->center_x + xDiff);
    this->y2 = static_cast<int>(this->center_y - yDiff);

    this->x3 = static_cast<int>(this->center_x - xDiff);
    this->y3 = static_cast<int>(this->center_y + yDiff);

    this->x4 = static_cast<int>(this->center_x + xDiff);
    this->y4 = static_cast<int>(this->center_y + yDiff);

	}
};

#endif // PHYSICS_OBJECT_H
