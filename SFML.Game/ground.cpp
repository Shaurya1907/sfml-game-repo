#include "ground.h"
#include<iostream>


void ground::Initialize()
{

}

void ground::Load()
{

    if (!texture.loadFromFile("Assets/Texture/ground.background.png")) {
        std::cout << "Failed to load background textures!" << std::endl;
        return;
    }


    sprite1.setTexture(texture);
    sprite2.setTexture(texture);

    // Position them side by side
    sprite1.setPosition(0.f, 575.f);
    sprite2.setPosition((float)texture.getSize().x, 575.f);

}

void ground::Update()
{
   sprite1.move(-scrollSpeed, 0.f);
    sprite2.move(-scrollSpeed, 0.f);

    if (sprite1.getPosition().x + texture.getSize().x <= 0)
    {
        sprite1.setPosition(sprite2.getPosition().x + texture.getSize().x, sprite1.getPosition().y);
    }

    if (sprite2.getPosition().x + texture.getSize().x <= 0)
    {
        sprite2.setPosition(sprite1.getPosition().x + texture.getSize().x, sprite2.getPosition().y);
    }

}

void ground::Draw(sf::RenderWindow& window)
{
    window.draw(sprite1);
    window.draw(sprite2);

}