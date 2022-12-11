#include "Classes.h"
#include <iostream>
Interface::Interface() {
	loadFont();
	loadTryAgainTexture();
	tryAgain = sf::Sprite(tTryAgain);
	tryAgain.setPosition(260, 650);
	points.setPosition(500, 700);
	cells.resize(400);
	cellsArraySize = cells.size();
	apple = sf::RectangleShape(sf::Vector2f(20, 20));
	apple.setFillColor(sf::Color::Red);
	setApplePosition();
	int j=0,q=0;
	for (int i = 0; i < cellsArraySize; i++) {
		cells[i] = sf::RectangleShape(sf::Vector2f(20,20));
		cells[i].setFillColor(sf::Color{ 120, 214, 145 });
		cells[i].setOutlineThickness(1);
		cells[i].setOutlineColor(sf::Color::Black);
		if (j == 20) {
			j = 0;
			q++;
		}
		cells[i].setPosition(200+j*21, 200+q*21);
		j++;
	}
}
void Interface::isOutOfBorders(float x, float y) {
	if ((x < 200) || (x > 600) || (y < 200) || (y > 600)) gameStop = true;
}
void Interface::setPoints(std::string s) {
	points = sf::Text(s, font);
	points.setFillColor(sf::Color::White);
	points.setPosition(690, 670);
	points.setCharacterSize(65);
}
void Interface::isAppleReached(float x, float y) {
	sf::Vector2f applePos = apple.getPosition();
	float applePosY = applePos.y;
	float applePosX = applePos.x;
	if ((applePosX == x) && (applePosY == y)) {
		setApplePosition();
		changeAppleReachedState();
		applesCollected++;
	}
}

void Interface::setApplePosition() {
	int randApplePosition = rand() % cellsArraySize, j = 0, q = 0;
	for (int i = 0; i < cellsArraySize; i++) {
		if (j == 20) {
			j = 0;
			q++;
		}
		if (randApplePosition == i) apple.setPosition(200 + j * 21, 200 + q * 21);
		j++;
	}
}
void Interface::mouseCords(sf::RenderWindow &w) {
	sf::Vector2i pos = sf::Mouse::getPosition(w); 
	xMouse = pos.x;
	yMouse = pos.y;
}
void Interface::isTryAgainClicked() {
	if ((gameStop) && (tryAgain.getGlobalBounds().contains(xMouse, yMouse))&&(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
		gameStop = false;
		gameReset = true;
	}
}
void Interface::changeAppleReachedState() {
	if (appleReached) appleReached = false;
	else appleReached = true;
}
int Interface::getAppleX(){
	sf::Vector2f applePos = apple.getPosition();
	float applePosX = applePos.x;
	return applePosX;
}
int Interface::getAppleY() {
	sf::Vector2f applePos = apple.getPosition();
	float applePosY = applePos.y;
	return applePosY;
}
Snake::Snake() {
	snakeHead = sf::RectangleShape(sf::Vector2f(20, 20));
	snakeHead.setFillColor(sf::Color::Red);
	gameReset();
}
void Snake::gameReset() {
	snakeHead.setPosition(410, 410);
	snakeTail.resize(2);
	headXCordHistory.resize(snakeTail.size());
	headYCordHistory.resize(snakeTail.size());
	for (int i = 0; i < snakeTail.size(); i++) {
		snakeTail[i] = sf::RectangleShape(sf::Vector2f(20, 20));
		snakeTail[i].setFillColor(sf::Color::Black);
		snakeTail[i].setPosition(431 + i * 21, 410);
		headXCordHistory[i] = 410 + i * 21;
		headYCordHistory[i] = 410;
	}
}
void Snake::addTail() {
	snakeTail.resize(snakeTail.size() + 1);
	snakeTail[snakeTail.size()-1] = sf::RectangleShape(sf::Vector2f(20, 20));
	snakeTail[snakeTail.size()-1].setFillColor(sf::Color::Black);
	snakeTail[snakeTail.size()-1].setPosition(431 + snakeTail.size() * 21, 410);
	headXCordHistory.resize(snakeTail.size());
	headYCordHistory.resize(snakeTail.size());

}
bool Snake::isTailEaten(float x, float y, Snake &snake) {
	for (int i = 0; i < snakeTail.size(); i++) {
		sf::Vector2f tailPos = snake.getSnakeTail(i).getPosition();
		float tailPosX = tailPos.x;
		float tailPosY = tailPos.y;
		if ((x == tailPosX) && (y == tailPosY)) return true;
	}
	return false;
}
bool Snake::isAppleSpawnedOnSnake(float x, float y) {
	float applePosX = x;
	float applePosY = y;
	for (int i = 0; i < snakeTail.size(); i++) {
		sf::Vector2f tailPos = snakeTail[i].getPosition();
		float tailPosX = tailPos.x;
		float tailPosY = tailPos.y;
		if ((tailPosX == applePosX) && (tailPosY == applePosY)) {
			std::cout << "applespawnedonsnake" << std::endl;
			return true;
		}
	}
	return false;
}
void Snake::addHeadWayHistory(float x, float y) {
	int tempX,tempY,tempX1,tempY1;
	tempX = headXCordHistory[0];
	tempY = headYCordHistory[0];
	headXCordHistory[0] = x;
	headYCordHistory[0] = y;
	for (int i = 1; i < snakeTail.size(); i++) {
		tempX1 = headXCordHistory[i];
		tempY1 = headYCordHistory[i];
		headXCordHistory[i] = tempX;
		headYCordHistory[i] = tempY;
		tempX = tempX1;
		tempY = tempY1;
	}
}
bool Moving::straightMoving(float x, float y, Snake &snake, Interface &ui) {
	if (snake.isTailEaten(x, y, snake)) ui.setGameState();
	ui.isOutOfBorders(x, y);
	if (ui.isGameOn()) return true;
	if (straightMovingDirection == 1) up(snake, x, y);
	if (straightMovingDirection == 2) down(snake, x, y);
	if (straightMovingDirection == 3) left(snake, x, y);
	if (straightMovingDirection == 4) right(snake, x, y);
	ui.isAppleReached(x, y);
	if (snake.isAppleSpawnedOnSnake(ui.getAppleX(), ui.getAppleY())) ui.setApplePosition();
	if (ui.getAppleReachedState()) { 
		snake.addTail();
		ui.changeAppleReachedState();
	}
	snake.addHeadWayHistory(x, y);
	moveTail(snake);
}
void Moving::setStraightMoving(int val) {
	int temp;
	temp = straightMovingDirection;
	straightMovingDirection = val;
	if ((temp == 3) && (val == 4)) straightMovingDirection = 3;
	if ((temp == 4) && (val == 3)) straightMovingDirection = 4;
	if ((temp == 1) && (val == 2)) straightMovingDirection = 1;
	if ((temp == 2) && (val == 1)) straightMovingDirection = 2;
}

