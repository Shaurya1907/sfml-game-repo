#include "Bird.h"
#include<iostream>

void Bird::Initialize()
{

}

void Bird::Load()
{
    if (!texture[0].loadFromFile("Assets/Texture/Bird/yellowbird-upflap.png") ||
        !texture[1].loadFromFile("Assets/Texture/Bird/yellowbird-midflap.png") ||
        !texture[2].loadFromFile("Assets/Texture/Bird/yellowbird-downflap.png")) {
        std::cout << "Failed to load one or more bird textures!" << std::endl;
        return;
    }

    sprite.setScale(1.5, 1.5f);
    sprite.setPosition(200.f, 300.f);
}

// Inside game loop
void Bird::Update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        velocityY = flapStrength;

        // Only trigger once per flap
        if (!justFlapped)
        {
            targetRotation = -20.f; // Tilt upward
            BirdAngleRotationClock.restart(); // Start timer
            justFlapped = true;
        }
    }
    else
    {
        justFlapped = false; // Allow next flap
    }

    // If waiting period is over, set target to downward tilt
    if (BirdAngleRotationClock.getElapsedTime().asSeconds() >= WaitBeforeRotation)
    {
        targetRotation = 90.f; // Tilt downward
    }

    // Smoothly move birdRotation toward targetRotation
    birdRotation += (targetRotation - birdRotation) * 0.001f; // Adjust 0.1f for speed
    sprite.setRotation(birdRotation);


    // Apply gravity
    velocityY += gravity;
    sprite.move(velocityX, velocityY);

    // Simple ground collision
    if (sprite.getPosition().y + sprite.getGlobalBounds().height >= 600)
    {
        sprite.setPosition(sprite.getPosition().x, 600 - sprite.getGlobalBounds().height);
        velocityY = 0;
    }

    if (sprite.getPosition().y <= 0)
    {
        sprite.setPosition(sprite.getPosition().x, 0);
        velocityY = 0;
    }

    //Animation of bird 
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
    {
        currentFrame = (currentFrame + 1) % 3;  // Cycle through 0, 1, 2
        sprite.setTexture(texture[currentFrame]);
        animationClock.restart();
    }

}

void Bird::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
