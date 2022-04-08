#include "SFML/Graphics.hpp"
#include"globals.h"
class ghost {

public:
	ghost();
	void initGhost(int x, int y, int dir, bool dead, int Gspeed, sf::Color Gcolor);
	bool isdead();
	void drawGhost(sf::RenderWindow& window);
	void printInfo();
	void chase1(int x, int y, int field[31][29]);
	void chase2(int x, int y, int field[31][29]);
	void chase3(int x, int y, int field[31][29]);
	void chase4(int x, int y, int field[31][29]);
	bool getPacman(int x, int y);
	void leave();
	int getXpos();
	int getYpos();

private:

	int xpos;
	int ypos;
	char color;
	int direction;
	bool dead;
	int speed;
	int offset;
	sf::CircleShape shape;

};