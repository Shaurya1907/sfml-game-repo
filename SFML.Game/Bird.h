#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
	sf::Texture texture[3];
    sf::Sprite sprite;

    // Physics
    float velocityY = 0.0f;
    float gravity = 0.0005f;
    float flapStrength = -0.2f;
    float velocityX = 0.00f;

    int currentFrame = 0;
    sf::Clock animationClock;
    float animationSpeed = 0.15f; // seconds per frame (150ms)

    // Rotation control
    sf::Clock BirdAngleRotationClock;
    float WaitBeforeRotation = 0.5f; // 0.5 second delay before tilting down
    bool justFlapped = false;
    float birdRotation = 0.f;       // Current rotation
    float targetRotation = 0.f;     // Where we want to rotate to

public:
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};