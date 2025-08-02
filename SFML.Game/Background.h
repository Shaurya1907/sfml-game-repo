#pragma once
#include <SFML/Graphics.hpp>

class Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	
	float scrollSpeed = 0.04f;

public:
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};