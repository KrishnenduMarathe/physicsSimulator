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

#include <thread>
#include "main.h"

#if defined(__linux__)

void setup_linux_terminal(struct termios* old)
{
    if (tcgetattr(0, old) < 0)
    {
        perror("tcgetattr()");
    }
    old->c_lflag &= ~ICANON;
    old->c_lflag &= ~ECHO;
    old->c_cc[VMIN] = 1;
    old->c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, old) < 0)
    {
        perror("tcsetattr ICANON");
    }
}

void restore_linux_terminal(struct termios* old)
{
    old->c_lflag |= ICANON;
    old->c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, old) < 0)
    {
        perror("tcsetattr ~ICANON");
    }
}

#endif

void get_keyboard_input(ENGINE* eHandle, char *Kinput)
{
	char input = *Kinput;
	while (true)
	{
		input = get_key_presses();
		if (eHandle->thread_exit || input == '`')
		{
			eHandle->thread_exit = true;
			break;
		}

		while (eHandle->BufferLock) { usleep(REFRESH_TIME); }
		eHandle->BufferLock = true;

		// Input function implementation
		if (eHandle->INPUT_BUFFER == "--NULL--") { eHandle->INPUT_BUFFER.assign(""); }
		eHandle->INPUT_BUFFER.push_back(input);
		eHandle->BufferLock = false;

		if (input == '?') { eHandle->modeSwitch = !eHandle->modeSwitch; }
		if (input == '|') { eHandle->debugWindow = !eHandle->debugWindow; }

	}

	// In case Input Thread Exits First
	system(CLEAR);
}

int main()
{
	#if defined(__linux__)
	struct termios terminalProps = {0};
	setup_linux_terminal(&terminalProps);
	#endif

	// ENGINE instance
	auto *physicsEngine = new ENGINE();
	physicsEngine->initiate_engine(DEFAULT_OBJECT, DEFAULT_MAP);

	// clear screen
	system(CLEAR);

	// Keyboard input thread
	char key;
	std::thread GET_INPUT (get_keyboard_input, physicsEngine, &key);

	while (true)
	{

		if (key == '`') { physicsEngine->thread_exit = true; break; }
		else { usleep(REFRESH_TIME); }

		if (physicsEngine->thread_exit) { break; }

		if (!physicsEngine->refresh_object()) { physicsEngine->thread_exit = true; break; }
		if (!physicsEngine->update_frame()) { physicsEngine->thread_exit = true; break; }
		if (!physicsEngine->draw_frame()) { physicsEngine->thread_exit = true; break; }

		if (key != '`') { key = 0; }

	}

	// Wait for keyboard input thread
	GET_INPUT.join();

	// In case Input thread finished early
	// Clear Screen
	system(CLEAR);
	// Free Memory
	physicsEngine->terminate_engine();
	delete physicsEngine;

	#if defined(__linux__)
	restore_linux_terminal(&terminalProps);
	#endif

	return 0;
}
