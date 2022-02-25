# PHYSICS SIMULATOR
A Physics Simulation Engine for Terminal for Windows and Linux Platform.

## LICENSE
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

## REQUIREMENTS
This game requires you to have a C++ build environment installed on your computer.
(I personally used MingW-w64 to install gcc compiler for windows)

It also requires Cmake and make installed. You can also install other programs like
ninja that is compactble with cmake instead of make.

## BUILD INSTRUCTIONS

1. Download the zip ans unzip or clone the project
2. Go to the downloaded directory
3. Go in command prompt or Terminal and type following commands:
4. mkdir build && cd build
5. cmake ..
6. make / ninja / whichever program you use
7. ../physicsSimulator

## SCREENSHOTS
![alt_tag](https://github.com/KrishnenduMarathe/physicsSimulator/blob/main/Media/1.png)

![alt_tag](https://github.com/KrishnenduMarathe/physicsSimulator/blob/main/Media/2.png)

## CONTROLS

#### KEYS       ||    ACTION
#### --------------------------------------------
#####  W         =>    Move UP
#####  A         =>    Move Left
#####  S         =>    Move Down
#####  D         =>    Move Right
#####  `         =>    Exit Simulation
#####  |         =>    Display Debug Window
#####  ?         =>    Start Object Rotation (constant speed)
