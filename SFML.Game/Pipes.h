#pragma once
#include "Score.h"
#include <SFML/Graphics.hpp>

class Pipes
{
private:

	sf::Texture texture;

	struct Pipe {
		sf::Sprite topPipe;
		sf::Sprite bottomPipe;

		bool passed = false;
	};

	float scrollSpeed = 0.06f; // same as Background

	std::vector<Pipe> pipes;

	sf::Clock pipeSpawnClock;
	float pipeSpawnInterval = 1.75f; // spawn pipe every 2 seconds
	float pipeSpeed = scrollSpeed;
	float verticalGap = 150;

public:
	
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
	bool CheckCollision(const sf::FloatRect& birdBounds);
	void CheckScore(const sf::FloatRect& birdBounds, Score& score);



};