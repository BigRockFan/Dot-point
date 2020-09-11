#ifndef SETUP_H
#define SETUP_H

class button
{
private:
	sf::RectangleShape box;
	sf::Text text;
public:
	void set_texture(std::string);
	sf::RectangleShape show_rec();
	void set_position(float, float);
	void set_size(float, float);
	void set_text(std::string, std::string, float, sf::Color, sf::Vector2f);
	void set_color(sf::Color);
	bool got_clicked(sf::RenderWindow);
	sf::RectangleShape draw();
	sf::Text drawText();
};

sf::RectangleShape button::show_rec()
{
	return box;
}
void button::set_texture(std::string name_of_texture)
{
	sf::Texture texture;
	if (!texture.loadFromFile(name_of_texture))
	{
		std::cout << "Error: Cannot load texture for 'play button'" << std::endl;
	}

}

void button::set_position(float x, float y)
{
	box.setPosition(x, y);
}

void button::set_size(float x, float y)
{
	box.setSize(sf::Vector2f(x, y));
}

void button::set_text(std::string name, std::string  texture_name, float size, sf::Color color, sf::Vector2f text_pos)
{
	text.setString(name);
    sf::Font font;
	if (!font.loadFromFile(texture_name))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(text_pos);
}

void button::set_color(sf::Color color)
{
	box.setFillColor(color);
}

bool button::got_clicked(sf::RenderWindow window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float> (mousePos.x), static_cast<float> (mousePos.y));
	if (box.getGlobalBounds().contains(mousePosF))
		return true;
	else
		return false;
}

sf::RectangleShape button::draw()
{
	return box;
}
sf::Text button::drawText()
{
	return text;
}
#endif