#ifndef BLOCK_H_
#define BLOCK_H_

class Block {
private:
	int x;
	int y;
	int width;
public:
	void setBlock(int _x, int _y, int _width);
	Block();
	void draw();
	int getX();
	int getY();
	int getS();
};

#endif /* BLOCK_H_ */

