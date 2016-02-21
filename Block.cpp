#include "Block.h"
#include<GLUT/glut.h>


void Block::setBlock(int _x, int _y, int _width) {
	x = _x;
	y = _y;
	width = _width;
}

Block::Block() {
	x = 0;
	y = 0;
	width = 0;
}

int Block::getX() {
	return x;
}

int Block::getY() {
	return y;
}

int Block::getS() {
	return width;
}

void Block::draw() {

	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + width);
	glVertex2f(x, y + width);

}

