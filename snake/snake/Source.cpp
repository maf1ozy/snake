#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes.h"
#include <ctime>

using namespace sf;
using namespace std;

char* intToStr(int n)
{
	char s[40], t, * temp;
	int i, k;
	int sign = 0;
	i = 0;
	k = n;
	if (k < 0)
	{
		sign = 1;
		k = -k;
	}
	do {
		t = k % 10;
		k = k / 10;
		s[i] = t | 0x30;
		i++;
	} while (k > 0);
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	temp = new char[i];
	k = 0;
	i--;
	while (i >= 0) {
		temp[k] = s[i];
		i--;
		k++;
	}
	temp[k] = '\0';
	return(temp);
}


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	int timePassed,lastTimeMove=0,x=0,y=0;
	sf::Time elapsedTime;
	sf::Clock clock;
	Interface ui;
	Snake snake;
	Moving move;
	RenderWindow window(VideoMode(800, 800), "Snake!");
	while (window.isOpen())
	{
		ui.mouseCords(window);
		ui.isTryAgainClicked();
		if (ui.getGameResetState()) {
			snake.gameReset();
			ui.setGameResetState();
			ui.setApplePosition();
			if (snake.isAppleSpawnedOnSnake(ui.getAppleX(), ui.getAppleY())) ui.setApplePosition();
			ui.setApplesCollected();
		}
		sf::Time deltaTime = clock.restart();
		elapsedTime += deltaTime;
		timePassed = elapsedTime.asMicroseconds();
		sf::Vector2f headPos = snake.getSnakeHeadShape().getPosition();
		float headPosX = headPos.x;
		float headPosY = headPos.y;
		if ((timePassed-lastTimeMove>77777)&&(!ui.isGameOn())) {
			move.straightMoving(headPosX, headPosY, snake, ui);
			lastTimeMove = timePassed;
		}
		ui.setPoints(intToStr(ui.getApplesCollected()));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if ((event.type == Event::EventType::KeyReleased) && (event.key.code == sf::Keyboard::W)) { move.setStraightMoving(1);}
			if ((event.type == Event::EventType::KeyReleased) && (event.key.code == sf::Keyboard::S)) { move.setStraightMoving(2);}
			if ((event.type == Event::EventType::KeyReleased) && (event.key.code == sf::Keyboard::A)) { move.setStraightMoving(3);}
			if ((event.type == Event::EventType::KeyReleased) && (event.key.code == sf::Keyboard::D)) { move.setStraightMoving(4);}
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < ui.getCellsArraySize(); i++) window.draw(ui.getCells(i));
		for(int i = 0; i < snake.getSnakeTailLength();i++) window.draw(snake.getSnakeTail(i));
		window.draw(ui.getApple());
		window.draw(snake.getSnakeHeadShape());
		window.draw(ui.getPoints());
		if(ui.isGameOn())window.draw(ui.getTryAgainSprite());
		window.display();
		//system("pause");
		//cout << timePassed << endl;

	}

	return 0;
}