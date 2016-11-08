#include <iostream>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <SDL.h>

//game related things
enum class GameState { PLAY, EXIT };
GameState _GameState;

//pointers related to graphics window
//The window we'll be rendering to
SDL_Window *Main_window = NULL;

//This is the main renenderer
SDL_Renderer *Main_render = NULL;

//this is the surface used for loading
SDL_Surface *loadSurface = NULL;

//this is the background image
SDL_Texture *background_text = NULL;

//this is for a tile
SDL_Texture *tile = NULL;

//game variable
int score = 0;
int level = 0;
//PacMan start location
int pacman_xpos = 14;
int pacman_ypos = 18;

//set up game map

#define dot = 0
#define wall = 1
#define space = 2
#define door = 3
#define pill = 4
#define PacMan_Close_right = 5
#define PacMan_open_right = 9
#define PacMan_Close_down = 6
#define PacMan_open_down = 10
#define PacMan_Close_left = 7
#define PacMan_open_left = 11
#define PacMan_Close_up  = 8
#define PacMan_open_up = 12

int gameMap[33][30] =
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 4, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 4, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 3, 3, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
1, 1, 4, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 4, 1, 1,
1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1,
1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void printMap()
{
	//system("cls");
	std::cout << "Score: " << score << std::endl << std::endl;
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 30; j++) {
			if (gameMap[i][j] == 1)
				std::cout << "#";
			else if (gameMap[i][j] == 0)
				std::cout << ".";
			else if (gameMap[i][j] == 2)
				std::cout << " ";
			else if (gameMap[i][j] == 3)
				std::cout << "-";
			else if (gameMap[i][j] == 4)
				std::cout << "0";
			else if (gameMap[i][j] > 4 && gameMap[i][j] < 12)
				std::cout << "C";
			else if (gameMap[i][j] == 20)
				std::cout << "G";
			else if (gameMap[i][j] == 30)
				std::cout << "A";
		}
		std::cout << std::endl;
	}
	std::cout << "y = " << pacman_ypos << " x = " << pacman_xpos << std::endl;
}

void print_map_to_screen()
{

	////loads a background texture

	loadSurface = SDL_LoadBMP("Graphics/Background.bmp");
	if (loadSurface == nullptr) {
		SDL_DestroyRenderer(Main_render);
		SDL_DestroyWindow(Main_window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	background_text = SDL_CreateTextureFromSurface(Main_render, loadSurface);
	SDL_FreeSurface(loadSurface);
	if (background_text == nullptr) {
		SDL_DestroyRenderer(Main_render);
		SDL_DestroyWindow(Main_window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	//First clear the renderer
	SDL_RenderClear(Main_render);
	//Draw the texture
	SDL_RenderCopy(Main_render, background_text, NULL, NULL);

	int C = 0;
	for (int i = 0; i<34; i++) {
		for (int j = 0; j<30; j++) {
			if (gameMap[i][j] != 2) {
				C = gameMap[i][j];

				//load tile
				SDL_Rect offset;
				offset.x = 10 * j;
				offset.y = 10 * i;
				offset.w = 10;
				offset.h = 10;

				switch (C) {
				case (0) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/Dot.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\2.bmp", SDL_GetError());
					}
					break;
				case (1) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/Block.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\4.bmp", SDL_GetError());
					}
					break;
				case (3) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/Gate.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\16.bmp", SDL_GetError());
					}
					break;
				case (4) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/PowerPill.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\32.bmp", SDL_GetError());
					}
					break;
				case (5) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/PacMan_closed_right.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\64.bmp", SDL_GetError());
					}
					break;
				case (9) :
					////Load tile image
					loadSurface = SDL_LoadBMP("Graphics/PacMan_open_right.bmp");
					if (loadSurface == NULL)
					{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\64.bmp", SDL_GetError());
					}
					break;
					case (6) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_closed_down.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\128.bmp", SDL_GetError());
						}
						break;
					case (10) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_open_down.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\256.bmp", SDL_GetError());
						}
						break;
					case (7) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_closed_left.bmp");
						/*if (loadSurface == NULL)
						{
						printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\512.bmp", SDL_GetError());
						}*/
						break;
					case (11) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_open_left.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\1024.bmp", SDL_GetError());
						}
						break;
					case (8) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_closed_up.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\1024.bmp", SDL_GetError());
						}
						break;
					case (12) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/PacMan_open_up.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\1024.bmp", SDL_GetError());
						}
						break;
					case (30) :
						////Load tile image
						loadSurface = SDL_LoadBMP("Graphics/RedGhost.bmp");
						if (loadSurface == NULL)
						{
							printf("Unable to load image %s! SDL Error: %s\n", "\Graphics\1024.bmp", SDL_GetError());
						}
						break;
				}

				tile = SDL_CreateTextureFromSurface(Main_render, loadSurface);
				SDL_FreeSurface(loadSurface);
				if (background_text == nullptr) {
					SDL_DestroyRenderer(Main_render);
					SDL_DestroyWindow(Main_window);
					std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
					SDL_Quit();
				}

				SDL_RenderCopy(Main_render, tile, NULL, &offset);
			}
		}
	}
	//Update the screen
	SDL_RenderPresent(Main_render);
}



//check to see if all dots are eaten (not complete yet!)
void check_Map()
{
	int numDots = 0;
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 30; j++){
			if (gameMap[i][j] == 0)
				numDots++;
		}
	}

	if (numDots == 0) {
		loadSurface = SDL_LoadBMP("Graphics/Level_Clear.bmp");
		if (loadSurface == nullptr) {
			SDL_DestroyRenderer(Main_render);
			SDL_DestroyWindow(Main_window);
			std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		background_text = SDL_CreateTextureFromSurface(Main_render, loadSurface);
		SDL_FreeSurface(loadSurface);
		if (background_text == nullptr) {
			SDL_DestroyRenderer(Main_render);
			SDL_DestroyWindow(Main_window);
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		//clear the renderer
		SDL_RenderClear(Main_render);
		//Draw the texture
		SDL_RenderCopy(Main_render, background_text, NULL, NULL);

		SDL_Delay(2000);
		level++;
	}
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(Main_window);
	Main_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

//int choose_direction(int current_direction, int Ghost_posX, int Ghost_posY, int PacMan_posX, int PacMan_posY)
//{
//	switch (current_direction) {
//	case(1) :
//		if (PacMan_posX > Ghost_posX && gameMap[Ghost_posY][Ghost_posX + 1] != 1){
//			return 2;
//			break;
//		}
//
//		else if (PacMan_posX < Ghost_posX && gameMap[Ghost_posY][Ghost_posX - 1] != 1) {
//			return 4;
//			break;
//		}
//
//	case(2) :
//		if (PacMan_posY > Ghost_posY && gameMap[Ghost_posY + 1][Ghost_posX] != 1) {
//			return 3;
//			break;
//		}
//
//		else if (PacMan_posY < Ghost_posY && gameMap[Ghost_posY - 1][Ghost_posX] != 1) {
//			return 1;
//			break;
//		}
//
//	case(3) :
//		if (PacMan_posX > Ghost_posX && gameMap[Ghost_posY][Ghost_posX + 1] != 1) {
//			return 2;
//			break;
//		}
//
//		else if (PacMan_posX < Ghost_posX && gameMap[Ghost_posY][Ghost_posX - 1] != 1) {
//			return 4;
//			break;
//		}
//
//	case(4) :
//		if (PacMan_posY > Ghost_posY && gameMap[Ghost_posY + 1][Ghost_posX] != 1) {
//			return 3;
//			break;
//		}
//
//		else if (PacMan_posY < Ghost_posY && gameMap[Ghost_posY - 1][Ghost_posX] != 1) {
//			return 1;
//			break;
//		}
//
//	}
//}
//
//int yellowGhost(int direction, int yellow_Ghost_posX, int yellow_Ghost_posY, int PacMan_posX, int PacMan_posY)
//{
//	switch (Move_Ghost(direction, yellow_Ghost_posX, yellow_Ghost_posY)) {
//	case (0) :
//		direction++;
//		break;
//
//	case (1) :
//		if (check_intersection(direction, yellow_Ghost_posX, yellow_Ghost_posY) == true){
//			direction = choose_direction(direction, yellow_Ghost_posX, yellow_Ghost_posY, PacMan_posX, PacMan_posY);
//		return direction;
//		break;
//	}
//		else {
//			return 1;
//			break;
//		}
//
//	case (2):
//		if (check_intersection(direction, yellow_Ghost_posX, yellow_Ghost_posY) == true) {
//			direction = choose_direction(direction, yellow_Ghost_posX, yellow_Ghost_posY,PacMan_posX,PacMan_posY);
//			return direction;
//			break;
//		}
//		else {
//			return 1;
//			break;
//		}
//	case (3):
//		if (check_intersection(direction, yellow_Ghost_posX, yellow_Ghost_posY) == true) {
//			direction = choose_direction(direction, yellow_Ghost_posX, yellow_Ghost_posY, PacMan_posX, PacMan_posY);
//			return direction;
//			break;
//		}
//		else {
//			return 1;
//			break;
//		}
//	case (4):
//		if (check_intersection(direction, yellow_Ghost_posX, yellow_Ghost_posY) == true) {
//			direction = choose_direction(direction, yellow_Ghost_posX, yellow_Ghost_posY, PacMan_posX, PacMan_posY);
//			return direction;
//			break;
//		}
//		else {
//			return 1;
//			break;
//		}
//	}
//}
//
//// Will determin if the ghost is at an intersection returning either True or False.
//bool check_intersection(int direction_of_travel, int Ghost_posX, int Ghost_posY)
//{
//	switch (direction_of_travel) {
//	case (1) :
//		if (gameMap[Ghost_posY][Ghost_posX + 1] != 1 || gameMap[Ghost_posY][Ghost_posX - 1] != 1) {
//			return true;
//			break;
//		}
//		else {
//			return false;
//			break;
//		}
//
//	case (2) :
//		if (gameMap[Ghost_posY + 1][Ghost_posX] != 1 || gameMap[Ghost_posY + 1][Ghost_posX] != 1) {
//			return true;
//			break;
//		}
//		else {
//			return false;
//			break;
//		}
//
//	case (3) :
//		if (gameMap[Ghost_posY][Ghost_posX - 1] != 1 || gameMap[Ghost_posY][Ghost_posX + 1] != 1) {
//			return true;
//			break;
//		}
//		else {
//			return false;
//			break;
//		}
//
//	case (4) :
//		if (gameMap[Ghost_posY - 1][Ghost_posX] != 1 || gameMap[Ghost_posY + 1][Ghost_posX] != 1) {
//			return true;
//			break;
//		}
//		else {
//			return false;
//			break;
//		}
//	}
//}

//Check if possible to move one step in given direction
int Move_Ghost(int direction_of_travel, int Ghost_posX, int Ghost_posY)
{
	int i = 0;
	switch (direction_of_travel) {
	case (1):
		if (gameMap[Ghost_posY-1][Ghost_posX] != 1) { //will travel in direction of pacman untill it hits wall
			i = gameMap[Ghost_posY][Ghost_posX]; // copy current type to temp value i
			gameMap[Ghost_posY-1][Ghost_posX] = 30; // move ghost along one place
			gameMap[Ghost_posY][Ghost_posX] = i;//sets tile behind ghost back to what it was before
			return 1; // to keep going in same direction - right
			break;
		}

		else {
			return 0;
			break;
		}

		case (2):
			if (gameMap[Ghost_posY][Ghost_posX + 1] != 1) { //will travel in direction of pacman untill it hits wall
				i = gameMap[Ghost_posY][Ghost_posX]; // copy current type to temp value i
				gameMap[Ghost_posY][Ghost_posX + 1] = 30; // move ghost along one place
				gameMap[Ghost_posY][Ghost_posX] = i;//sets tile behind ghost back to what it was before
				return 2; // to keep going in same direction - right
				break;
			}

			else {
				return 0;
				break;
			}

		case (3):
			if (gameMap[Ghost_posY + 1][Ghost_posX] != 1) { //will travel in direction of pacman untill it hits wall
				i = gameMap[Ghost_posY][Ghost_posX]; // copy current type to temp value i
				gameMap[Ghost_posY + 1][Ghost_posX] = 30; // move ghost along one place
				gameMap[Ghost_posY][Ghost_posX] = i;//sets tile behind ghost back to what it was before
				return 3; // to keep going in same direction - right
				break;
			}

			else {
				return 0;
				break;
			}

		case (4):
			if (gameMap[Ghost_posY][Ghost_posX - 1] != 1) { //will travel in direction of pacman untill it hits wall
				i = gameMap[Ghost_posY][Ghost_posX]; // copy current type to temp value i
				gameMap[Ghost_posY][Ghost_posX - 1] = 30; // move ghost along one place
				gameMap[Ghost_posY][Ghost_posX] = i;//sets tile behind ghost back to what it was before
				return 4; // to keep going in same direction - right
				break;
			}

			else {
				return 0;
				break;
			}
	}
}

//find a point in array ie pacman!
int orange_Ghost(int number, int Pacman_xpos, int Pacman_ypos, int orangeGhost_xpos, int orangeGhost_ypos)
{
	int i = 0;
	switch (number) {

	case(1) :
		//travel loop - direction = Right.
		if (gameMap[orangeGhost_ypos ][orangeGhost_xpos + 1] != 1) { //will travel in direction of pacman untill it hits wall
			i = gameMap[orangeGhost_ypos][orangeGhost_xpos + 1]; // copy current type to temp value i
			gameMap[orangeGhost_ypos][orangeGhost_xpos + 1] = 30; // move ghost along one place
			gameMap[orangeGhost_ypos][orangeGhost_xpos] = i;//sets tile behind ghost back to what it was before
			return 1; // to keep going in same direction - right
			break;
		}

			//change direction
		else if (orangeGhost_xpos < Pacman_xpos) {
			return 2; // down
			break;
		}
		else {
			return 4;// up
			break;
		}


	case(2) :
		//travel loop. - direction = Down.
		if (gameMap[orangeGhost_ypos + 1][orangeGhost_xpos] != 1) { //will travel in direction of pacman untill it hits wall
			i = gameMap[orangeGhost_ypos + 1][orangeGhost_xpos]; // copy current type to temp value i
			gameMap[orangeGhost_ypos + 1][orangeGhost_xpos] = 30; // move ghost along one place
			gameMap[orangeGhost_ypos][orangeGhost_xpos] = i;//sets tile behind ghost back to what it was before
			return 2; // to keep going in same direction - down
			break;
		}
			//change direction
		else if (orangeGhost_xpos < Pacman_xpos) {
			return 1; // right
			break;
		}
		else {
			return 3;// left
			break;
		}

	case(3) :
		//travel loop. - direction = Left.
		if (gameMap[orangeGhost_ypos][orangeGhost_xpos - 1] != 1) { //will travel in direction of pacman untill it hits wall
			i = gameMap[orangeGhost_ypos][orangeGhost_xpos - 1]; // copy current type to temp value i
			gameMap[orangeGhost_ypos][orangeGhost_xpos - 1] = 30; // move ghost along one place
			gameMap[orangeGhost_ypos][orangeGhost_xpos] = i;//sets tile behind ghost back to what it was before
			return 3; // to keep going in same direction - left
			break;
		}
			//change direction
		else if (orangeGhost_ypos < Pacman_ypos) {
			return 2; // down
			break;
		}
		else {
			return 4;// up
			break;
		}

	case(4) :
		//travel loop. - direction = Up.
		if (gameMap[orangeGhost_ypos-1][orangeGhost_xpos] != 1) { //will travel in direction of pacman untill it hits wall
			i = gameMap[orangeGhost_ypos-1][orangeGhost_xpos]; // copy current type to temp value i
			gameMap[orangeGhost_ypos-1][orangeGhost_xpos] = 30; // move ghost along one place
			gameMap[orangeGhost_ypos][orangeGhost_xpos] = i;//sets tile behind ghost back to what it was before
			return 4; // to keep going same direction - up
			break;
		}

			//change direction
		else if (orangeGhost_xpos < Pacman_xpos) {
			return 1; // right
			break;
		}
		else {
			return 3;// left
			break;
		}

	}
}

int red_Ghost(int number, int redGhost_xpos, int redGhost_ypos)
{
	switch (number) {
		case (1) :
			if (gameMap[redGhost_ypos - 1][redGhost_xpos] !=1) {
				gameMap[redGhost_ypos - 1][redGhost_xpos] = 20;
				gameMap[redGhost_ypos][redGhost_xpos] = 2;
				redGhost_ypos--;
				return 1;
				break;
			}
				return 0;
				break;
		
		case (2) :
			if (gameMap[redGhost_ypos][redGhost_xpos - 1] != 1) {
				gameMap[redGhost_ypos][redGhost_xpos - 1] = 20;
				gameMap[redGhost_ypos][redGhost_xpos] = 2;
				redGhost_xpos = redGhost_xpos - 1;
				return 2;
				break;
			}
				 return 0;
				 break;

		case (3) :
			if (gameMap[redGhost_ypos + 1][redGhost_xpos] != 1) {
				gameMap[redGhost_ypos + 1][redGhost_xpos] = 20;
				gameMap[redGhost_ypos][redGhost_xpos] = 2;
				redGhost_ypos ++;
				return 3;
				break;
			}
				return 0;
				break;

		case (4) :
			if (gameMap[redGhost_ypos][redGhost_xpos + 1] != 1) {
				gameMap[redGhost_ypos][redGhost_xpos + 1] = 20;
				gameMap[redGhost_ypos][redGhost_xpos] = 2;
				redGhost_xpos++;

				return 4;
				break;
			}
				 return 0;
				 break;
	}
}

int main(int argc, char **argv)
{

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL could not initialize!" << std::endl;
		}

		//How to open a window - the window object needs to be a pointer
		Main_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 330, SDL_WINDOW_SHOWN);
		if (Main_window == nullptr) {
			std::cout << "Could not create a SDL window" << std::endl;
		}

		//Create main render
		Main_render = SDL_CreateRenderer(Main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (Main_render == nullptr) {
			SDL_DestroyWindow(Main_window);
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		gameMap[pacman_ypos][pacman_xpos] = 5;
		/*int redGhost_ypos = 15;
		int redGhost_xpos = 10;*/
		int orangeGhost_xpos = 16;
		int orangeGhost_ypos = 12;
		gameMap[orangeGhost_ypos][orangeGhost_xpos] = 30;

		srand(time(NULL));

	printMap();
	//int number = rand() % 4 + 1;
	int number = 3;
	print_map_to_screen();
	while (_GameState != GameState::EXIT) {
		//std::cout << "init ghost x: " << redGhost_xpos << " init ghost y: " << redGhost_ypos << std::endl;

		//switch (red_Ghost(number, redGhost_xpos, redGhost_ypos)){
		//case (0) :
		//	//number=rand()%4+1;
		//	number++;
		//	if (number > 4)
		//		number = rand() % 4 + 1;
		//	break;
		//case (1):
		//	redGhost_ypos = redGhost_ypos - 1;
		//	break;
		//case (3):
		//	redGhost_ypos = redGhost_ypos + 1;
		//	break;
		//case(2):
		//	redGhost_xpos = redGhost_xpos - 1;
		//	break;
		//case(4):
		//	redGhost_xpos = redGhost_xpos + 1;
		//	break;
		//}

		switch (orange_Ghost(number, pacman_xpos, pacman_ypos, orangeGhost_xpos, orangeGhost_ypos)) {

		case (1) :
				orangeGhost_xpos = orangeGhost_xpos++;
				number = 1;
				break;
		case (2) :
				orangeGhost_ypos = orangeGhost_ypos++;
				number = 2;
				break;
		case (3) :
				orangeGhost_xpos = orangeGhost_xpos--;
				number = 3;
				break;
		case (4) :
				orangeGhost_ypos = orangeGhost_ypos--;
				number = 4;
				break;
		}
		printMap();
		//print_map_to_screen();
		std::cout << "--------" << std::endl;
		//std::cout << "ghost x: " << redGhost_xpos << " ghost y: " << redGhost_ypos << " number: "<<number<<std::endl;
		SDL_Delay(100);
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {
			case SDL_QUIT:
				_GameState = GameState::EXIT;
				std::cout << "close button" << std::endl;
				break;

				case SDL_KEYDOWN:

				switch (evnt.key.keysym.sym)
				{

						case SDLK_UP:
							if (gameMap[pacman_ypos-1][pacman_xpos] != 1) {

								if (gameMap[pacman_ypos-1][pacman_xpos] == 0)
									score++;
								if (gameMap[pacman_ypos][pacman_xpos] > 4 && gameMap[pacman_ypos][pacman_xpos] < 9)
								gameMap[pacman_ypos-1][pacman_xpos] = 12;
								else gameMap[pacman_ypos - 1][pacman_xpos] = 8;
								gameMap[pacman_ypos][pacman_xpos] = 2;
								pacman_ypos = pacman_ypos - 1;
							}
							std::cout << std::endl << "up" << std::endl;
							printMap();
							print_map_to_screen();
							break;

						case SDLK_DOWN:
							if (gameMap[pacman_ypos + 1][pacman_xpos] != 1) {

								if (gameMap[pacman_ypos + 1][pacman_xpos] == 0)
									score++;
								if (gameMap[pacman_ypos][pacman_xpos] > 4 && gameMap[pacman_ypos][pacman_xpos] < 9)
									gameMap[pacman_ypos + 1][pacman_xpos] = 10;
								else gameMap[pacman_ypos + 1][pacman_xpos] = 6;
								gameMap[pacman_ypos][pacman_xpos] = 2;
								pacman_ypos = pacman_ypos + 1;
							}
							std::cout << std::endl << "down" << std::endl;
							printMap();
							print_map_to_screen();
							break;

				case SDLK_LEFT:
					
					if (gameMap[pacman_ypos][pacman_xpos - 1] != 1) {
						
						if (gameMap[pacman_ypos][pacman_xpos - 1] == 0)
							score++;
						if (gameMap[pacman_ypos][pacman_xpos] > 4 && gameMap[pacman_ypos][pacman_xpos] < 9)
							gameMap[pacman_ypos][pacman_xpos - 1] = 11;
						else gameMap[pacman_ypos][pacman_xpos - 1] = 7;
						gameMap[pacman_ypos][pacman_xpos] = 2;
						pacman_xpos = pacman_xpos - 1;
						//screen warp
						if (pacman_xpos == 0) {
							pacman_xpos = 29;
							gameMap[15][0] = 2;
						}

					}
					
					std::cout << std::endl << "left" << std::endl;
					printMap();
					print_map_to_screen();
					break;

						case SDLK_RIGHT:

							if (gameMap[pacman_ypos][pacman_xpos + 1] != 1) {

								if (gameMap[pacman_ypos][pacman_xpos + 1] == 0)
									score=score+10;
								if (gameMap[pacman_ypos][pacman_xpos + 1] == 4)
									score=score+50;
								if (gameMap[pacman_ypos][pacman_xpos] > 4 && gameMap[pacman_ypos][pacman_xpos] < 9)
									gameMap[pacman_ypos][pacman_xpos + 1] = 9;
								else gameMap[pacman_ypos][pacman_xpos + 1] = 5;
								gameMap[pacman_ypos][pacman_xpos] = 2;
								pacman_xpos = pacman_xpos + 1;
								//screen warp
								if (pacman_xpos == 29) {
									pacman_xpos = 0;
									gameMap[15][29] = 2;
								}
							}

							std::cout << std::endl << "right" << std::endl;
							printMap();
							print_map_to_screen();
							break;

						case SDLK_q:
							_GameState = GameState::EXIT;
							std::cout << "q" << std::endl;
							break;


					}
				}
			}
		}
	
	close();
return 0;
	}