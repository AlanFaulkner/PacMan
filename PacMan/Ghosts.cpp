#include "Ghosts.h"

Ghosts::Ghosts()
{
	srand(time(NULL));
}

//void Ghosts::move_Ghosts()
//{
//	switch (red_Ghost(direction, redGhost_xpos, redGhost_ypos)) {
//	case (0) :
//		direction++;
//		if (direction > 4)
//			direction = rand() % 4 + 1;
//		break;
//	case (1) :
//		redGhost_ypos = redGhost_ypos - 1;
//		break;
//	case (3) :
//		redGhost_ypos = redGhost_ypos + 1;
//		break;
//	case(2) :
//		redGhost_xpos = redGhost_xpos - 1;
//		break;
//	case(4) :
//		redGhost_xpos = redGhost_xpos + 1;
//		break;
//	}
//}
//
//int Ghosts::red_Ghost(int number, int redGhost_xpos, int redGhost_ypos)
//{
//	switch (number) {
//	case (1) :
//		if (gameMap[redGhost_ypos - 1][redGhost_xpos] != 1) {
//			gameMap[redGhost_ypos - 1][redGhost_xpos] = 20;
//			gameMap[redGhost_ypos][redGhost_xpos] = 2;
//			redGhost_ypos--;
//			return 1;
//			break;
//		}
//			 return 0;
//			 break;
//
//	case (2) :
//		if (gameMap[redGhost_ypos][redGhost_xpos - 1] != 1) {
//			gameMap[redGhost_ypos][redGhost_xpos - 1] = 20;
//			gameMap[redGhost_ypos][redGhost_xpos] = 2;
//			redGhost_xpos = redGhost_xpos - 1;
//			return 2;
//			break;
//		}
//			 return 0;
//			 break;
//
//	case (3) :
//		if (gameMap[redGhost_ypos + 1][redGhost_xpos] != 1) {
//			gameMap[redGhost_ypos + 1][redGhost_xpos] = 20;
//			gameMap[redGhost_ypos][redGhost_xpos] = 2;
//			redGhost_ypos++;
//			return 3;
//			break;
//		}
//			 return 0;
//			 break;
//
//	case (4) :
//		if (gameMap[redGhost_ypos][redGhost_xpos + 1] != 1) {
//			gameMap[redGhost_ypos][redGhost_xpos + 1] = 20;
//			gameMap[redGhost_ypos][redGhost_xpos] = 2;
//			redGhost_xpos++;
//
//			return 4;
//			break;
//		}
//			 return 0;
//			 break;
//	}
//}
