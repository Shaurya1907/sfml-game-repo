#include "Background.h"
#include<iostream>


void Background::Initialize()
{

}

void Background::Load()
{

    if (!texture.loadFromFile("Assets/Texture/background-day.png")) {
        std::cout << "Failed to load background textures!" << std::endl;
        return;
    }


    sprite1.setTexture(texture);
    sprite2.setTexture(texture);

    // Position them side by side
    sprite1.setPosition(0.f, 0.f);
    sprite2.setPosition(texture.getSize().x, 0.f);

}

void Background::Update(float deltaTime)
{
    // Scroll background (after bird moved)
    sprite1.move(-backgroundSpeed * deltaTime, 0.f);
    sprite2.move(-backgroundSpeed * deltaTime, 0.f);

    // When background1 moves completely off the screen
    if (sprite1.getPosition().x + texture.getSize().x <= 0)
    {
        sprite1.setPosition(sprite2.getPosition().x + texture.getSize().x, 0.f);
    }

    // When background2 moves completely off the screen
    if (sprite2.getPosition().x + texture.getSize().x <= 0)
    {
        sprite2.setPosition(sprite1.getPosition().x + texture.getSize().x, 0.f);
    }

}

void Background::Draw(sf::RenderWindow& window)
{
    window.draw(sprite1);
    window.draw(sprite2);

}