////////////////////////////////////////////////////////////
// Headers:
// ctime for getting system time and
// cmath for sin and cos functions
////////////////////////////////////////////////////////////
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <string>

const int screenWidth = 800;
const int screenHeight = 600;
const auto PI = M_PI;
const int clockCircleSize = 250;
const int clockCircleThickness = 2;
const int characterSize = 20;

struct  Clock
{
	sf::Vector2f center;
	sf::CircleShape hoursMarker[12];
	sf::RectangleShape minutsMarker[60];
	//sf::Font font;
	sf::Text digits[12];
	//sf::Music clockTick;
	Clock(sf::RenderWindow & window)
	{
		center = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	}
};

void InitHoursMarkers(Clock & clock)
{
	sf::Vector2f currentPosition;
	float angle = 0.0;
	for (int i = 0; i < 12; i++)
	{
		currentPosition.x = (clockCircleSize - 10) * cos(angle);
		currentPosition.y = (clockCircleSize - 10) * sin(angle);

		clock.hoursMarker[i] = sf::CircleShape(3);
		clock.hoursMarker[i].setFillColor(sf::Color::Black);
		clock.hoursMarker[i].setOrigin(clock.hoursMarker[i].getGlobalBounds().width / 2,
			clock.hoursMarker[i].getGlobalBounds().height / 2);
		clock.hoursMarker[i].setPosition(currentPosition + clock.center);
		clock.hoursMarker[i].setRotation(i * 30);

		angle = angle + ((2.0 * PI) / 12.0);
	}
}

void InitMinutesMarkers(Clock & clock)
{
	sf::Vector2f currentPosition;
	float angle = 0.0;
	for (int i = 0; i < 60; i++)
	{
		currentPosition.x = (clockCircleSize - 10) * cos(angle);
		currentPosition.y = (clockCircleSize - 10) * sin(angle);

		if (i % 5 != 0)
		{
			clock.minutsMarker[i] = sf::RectangleShape(sf::Vector2f(8, 3));
			clock.minutsMarker[i].setFillColor(sf::Color::Black);
			clock.minutsMarker[i].setOrigin(clock.minutsMarker[i].getGlobalBounds().width / 2,
				clock.minutsMarker[i].getGlobalBounds().height / 2);
			clock.minutsMarker[i].setPosition(currentPosition + clock.center);
			clock.minutsMarker[i].setRotation(i * 6);
		}

		angle = angle + ((2.0 * PI) / 60.0);
	}
}

void InitClock(Clock & clock)
{
	InitHoursMarkers(clock);
	InitMinutesMarkers(clock);
}

void HandleEvents(sf::Window & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void DrawClock(sf::RenderWindow & window, Clock & clock)
{
	auto drawHoursMarkers = [&]() {
		for (int i = 0; i < 12; i++)
		{
			window.draw(clock.hoursMarker[i]);
		}
	};

	auto drawMinutesMarkers = [&] (){
		for (int i = 0; i < 60; i++)
		{
			if (i % 5 != 0)
			{
				window.draw(clock.minutsMarker[i]);
			}
		}
	};

	drawHoursMarkers();
	drawMinutesMarkers();
	window.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Analog Clock", sf::Style::Close, settings);
	Clock clock(window);
	InitClock(clock);
	while (window.isOpen())
	{
		HandleEvents(window);
		window.clear(sf::Color::White);
		DrawClock(window, clock);
	}
	return EXIT_SUCCESS;
}