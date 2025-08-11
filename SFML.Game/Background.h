#pragma once
#include <SFML/Graphics.hpp>

class Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	
	const float backgroundSpeed = 50.f;

public:
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};