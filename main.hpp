#include <SFML/Graphics.hpp>
#include <time.h>

#define TILES_IMG "data/tiles.png"
#define WIDTH_IMG 18
#define WIDTH_CONSOLE 800
#define HEIGHT_CONSOLE 800
#define SCALE 10
#define MAX 500

using namespace sf;

struct Coor {
	int x;
	int y;
	Coor();
	bool operator == (Coor &obj);
};

struct Status {
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;
	Status();
};

class Snake {
private:
	Coor coorSnake[MAX];
	Status statusSnake;
	unsigned int total;
public:
	Snake();
	void listenKeyboard(bool isUp, bool isDown, bool isLeft, bool isRight);
	void update();
	unsigned int &length();
	Coor *getPosition();
};

class Food {
private:
	Coor coorFood;
	bool isFood;
public:
	Food();
	void update(bool isFood);
	void generateFood();
	Coor &getPosition();
};