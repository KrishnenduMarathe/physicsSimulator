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
