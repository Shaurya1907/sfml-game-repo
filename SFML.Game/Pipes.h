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

	std::vector<Pipe> pipes;

	sf::Clock pipeSpawnClock;
	float pipeSpawnInterval =1.1f; // spawn pipe every 2 seconds
	const float pipeSpeed = 175.f;
	float verticalGap = 140;

public:
	
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	bool CheckCollision(const sf::FloatRect& birdBounds);
	void CheckScore(const sf::FloatRect& birdBounds, Score& score);



};