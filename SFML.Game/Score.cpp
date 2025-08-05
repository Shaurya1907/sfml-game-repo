#include "Score.h"
#include <iostream>

void Score::UpdateSprites()
{
    digitSprites.clear();

    std::string scoreStr = std::to_string(currentScore);
    float xOffset = 0.0f;
    float spacing = 2.0f; // gap between digits

    for (char c : scoreStr)
    {
        int digit = c - '0';
        sf::Sprite sprite(digitTextures[digit]);
        sprite.setScale(1.5f, 1.5f); // scale up if needed
        sprite.setPosition(230 + xOffset, 50); // top-left of screen

        xOffset += sprite.getGlobalBounds().width + spacing;
        digitSprites.push_back(sprite);
    }
}

void Score::Load(const std::string& folderPath)
{
    digitTextures.clear();

    for (int i = 0; i <= 9; i++)
    {
        sf::Texture tex;
        std::string filePath = folderPath + "/" + std::to_string(i) + ".png";
        if (!tex.loadFromFile(filePath))
        {
            std::cout << "Failed to load number: " << filePath << std::endl;
            continue;
        }
        digitTextures.push_back(tex);
    }

    UpdateSprites(); // initialize sprites for score=0
}

void Score::Draw(sf::RenderWindow& window)
{
    UpdateSprites(); // update positions/textures for current score
    for (auto& sprite : digitSprites)
        window.draw(sprite);
}