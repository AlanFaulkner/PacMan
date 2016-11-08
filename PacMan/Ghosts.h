#pragma once

#include <iostream>
#include <cstdio>
#include <ctime>

enum class Direction {direction, up,down,left,right};

class Ghosts {

	public:

		Ghosts();
		/*void move_Ghosts();*/

	private:

		int direction = rand() % 4 + 1;

		int redGhost_xpos = 14;
		int redGhost_ypos = 12;
		/*int red_Ghost(int direction, int redGhost_xpos, int redGhost_ypos);*/


};