#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
	sf::Texture texture[3];
    sf::Sprite sprite;

    // Physics
    float velocityY = 0.0f;
    float gravity = 2000.f;
    float flapStrength = -550.0f;
    float velocityX = 0.00f;

    int currentFrame = 0;
    sf::Clock animationClock;
    float animationSpeed = 0.15f;   // seconds per frame (150ms)

    // Rotation control
    sf::Clock BirdAngleRotationClock;
    float WaitBeforeRotation = 0.5f;// 0.5 second delay before tilting down
    bool justFlapped = false;
    float birdRotation = 0.f;       // Current rotation
    float targetRotation = 0.f;     // Where we want to rotate to
    float rotationSpeed = 2.5f;   //speed of rotation

public:

    sf::FloatRect GetBounds() const {
        sf::FloatRect bounds = sprite.getGlobalBounds();

        // Shrink the box slightly to match the visible bird better
        bounds.left += 10.f;  // move right
        bounds.top += 10.f;  // move down
        bounds.width -= 15.f; // reduce width
        bounds.height -= 15.f; // reduce height
        return bounds;
    }

    void Flap();
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};