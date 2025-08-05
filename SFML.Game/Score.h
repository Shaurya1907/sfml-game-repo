#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Score
{
private:
    unsigned int currentScore = 0;
    std::vector<sf::Texture> digitTextures; // stores textures for 0–9
    std::vector<sf::Sprite> digitSprites;   // sprites for current score

public:
    void Load(const std::string& folderPath);
    void Reset() { currentScore = 0; }
    void AddPoint() { currentScore++; }
    unsigned int GetScore() const { return currentScore; }

    void UpdateSprites();
    void Draw(sf::RenderWindow& window);
};
