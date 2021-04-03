#include "main.hpp"

// All Constructors
Coor::Coor() : x(0), y(0) {}

Status::Status() : isUp(false), isDown(false), isLeft(false), isRight(true) {}

Snake::Snake() : total(1) {}

Food::Food() : isFood(false) {}

bool Coor::operator == (Coor &obj) {
	if (this->x == obj.x && this->y == obj.y) return true;
	else return false;
}

// Member functions of class Snake
void Snake::listenKeyboard(bool isUp, bool isDown, bool isLeft, bool isRight) {
	if (statusSnake.isUp && isDown) {
		statusSnake.isUp = true;
		return;
	}
	if (statusSnake.isDown && isUp) {
		statusSnake.isDown = true;
		return;
	}
	if (statusSnake.isLeft && isRight) {
		statusSnake.isLeft = true;
		return;
	}
	if (statusSnake.isRight && isLeft) {
		statusSnake.isRight = true;
		return;
	}
	statusSnake.isUp    = isUp;
	statusSnake.isDown  = isDown;
	statusSnake.isLeft  = isLeft;
	statusSnake.isRight = isRight;
}

void Snake::update() {
	for (int i = total - 1; i > 0; --i) {
		coorSnake[i] = coorSnake[i - 1];
	}
	if (statusSnake.isUp) 	 coorSnake[0].y -= 1;
	if (statusSnake.isDown)  coorSnake[0].y += 1;
	if (statusSnake.isLeft)  coorSnake[0].x -= 1;
	if (statusSnake.isRight) coorSnake[0].x += 1;

	if (coorSnake[0].x < 0) coorSnake[0].x = WIDTH_CONSOLE / SCALE - 1;
	if (coorSnake[0].x > WIDTH_CONSOLE / SCALE - 1) coorSnake[0].x = 0;
	if (coorSnake[0].y < 0) coorSnake[0].y = HEIGHT_CONSOLE / SCALE - 1;
	if (coorSnake[0].y > HEIGHT_CONSOLE / SCALE - 1) coorSnake[0].y = 0;

	for (int i = 1; i < total; ++i) {
		if (coorSnake[0] == coorSnake[i]) total = 1;
	}

}

unsigned int &Snake::length() {
	return total;
}

Coor *Snake::getPosition() {
	return coorSnake;
}

// Member functions of class Food
void Food::update(bool isFood) {
	this->isFood = isFood;
	generateFood();
}

void Food::generateFood() {
	if (!isFood) {
		coorFood.x = rand() % (WIDTH_CONSOLE / SCALE);
		coorFood.y = rand() % (HEIGHT_CONSOLE / SCALE);
		isFood = true;
	}
}

Coor &Food::getPosition() {
	return coorFood;
}

int main() {
	RenderWindow window(VideoMode(WIDTH_CONSOLE, HEIGHT_CONSOLE), "SNAKE!");
	Event event;
	Texture texture;
	Sprite sprite_snake, sprite_food;
	Snake snake;
	Food food[5];

	window.setFramerateLimit(30);

	texture.loadFromFile(TILES_IMG);
	texture.setSmooth(true);

	sprite_snake.setTexture(texture);
	sprite_food.setTexture(texture);

	srand(time(NULL));

	for (int i = 0; i < 5; ++i) {
		food[i].update(false);
	}

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up)    snake.listenKeyboard(true, false, false, false);
				if (event.key.code == Keyboard::Down)  snake.listenKeyboard(false, true, false, false);
				if (event.key.code == Keyboard::Left)  snake.listenKeyboard(false, false, true, false);
				if (event.key.code == Keyboard::Right) snake.listenKeyboard(false, false, false, true);
			}
		}
		snake.update();
		for (int i = 0; i < 5; ++i) {
			if (snake.getPosition()[0] == food[i].getPosition()) {
				food[i].update(false);
				++snake.length();
			}
		}
		window.clear(Color::White);
		for (int i = 0; i < 5; ++i) {
			sprite_food.setPosition(food[i].getPosition().x * SCALE, food[i].getPosition().y * SCALE);
			sprite_food.setTextureRect(IntRect(WIDTH_IMG * (rand() % 7), 0, SCALE, SCALE));
			window.draw(sprite_food);
		}


		int count = 0;
		for (int i = 0; i < snake.length(); ++i) {
			sprite_snake.setPosition(snake.getPosition()[i].x * SCALE, snake.getPosition()[i].y * SCALE);
			sprite_snake.setTextureRect(IntRect(WIDTH_IMG * count, 0, SCALE, SCALE));
			++count;
			if (count == 6) count = 0;
			window.draw(sprite_snake);
		}

		window.display();
	}

	return 0;
}