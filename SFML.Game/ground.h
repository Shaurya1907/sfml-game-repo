#pragma once
#include <SFML/Graphics.hpp>


class ground
{
private:
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;

	float scrollSpeed = 0.06f;

public:
	float GetTopY() const {
		return sprite1.getPosition().y; // top edge of the ground
	}
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};