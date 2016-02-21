#include <GLUT/glut.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Block.h"
#include <string.h>

#define head snake[0]

std::vector<Block> snake;
Block food;

int headDirection;
bool playerTurn;
int playerScore;

std::string commands[5];

bool inGame;

class Game {
public:
	int delay = 150;
	int windowSize = 400;
	int startingLenth = 3;
	int blockSize = 10;
	int flashPerFood = 1;

}settings;


void draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);


	glColor3f(1, 0, 0);
	food.draw();

	glColor3f(1, 1, 1);
	for(int i = 0; i < snake.size(); ++i) {
		snake[i].draw();
	}

	glEnd();

	glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
	if(playerTurn) {
		switch(key) {
		case GLUT_KEY_UP:
			if(headDirection != 2) {
				headDirection = 3;
			}
			break;
		case GLUT_KEY_DOWN:
			if(headDirection != 3) {
				headDirection = 2;
			}
			break;
		case GLUT_KEY_LEFT:
			if(headDirection != 1) {
				headDirection = 0;
			}
			break;
		case GLUT_KEY_RIGHT:
			if(headDirection != 0) {
				headDirection = 1;
			}
			break;
		}
	}

	playerTurn = false;
}

void timer(int value) {

	for(int i = snake.size() - 1; i > 0; --i) {
		snake[i].setBlock(snake[i-1].getX(), snake[i-1].getY(), settings.blockSize);
	}

	switch(headDirection) {
	case 0:
		if(head.getX() - settings.blockSize >= 0)
			head.setBlock(head.getX() - settings.blockSize, head.getY(), settings.blockSize);
		else if(head.getX() - settings.blockSize < 0) {
			head.setBlock(settings.windowSize - settings.blockSize, head.getY(), settings.blockSize);
		}
		break;
	case 1:
		if(head.getX() + settings.blockSize < settings.windowSize)
			head.setBlock(head.getX() + settings.blockSize, head.getY(), settings.blockSize);
		else if(head.getX() + settings.blockSize >= settings.windowSize) {
			head.setBlock(0, head.getY(), settings.blockSize);
		}
		break;
	case 2:
		if(head.getY() + settings.blockSize < settings.windowSize)
			head.setBlock(head.getX(), head.getY()  + settings.blockSize, settings.blockSize);
		else if(head.getY() + settings.blockSize >= settings.windowSize) {
			head.setBlock(head.getX(), 0, settings.blockSize);
		}
		break;
		break;
	case 3:
		if(head.getY() - settings.blockSize >= 0)
			head.setBlock(head.getX(), head.getY()  - settings.blockSize, settings.blockSize);
		else if(head.getY() - settings.blockSize < 0) {
			head.setBlock(head.getX(), settings.windowSize - settings.blockSize, settings.blockSize);
		}
		break;
	}

	if(food.getX() == head.getX() && food.getY() == head.getY()) {
		int x, y;

		snake.reserve(settings.flashPerFood);

		bool sd = true;
		while(sd) {

			x = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
			y = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;

			for(int i = 0; i < snake.size(); ++i) {
				if(snake[i].getX() == x && snake[i].getY() == y) {
					x = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
					y = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
				}
				else {
					sd = false;
				}
			}
		}

		food.setBlock(x, y, settings.blockSize);

		for(int i = 1; i <= settings.flashPerFood; ++i) {
			Block flash;
			flash.setBlock(-10 - i*settings.blockSize, head.getY(), settings.blockSize);
			snake.push_back(flash);
		}
	}

	for(int i = 1; i < snake.size() - 1; ++i) {
		if(head.getX() == snake[i].getX() && head.getY() == snake[i].getY()) {
			system("say азазазаза заза заза");
			exit(0);
		}
	}

	playerTurn = true;

	glutPostRedisplay();
	glutTimerFunc(settings.delay, timer, 0);
}

int main(int argc, char **argv) {

	commands[0] = "help";
	commands[1] = "start";
	commands[2] = "set";
	commands[3] = "lvl";
	commands[4] = "speed";

	inGame = true;


	std::cout << "Hello in da funcking snake" << std::endl;
	std::cout << "Write /help for commands" << std::endl;

	while(inGame) {

		std::string a;
		std::cin >> a;

		if(a == commands[0]) {
			std::cout << "start: start game." << std::endl;
			std::cout << "set: set window size." << std::endl;
			std::cout << "lvl: set the amount of flash/food." << std::endl;
			std::cout <<"speed: set the speed." << std::endl;

		}
		else if(a == commands[1]) {
			inGame = false;
			break;
		}
		else if(a == commands[2]) {
			std::cout << "Enter window size." << std::endl;
			std::cin >> settings.windowSize;
		}
		else if(a == commands[3]) {
			std::cout << "Enter the amount." << std::endl;
			std::cin >> settings.flashPerFood;
		}
		else if(a == commands[4]) {
			std::cout << "Enter new speed in millisecs." << std::endl;
			std::cin >> settings.delay;
		}

	}

	for(int i = 0; i < settings.startingLenth; ++i) {
		Block flash;
		flash.setBlock(settings.windowSize/2 + i*settings.blockSize, settings.windowSize/2, settings.blockSize);
		snake.push_back(flash);
	}

	headDirection = 0;
	playerTurn = true;
	playerScore = settings.startingLenth;

	int x, y;

	bool sd = true;
	while(sd) {

	 x = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
	 y = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;

		for(int i = 0; i < snake.size(); ++i) {
			if(snake[i].getX() == x && snake[i].getY() == y) {
				x = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
				y = (((int)rand())%(settings.windowSize/settings.blockSize)) * settings.blockSize;
			}
			else {
				sd = false;
			}
		}
	}

	food.setBlock(x, y, settings.blockSize);

	commands[0] = "help";
	commands[1] = "start";
	commands[2] = "set";
	commands[3] = "lvl";

	inGame = true;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(settings.windowSize , settings.windowSize);
	glutInitWindowPosition(300, 550);
	glutCreateWindow("Python v.0.2");
	glutDisplayFunc(draw);
	glutSpecialFunc(keyboard);
	glutTimerFunc(settings.delay, timer, 0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, settings.windowSize, settings.windowSize, 0, -1, 1);

	glutMainLoop();
	return 0;
}

