#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Interface {
	std::vector<sf::RectangleShape> cells;
	sf::RectangleShape apple;
	sf::Font font;
	sf::Text points;
	sf::Texture tTryAgain;
	sf::Sprite tryAgain;
	int cellsArraySize;
	int applesCollected = 0;
	int xMouse, yMouse;
	bool gameStop = false, appleReached = false, gameReset = false;
public:
	Interface();
	int getXMouse() { return xMouse; }
	int getYMouse() { return yMouse; }
	void mouseCords(sf::RenderWindow &window);
	int loadFont(){ if (!font.loadFromFile("font.ttf")) return -1; }
	int loadTryAgainTexture(){ if (!tTryAgain.loadFromFile("tryagain.png")) return -1; }
	int getCellsArraySize() { return cellsArraySize; }
	int getApplesCollected() { return applesCollected; }
	sf::RectangleShape getCells(int val) { return cells[val]; }
	sf::RectangleShape getApple() { return apple; }
	sf::Sprite getTryAgainSprite() { return tryAgain; }
	sf::Text getPoints() { return points; }
	void setPoints(std::string s);
	void isAppleReached(float x, float y);
	void isOutOfBorders(float x, float y);
	void setApplePosition();
	void setApplesCollected() { applesCollected = 0; }
	void setGameState() { gameStop = true; }
	bool isGameOn() { return gameStop; }
	bool getGameResetState() { return gameReset; };
	void setGameResetState() { gameReset = false; }
	bool getAppleReachedState() { return appleReached; }
	void changeAppleReachedState();
	void isTryAgainClicked();
	int getAppleX();
	int getAppleY();
};

class Snake {
	sf::RectangleShape snakeHead;
	std::vector<sf::RectangleShape> snakeTail;
	std::vector<float> headXCordHistory;
	std::vector<float> headYCordHistory;
public:
	Snake();
	void gameReset();
	sf::RectangleShape getSnakeHeadShape() { return snakeHead; }
	sf::RectangleShape getSnakeTail(int val) { return snakeTail[val]; }
	int getSnakeTailLength() { return snakeTail.size(); }
	void setSnakePosition(float x, float y) { snakeHead.setPosition(x, y); }
	void addTail();
	void setSnakeTailPosition(int val) { snakeTail[val].setPosition(headXCordHistory[val], headYCordHistory[val ]); }
	void addHeadWayHistory(float x, float y);
	float getXCordHistory(int val) { return headXCordHistory[val]; }
	float getYCordHistory(int val) { return headYCordHistory[val]; }
	bool isTailEaten(float x, float y, Snake &snake);
	bool isAppleSpawnedOnSnake(float x, float y);
};

class Moving {
private:
	int straightMovingDirection = 3;
public:
	Moving() {}
	void up(Snake& snake, float x, float y) { snake.setSnakePosition(x, y - 21); }
	void down(Snake& snake, float x, float y) { snake.setSnakePosition(x, y + 21); }
	void left(Snake& snake, float x, float y) { snake.setSnakePosition(x-21, y); }
	void right(Snake& snake, float x, float y) { snake.setSnakePosition(x+21, y); }
	void setStraightMoving(int val);
	bool straightMoving(float x, float y, Snake &snake, Interface &ui);
	void moveTail(Snake& snake) {for (int i = 0; i < snake.getSnakeTailLength(); i++) snake.setSnakeTailPosition(i);}
};