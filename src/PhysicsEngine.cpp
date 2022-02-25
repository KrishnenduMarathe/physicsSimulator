#include "PhysicsEngine.h"

bool ENGINE::insert_MapNotice(int MAP)
{
	for (int m = 0; m < this->map->numberOfObjects; m++)
	{
		if (this->map_notice[m] == MAP) { return false; }
	}

	for (int m = 0; m < this->map->numberOfObjects; m++)
	{
		if (this->map_notice[m] == -1)
		{
			this->map_notice[m] = MAP;
			return false;
		}
	}

	return true;
}

void ENGINE::empty_MapNotice()
{
	for (int m = 0; m < this->map->numberOfObjects; m++)
	{
		this->map_notice[m] = -1;
	}
}

#if defined(_WIN32)
void ENGINE::get_terminal_dimension()
{
	// FROM: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
	CONSOLE_SCREEN_BUFFER_INFO terminalWindow;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminalWindow);
	this->terminalWidth = terminalWindow.srWindow.Right-terminalWindow.srWindow.Left+1;
	this->terminalHeight = terminalWindow.srWindow.Bottom-terminalWindow.srWindow.Top+1;

}
#elif __linux__
void ENGINE::get_terminal_dimension()
{
	// FROM: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
	struct winsize terminalWindow{};
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalWindow);
	this->terminalWidth = terminalWindow.ws_col;
	this->terminalHeight = terminalWindow.ws_row;

}
#endif

#define TimeInSec static_cast<float>(REFRESH_TIME)/1000000

bool ENGINE::is_object(int pixelX, int pixelY)
{
	float radians = (this->object->angle * 22) / (180 * 7);
	float sinT = sinf(radians);
	float cosT = cosf(radians);

	// Correct Pixel Coordinate Space into Object Coordinate Space
	float X, Y;
	X = static_cast<float>(pixelX) - this->object->center_x;
	Y = this->object->center_y - static_cast<float>(pixelY);

	// Calculate in un-rotated domain
	float Xn, Yn;
	Xn = (X*cosT) + (Y*sinT);
	Yn = (Y*cosT) - (X*sinT);

	// Correct for Window system coordinate space
	int Xc, Yc;
	Xc = static_cast<int>(Xn+this->object->center_x);
	Yc = static_cast<int>(this->object->center_y - Yn);

	// Detecting pixel location
	if (Xc <= this->object->x2 && Xc >= this->object->x1)
	{
		if (Yc <= this->object->y3 && Yc >= this->object->y1)
		{
			return true;
		}
	}

	return false;
}

void ENGINE::initiate_engine(int OCode, int MCode)
{
	this->get_terminal_dimension();

	// Allocate FrameBuffer
	this->FrameBuffer = new PIXEL*[this->terminalHeight];
	for (int h = 0; h < this->terminalHeight; h++)
	{
		this->FrameBuffer[h] = new PIXEL[this->terminalWidth];
		for (int w = 0; w < this->terminalWidth; w++)
		{
			this->FrameBuffer[h][w].set_coordinate(w, h);
			this->FrameBuffer[h][w].holder = ' ';
		}
	}

	// Object Initiation
	if (OCode == 1)
	{
		this->object = new PIPE();
		this->object->width = DEFAULT_LENGTH;
		this->object->height = 1;
	} else { return; }

	this->object->center_x = static_cast<float>(this->terminalWidth) / 2;
	this->object->center_y = static_cast<float>(this->terminalHeight) / 2;
	this->object->update_dimensions();

	auto area = this->object->height * this->object->width;
	this->object->mass = area * DENSITY;

	// Initiate Map
	if (MCode == 1)
	{
		this->map = new MAP01();
		this->map_notice = new int[this->map->numberOfObjects];
		this->empty_MapNotice();
	} else { return; }

	this->INIT = true;
}

bool ENGINE::refresh_object()
{
	if (!this->INIT) { return this->INIT; }

	// Update Map
	this->map->update_map();

	// Mode Change
	if (this->modeSwitch)
	{
		this->object->angle += static_cast<float>(22)/7;
	} else
	{
		this->object->angle = 0.0f;
	}
	this->object->angle = fmodf(this->object->angle, 360);

	const float AccelBoost = 50.0f;
	const float AirResist = 2.0f;
	const float gAccel = 9.8;

	float acceleration_x = 0, acceleration_y = 0;

	/* ---------------------- *
	** Kinematic Calculations |
	** -----------------------*/
	float travel_distance_x, travel_distance_y;

	/* ----------------- *
	** Colision Response |
	** ----------------- */
	if (this->object->collision)
	{

		this->object->collision = false;
		float V;
		V = (-1) * collisionCoefficient * sqrtf(powf(this->object->old_velocity_x, 2) + powf(this->object->old_velocity_y, 2));
		this->object->velocity_x = 0;
		this->object->velocity_y = 0;

		for (int m = 0; m < this->map->numberOfObjects; m++)
		{
			if (this->map_notice[m] != -1)
			{
				this->object->velocity_x += (V * sinf(this->map->map_objects[this->map_notice[m]].angle * 22 / (180 * 7)) * copysignf(1, this->object->old_velocity_x));
				this->object->velocity_y += (V * cosf(this->map->map_objects[this->map_notice[m]].angle * 22 / (180 * 7)) * copysignf(1, this->object->old_velocity_y));
			}
		}

		this->empty_MapNotice();
	}

	/* -------------- *
	** Air Resistance |
	** -------------- */

	if (this->object->velocity_x > 0)
	{
			acceleration_x -= AirResist;
	} else
	{
			if (this->object->velocity_x != 0)
			{
					acceleration_x += AirResist;
			}
	}

	if (this->object->velocity_y > 0)
	{
			acceleration_y -= AirResist;
	} else
	{
			if (this->object->velocity_y != 0)
			{
					acceleration_y += AirResist;
			}
	}

	/* ------- *
	** Gravity |
	** ------- */
	acceleration_y += gAccel;

	/* ------------- *
	** Input Loading |
	** --------------*/
	if (this->INPUT_BUFFER != "--NULL--" && !this->INPUT_BUFFER.empty())
	{
		while (this->BufferLock) { usleep(REFRESH_TIME); }
		this->BufferLock = true;

		unsigned long int sMaxLength = this->INPUT_BUFFER.length();
		char iKey;

		for (unsigned long int sl = 0; sl < sMaxLength; sl++)
		{
			iKey = this->INPUT_BUFFER[sl];

			switch (iKey)
			{
				case 'w':
          acceleration_y -= AccelBoost;
          break;
        case 'a':
          acceleration_x -= AccelBoost;
          break;
        case 's':
          acceleration_y += AccelBoost;
					break;
        case 'd':
          acceleration_x += AccelBoost;
          break;
        case 'c':
          acceleration_x = 0;
          acceleration_y = 0;

					this->object->velocity_x = 0;
          this->object->velocity_y = 0;

					this->object->center_y = static_cast<float>(this->terminalHeight) / 2;
          this->object->center_x = static_cast<float>(this->terminalWidth) / 2;
				default:
					break;
			}
		}

		this->INPUT_BUFFER.clear();
		this->BufferLock = false;
	}

	// s = ut + 0.5 x a x t^2
	travel_distance_x = (this->object->velocity_x * TimeInSec) + (0.5f * acceleration_x * powf(TimeInSec, 2));
	travel_distance_y = (this->object->velocity_y * TimeInSec) + (0.5f * acceleration_y * powf(TimeInSec, 2));

	// v = u + a*t
	this->object->velocity_x += (acceleration_x * TimeInSec);
	this->object->velocity_y += (acceleration_y * TimeInSec);

	this->object->old_velocity_x = this->object->velocity_x;
	this->object->old_velocity_y = this->object->velocity_y;

	this->object->center_x += travel_distance_x;
	this->object->center_y += travel_distance_y;
	this->object->update_dimensions();

	/* --------- *
	** Collision |
	** ----------*/
	float radians = (this->object->angle * 22) / (180 * 7);
	float sinT = sinf(radians);
	float cosT = cosf(radians);

	// Get Object Vertexes in Rotation
	float X, Y;
	int x_array[4], y_array[4];

	X = static_cast<float>(this->object->x1) - this->object->center_x;
	Y = this->object->center_y - static_cast<float>(this->object->y1);
	x_array[0] = static_cast<int>(((X*cosT) + (Y*sinT)) + this->object->center_x);
	y_array[0] = static_cast<int>(this->object->center_y - ((Y*cosT) - (X*sinT)));

	X = static_cast<float>(this->object->x2) - this->object->center_x;
	Y = this->object->center_y - static_cast<float>(this->object->y2);
	x_array[1] = static_cast<int>(((X*cosT) + (Y*sinT)) + this->object->center_x);
	y_array[1] = static_cast<int>(this->object->center_y - ((Y*cosT) - (X*sinT)));

	X = static_cast<float>(this->object->x3) - this->object->center_x;
	Y = this->object->center_y - static_cast<float>(this->object->y3);
	x_array[2] = static_cast<int>(((X*cosT) + (Y*sinT)) + this->object->center_x);
	y_array[2] = static_cast<int>(this->object->center_y - ((Y*cosT) - (X*sinT)));

	X = static_cast<float>(this->object->x4) - this->object->center_x;
	Y = this->object->center_y - static_cast<float>(this->object->y4);
	x_array[3] = static_cast<int>(((X*cosT) + (Y*sinT)) + this->object->center_x);
	y_array[3] = static_cast<int>(this->object->center_y - ((Y*cosT) - (X*sinT)));

	int MM;
	int MM_ARRAY[this->map->numberOfObjects];
	bool MM_FOUND = false;
	int m_xarray[4], m_yarray[4];
	float cosM, sinM;
	float distance1[4], distance2;
	float radiansM;

	for (int iter = 0; iter < this->map->numberOfObjects; iter++)
	{
		MM_ARRAY[iter] = -1;
	}

	for (int iter = 0; iter < 4; iter++)
	{
		MM_FOUND = false;
		MM = this->map->is_map_object(x_array[iter], y_array[iter]);
		if (MM != -1)
		{
			for (int i = 0; i < this->map->numberOfObjects; i++)
			{
				if (MM_ARRAY[i] != -1 && MM_ARRAY[i] == MM)
				{
					MM_FOUND = true;
					break;
				}
			}

			if (!MM_FOUND)
			{
				for (int i = 0; i < this->map->numberOfObjects; i++)
				{
					if (MM_ARRAY[i] == -1)
					{
						MM_ARRAY[i] = MM;
						if (this->insert_MapNotice(MM)) { perror("Error: Inserting object in MapNotice failed!"); exit(1); }
						break;
					}
				}

				radiansM = (this->map->map_objects[MM].angle * 22) / (180 * 7);
				sinM = sinf(radiansM);
				cosM = cosf(radiansM);

				X = static_cast<float>(this->map->map_objects[MM].x1) - this->map->map_objects[MM].center_x;
				Y = this->map->map_objects[MM].center_y - static_cast<float>(this->map->map_objects[MM].y1);
				m_xarray[0] = static_cast<int>(((X*cosM) + (Y*sinM)) + this->map->map_objects[MM].center_x);
				m_yarray[0] = static_cast<int>(this->map->map_objects[MM].center_y - ((Y*cosM) - (X*sinM)));

				X = static_cast<float>(this->map->map_objects[MM].x2) - this->map->map_objects[MM].center_x;
				Y = this->map->map_objects[MM].center_y - static_cast<float>(this->map->map_objects[MM].y2);
				m_xarray[1] = static_cast<int>(((X*cosM) + (Y*sinM)) + this->map->map_objects[MM].center_x);
				m_yarray[1] = static_cast<int>(this->map->map_objects[MM].center_y - ((Y*cosM) - (X*sinM)));

				X = static_cast<float>(this->map->map_objects[MM].x3) - this->map->map_objects[MM].center_x;
				Y = this->map->map_objects[MM].center_y - static_cast<float>(this->map->map_objects[MM].y3);
				m_xarray[2] = static_cast<int>(((X*cosM) + (Y*sinM)) + this->map->map_objects[MM].center_x);
				m_yarray[2] = static_cast<int>(this->map->map_objects[MM].center_y - ((Y*cosM) - (X*sinM)));

				X = static_cast<float>(this->map->map_objects[MM].x4) - this->map->map_objects[MM].center_x;
				Y = this->map->map_objects[MM].center_y - static_cast<float>(this->map->map_objects[MM].y4);
				m_xarray[3] = static_cast<int>(((X*cosM) + (Y*sinM)) + this->map->map_objects[MM].center_x);
				m_yarray[3] = static_cast<int>(this->map->map_objects[MM].center_y - ((Y*cosM) - (X*sinM)));

				// Distance from point to vertices
				for (int v = 0; v < 4; v++)
				{
					distance1[v] = sqrtf(powf(static_cast<float>(x_array[iter]) - static_cast<float>(m_xarray[v]), 2) + powf(static_cast<float>(y_array[iter]) - static_cast<float>(m_yarray[v]), 2));
				}

				float* min_ptr = std::min_element(distance1, distance1+4);
				float min_distance1 = *min_ptr;

				// find vertex position
				int vPos = -1;
				for (int v= 0; v < 4; v++)
				{
					if (distance1[v] == min_distance1)
					{
						vPos = v;
						break;
					}
				}

				if (vPos == -1)
				{
					perror("Error: Vertex not found!");
					exit(1);
				}

				// Calculate distance from map object center to minimum vertex
				distance2 = sqrtf(powf(this->map->map_objects[MM].center_x - static_cast<float>(m_xarray[vPos]), 2) + powf(this->map->map_objects[MM].center_y - static_cast<float>(m_yarray[vPos]), 2));

				// Determine Nearest face (minimum of the two distance calculations)
				// Minor Error -- Assuming that the object center, point of inclusion and vertex are in straight line
				float use_height = static_cast<float>(this->map->map_objects[MM].height)/2;
				float use_width = static_cast<float>(this->map->map_objects[MM].width)/2;
				if (this->map->map_objects[MM].whoAmI == "pipe")
				{
					if (use_height < 1) { use_height = 0.5f; }
					if (use_width < 1) { use_width = 0.5f; }
				}

				float manageDistance1 = (use_width * min_distance1)/distance2; //std::min( , );
				float manageDistance2 = (use_height * min_distance1)/distance2;

				// Calculate X-Y Components
				float x_component1, y_component1, x_component2, y_component2;
				// x_component = manageDistance * cos(90 - theta_M)
				x_component1 = manageDistance1 * sinM;
				y_component1 = manageDistance1 * cosM;

				x_component2 = manageDistance2 * sinM;
				y_component2 = manageDistance2 * cosM;

				// Append Values
				this->object->collision = true;
				this->object->center_x -= copysignf(std::min(x_component1, x_component2), this->object->velocity_x);
				this->object->center_y -= copysignf(std::min(y_component1, y_component2), this->object->velocity_y);
				this->object->velocity_x = 0;
				this->object->velocity_y = 0;
				this->object->update_dimensions();
			} else
			{
				this->object->velocity_x = 0;
				this->object->velocity_y = 0;
			}
		}

		// Out of bounds Coordinate Crash Fix - Hard coded
		if (this->object->center_x < 0.0f) { this->object->center_x = static_cast<float>(this->object->width) * cosT / 2; this->object->collision = true; }
		if (this->object->center_y < 0.0f) { this->object->center_y = static_cast<float>(this->object->width) * cosT / 2; this->object->collision = true; }
		if (this->object->center_x > static_cast<float>(this->terminalWidth - 1)) { this->object->center_x = static_cast<float>(this->terminalWidth - 1) - (static_cast<float>(this->object->width) * cosT / 2); this->object->collision = true; }
		if (this->object->center_y > static_cast<float>(this->terminalHeight - 1)) { this->object->center_y = static_cast<float>(this->terminalHeight - 1) - (static_cast<float>(this->object->width) * cosT / 2); this->object->collision = true; }
		this->object->update_dimensions();
	}

	// Debug Window
	if (this->debugWindow)
	{
		this->debug.assign(" :: DEBUG::,Theta: "+std::to_string(this->object->angle)+",x-y: "+std::to_string(this->object->center_x)+" "+std::to_string(this->object->center_y)+",Vx-Vy: "+std::to_string(this->object->velocity_x)+" "+std::to_string(this->object->velocity_y));
	} else { this->debug.assign(""); }

	// DEBUG
	//this->object->center_x = static_cast<float>(this->terminalWidth) / 2;
	//this->object->center_y = static_cast<float>(this->terminalHeight) / 2;
	//this->object->update_dimensions();

	return true;
}

bool ENGINE::update_frame()
{
	if (!this->INIT) { return this->INIT; }

	if (this->FrameBuffer != nullptr)
	{
		for (int h = 0; h < this->terminalHeight; h++)
    {
        delete[] this->FrameBuffer[h];
    }
    delete[] this->FrameBuffer;
	}

	// Get Updates
	int old_height = this->terminalHeight;
	int old_width = this->terminalWidth;
	this->get_terminal_dimension();
	if (old_height > this->terminalHeight || old_width > this->terminalWidth) { system(CLEAR); }

	// Debug Message
	int currentHeight = 1;
	int stringIterator = 0;
	unsigned long int string_length = this->debug.length();

	std::string bgColor = COLOR::unicode_escape+COLOR::bg_black+COLOR::unicode_end;
	std::string mapColor = COLOR::unicode_escape+COLOR::bg_white_b+COLOR::unicode_end;
	std::string objectColor = COLOR::unicode_escape+COLOR::bg_magenta_b+COLOR::unicode_end;
	std::string debugColor = COLOR::unicode_escape+COLOR::fg_white_b+COLOR::separator+COLOR::bg_black+COLOR::separator+COLOR::bold_on+COLOR::unicode_end;

	// Allocate FrameBuffer
	this->FrameBuffer = new PIXEL*[this->terminalHeight];
	for (int h = 0; h < this->terminalHeight; h++)
	{
		this->FrameBuffer[h] = new PIXEL[this->terminalWidth];
		for (int w = 0; w < this->terminalWidth; w++)
		{
			this->FrameBuffer[h][w].set_coordinate(w, h);
			this->FrameBuffer[h][w].ascii.assign(bgColor);
			this->FrameBuffer[h][w].holder = ' ';

			if (this->map->is_map_object(w, h) != -1)
			{
				this->FrameBuffer[h][w].ascii.assign(mapColor);
			}

			if (this->is_object(w, h))
			{
				this->FrameBuffer[h][w].ascii.assign(objectColor);
			} else
			{
				if ( h == currentHeight && w >= 1 && stringIterator < string_length)
				{
					if (this->debug[stringIterator] != ',')
					{
						this->FrameBuffer[h][w].holder = this->debug[stringIterator];
						this->FrameBuffer[h][w].ascii.assign(debugColor);
						stringIterator++;
					} else
					{
						stringIterator++;
						currentHeight++;
					}
				}
			}
		}
	}
	return true;
}

bool ENGINE::draw_frame()
{
	if (!this->INIT) { return this->INIT; }

	// Terminal Rollback
	std::cout << COLOR::unicode_escape+"H";

	// Redraw
	for (int h = 0; h < this->terminalHeight; h++)
	{
		for (int w = 0; w < this->terminalWidth; w++)
		{
			std::cout << this->FrameBuffer[h][w].ascii + this->FrameBuffer[h][w].holder + COLOR::reset;
			std::flush(std::cout);
		}

		if (h != (this->terminalHeight - 1))
		{
			std::cout << std::endl;
		}

		// Exit loop when thread_exit triggered
		if (this->thread_exit) { break; }
	}

	return true;
}

void ENGINE::terminate_engine()
{
	// Free FrameBuffer
	for (int h = 0; h < this->terminalHeight; h++)
	{
			delete[] this->FrameBuffer[h];
	}
	delete[] this->FrameBuffer;
}
