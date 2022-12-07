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
#ifndef _MAIN_H_
#define _MAIN_H_

#include "PhysicsEngine.h"

char get_key_presses()
{
    // FROM:
    // https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed

    char character = 0;
    #if defined(_WIN32)
    character = _getch();
    #elif __linux__
    if (read(0, &character, 1) < 0)
    {
        perror("read()");
    }
    #endif

    return character;
}

#endif // _MAIN_H_
