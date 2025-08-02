#pragma once
#include <SFML/Graphics.hpp>

class Pipes
{
private:

	sf::Texture texture;

	struct Pipe {
		sf::Sprite topPipe;
		sf::Sprite bottomPipe;
	};

	float scrollSpeed = 0.04f; // same as Background

	std::vector<Pipe> pipes;

	sf::Clock pipeSpawnClock;
	float pipeSpawnInterval = 2.5f; // spawn pipe every 2 seconds
	float pipeSpeed = scrollSpeed;
	float pipeGap = 180.0f; //vertical gap between pipes

public:
	

	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};