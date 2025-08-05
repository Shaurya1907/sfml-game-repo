#include "Bird.h"
#include<iostream>

void Bird::Initialize()
{
    // Reset position to starting point
    sprite.setPosition(225.f, 275.f);

    // Reset vertical and horizontal velocity
    velocityY = 0.f;
    velocityX = 0.f;

    // Reset rotation
    birdRotation = 0.f;
    targetRotation = 0.f;
    sprite.setRotation(0.f);

    // Allow flapping again
    justFlapped = false;

}

void Bird::Load()
{
    if (!texture[0].loadFromFile("Assets/Texture/Bird/yellowbird-upflap.png") ||
        !texture[1].loadFromFile("Assets/Texture/Bird/yellowbird-midflap.png") ||
        !texture[2].loadFromFile("Assets/Texture/Bird/yellowbird-downflap.png")) {
        std::cout << "Failed to load one or more bird textures!" << std::endl;
        return;
    }

    sprite.setScale(1.4, 1.4f);
    sprite.setPosition(225.f, 330.f);
}

void Bird::Flap()
{
    velocityY = flapStrength; // Jump up
    targetRotation = -20.f;   // Tilt upward
    BirdAngleRotationClock.restart(); // Restart rotation delay
}

// Inside game loop
void Bird::Update()
{
    // If waiting period is over, tilt downward
    if (BirdAngleRotationClock.getElapsedTime().asSeconds() >= WaitBeforeRotation)
    {
        targetRotation = 90.f; // Tilt downward
    }

    // Smoothly rotate bird towards target rotation
    birdRotation += (targetRotation - birdRotation) * rotationSpeed;
    sprite.setRotation(birdRotation);

    // Apply gravity
    velocityY += gravity;
    sprite.move(velocityX, velocityY);

  
    // Ceiling collision
    if (sprite.getPosition().y <= 0)
    {
        sprite.setPosition(sprite.getPosition().x, 0);
        velocityY = 0;
    }

    // Animate bird
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
    {
        currentFrame = (currentFrame + 1) % 3; // Cycle through 0,1,2
        sprite.setTexture(texture[currentFrame]);
        animationClock.restart();
    }
}


void Bird::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
