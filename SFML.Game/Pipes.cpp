#include "Pipes.h"
#include<iostream>

void Pipes::Initialize()
{

}
void Pipes::Load()
{
    if (!texture.loadFromFile("Assets/Texture/pipe-green.png")) {
        std::cout << "Pipe texture failed to load!" << std::endl;
        return;
    }

}
void Pipes::Update()
{
    //pipes
    if (pipeSpawnClock.getElapsedTime().asSeconds() >= pipeSpawnInterval) {

        // --- Predefined safe Y positions for bottom pipe ---
        static std::vector<float> safeYPositions = {
            280.f,
            300.f,
            350.f,
            400.f,
            450.f,
        };

        // Pick a random safe Y position
        int index = rand() % safeYPositions.size();
        float yOffset = safeYPositions[index];

        // --- Randomize gap size a little ---
        float minGap = 150.f; // Minimum allowed gap
        float maxGap = 200.f; // Maximum allowed gap
        float randomGap = minGap + static_cast<float>(rand()) / RAND_MAX * (maxGap - minGap);

        Pipe newPipe;

        // Bottom pipe
        newPipe.bottomPipe.setTexture(texture);
        newPipe.bottomPipe.setPosition(800.f, yOffset);

        // Top pipe (flipped)
        newPipe.topPipe.setTexture(texture);
        newPipe.topPipe.setScale(1.f, -1.f);
        newPipe.topPipe.setPosition(800.f, yOffset - randomGap);

        // Add to vector
        pipes.push_back(newPipe);

        // Restart spawn timer
        pipeSpawnClock.restart();
    }

    for (Pipe& pipe : pipes) {
        pipe.topPipe.move(-pipeSpeed, 0.f);
        pipe.bottomPipe.move(-pipeSpeed, 0.f);
    }

    // Remove pipes that have moved off-screen
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [&](Pipe& p) {
        return p.bottomPipe.getPosition().x + texture.getSize().x < 0;
        }), pipes.end());
}
void Pipes::Draw(sf::RenderWindow& window)
{
    for (const auto& pipe : pipes) {
        window.draw(pipe.topPipe);
        window.draw(pipe.bottomPipe);
    }
}
