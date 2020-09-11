/*
By: Rohan Putcha
Dotpoint 2.0
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "setup.h"
#define sens 25

int main()
{
	srand(time(NULL));

	// variables (for the coordinates of the pieces, for the score, for the starting screen and for score display screen)
	float randx, randy;
	bool over = false;
	bool gamescreen = false;
	int score = -1;    // starts at -1 because the first piece spawns on the circle at (50, 50)

	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dotpoint 2.0");
	window.setFramerateLimit(60);

	//event, clock and font
	sf::Event event;
	sf::Clock timer;
	sf::Font font;
	if (!font.loadFromFile("realitysunday.ttf"))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}

	//textures, font and text and the button
	button play;
	play.set_texture("texture.png");
	play.set_position(320, 300);
	play.set_size(180, 60);
	play.set_text("PLAY", "realitysunday.ttf", 35, sf::Color::Black, sf::Vector2f(310, 300));
	play.set_color(sf::Color(255, 255, 255));


	//set title
	sf::Text title("DOTPOINT", font, 80);
	title.setFillColor(sf::Color::Black);
	title.setPosition(sf::Vector2f(75, 140));

	//create the circle shape and piece
	sf::CircleShape circle(50);
	sf::RectangleShape piece(sf::Vector2f(50, 50));
	sf::Texture cointexture;
	if (!cointexture.loadFromFile("coin.png"))
	{
		std::cout << "Error: Cannot load texture for 'play button'" << std::endl;
	}
	piece.setTexture(&cointexture);
	circle.setFillColor(sf::Color(0, 255, 255));
	circle.setOutlineColor(sf::Color(250, 150, 100));
	circle.setOutlineThickness(-20);
	float coord[2] = { 50, 50 };

	//text object for score
	sf::Text scoretext("", font, 120);
	scoretext.setPosition(130, 220);
	scoretext.setFillColor(sf::Color::Blue);
	// run the program as long as the window is open
	while (gamescreen == false)
	{
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float> (mousePos.x), static_cast<float> (mousePos.y));
				if ((play.show_rec()).getGlobalBounds().contains(mousePosF))
				{
					gamescreen = true;
				}

			}
			
		}
		window.clear(sf::Color(0, 50, 0));
		window.draw(play.draw());
		window.draw(play.drawText());
		window.draw(title);
		window.display();


	}

	timer.restart();
	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with red color
		window.clear(sf::Color(255, 0, 0));
		window.draw(circle);
		if ((circle.getGlobalBounds().intersects(piece.getGlobalBounds()) == true) && over == false)
		{
			score++;
			randx = (rand() % 700) + 50;
			randy = (rand() % 500) + 50;
			piece.setPosition(randx, randy);
			//Debugging (coordinates of piece): std::cout << randx << " " << randy << std::endl;
		}
		if (timer.getElapsedTime() > sf::seconds(20))
		{
			window.clear(sf::Color(255, 0, 0));
			std::string s = std::to_string(score);
			scoretext.setString("Score- " + s);
			window.draw(scoretext);
			over = true;
		}

		if (over == false)
			window.draw(piece);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (coord[1] > 50)
			{
				circle.move(0, -sens);
				coord[1] = coord[1] - sens;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (coord[0] > 50)
			{
				circle.move(-sens, 0);
				coord[0] = coord[0] - sens;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (coord[1] < 550)
			{
				circle.move(0, sens);
				coord[1] = coord[1] + sens;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (coord[0] < 750)
			{
				circle.move(sens, 0);
				coord[0] = coord[0] + sens;
			}
		}
		// end the current frame and show the frame
		window.display();

	}

	return 0;
}