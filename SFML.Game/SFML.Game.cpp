#include <SFML/Graphics.hpp>
#include <algorithm>
#include<iostream>

struct Pipe {
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
};

int main() {

    //-------------------------------INITIALIZE-------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Floppy Bird", sf::Style::Default, settings);

    // Physics
    float velocityY = 0.0f;
    float gravity = 0.0005f;
    float flapStrength = -0.2f;
    float velocityX = 0.00f;                   

    float scrollSpeed = 0.04f; // same as bird/camera velocity
    

    //--------------------------------INITIALIZE-------------------------

    //----------------------------------LOAD-----------------------------

    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("Assets/Texture/background-day.png"))
        return -1;

   
    sf::Sprite background1(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    // Position them side by side
    background1.setPosition(0.f, 0.f);
    background2.setPosition(backgroundTexture.getSize().x, 0.f);

    sf::Texture BirdTexture[3];
    sf::Sprite  BirdSprite;
    BirdSprite.setScale(1.5, 1.5f);
    BirdSprite.setPosition(200.f, 300.f);

    int currentFrame = 0;
    sf::Clock animationClock;

    float animationSpeed = 0.15f; // seconds per frame (150ms)

    if (!BirdTexture[0].loadFromFile("Assets/Texture/Bird/yellowbird-upflap.png") ||
        !BirdTexture[1].loadFromFile("Assets/Texture/Bird/yellowbird-midflap.png") ||
        !BirdTexture[2].loadFromFile("Assets/Texture/Bird/yellowbird-downflap.png")) {
        std::cout << "Failed to load one or more bird textures!" << std::endl;
        return -1;
    }

    sf::Texture pipeTexture;
    if (!pipeTexture.loadFromFile("Assets/Texture/pipe-green.png")) {
        std::cout << "Pipe texture failed to load!" << std::endl;
        return -1;
    }

    std::vector<Pipe> pipes;

    sf::Clock pipeSpawnClock;
    float pipeSpawnInterval = 2.5f; // spawn pipe every 2 seconds
    float pipeSpeed = scrollSpeed;
    float pipeGap = 180.0f; //vertical gap between pipes

    // Rotation control
    sf::Clock BirdAngleRotationClock;
    float WaitBeforeRotation = 0.5f; // 1 second delay before tilting down
    bool justFlapped = false;
    float birdRotation = 0.f;       // Current rotation
    float targetRotation = 0.f;     // Where we want to rotate to


    //-----------------------------------LOAD-----------------------------

    //main game loop
    while (window.isOpen()) {

     //--------------------------------UPDATE------------------------------

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
           
        }

        // Inside game loop
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
        BirdSprite.setRotation(birdRotation);


        // Apply gravity
        velocityY += gravity;
        BirdSprite.move(velocityX, velocityY);

        // Scroll background (after bird moved)
        background1.move(-scrollSpeed, 0.f);
        background2.move(-scrollSpeed, 0.f);

        // Simple ground collision
        if (BirdSprite.getPosition().y + BirdSprite.getGlobalBounds().height  >= 600)
        {
            BirdSprite.setPosition(BirdSprite.getPosition().x, 600 - BirdSprite.getGlobalBounds().height);
            velocityY = 0;
        }

        if (BirdSprite.getPosition().y <= 0)
        {
            BirdSprite.setPosition(BirdSprite.getPosition().x, 0);
            velocityY = 0;
        }

        if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
        {
            currentFrame = (currentFrame + 1) % 3;  // Cycle through 0, 1, 2
            BirdSprite.setTexture(BirdTexture[currentFrame]);
            animationClock.restart();
        }

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
            newPipe.bottomPipe.setTexture(pipeTexture);
            newPipe.bottomPipe.setPosition(800.f, yOffset);

            // Top pipe (flipped)
            newPipe.topPipe.setTexture(pipeTexture);
            newPipe.topPipe.setScale(1.f, -1.f);
            newPipe.topPipe.setPosition(800.f, yOffset - randomGap);

            // Add to vector
            pipes.push_back(newPipe);

            // Restart spawn timer
            pipeSpawnClock.restart();
        }

        // When background1 moves completely off the screen
        if (background1.getPosition().x + backgroundTexture.getSize().x <= 0)
        {
            background1.setPosition(background2.getPosition().x + backgroundTexture.getSize().x, 0.f);
        }

        // When background2 moves completely off the screen
        if (background2.getPosition().x + backgroundTexture.getSize().x <= 0)
        {
            background2.setPosition(background1.getPosition().x + backgroundTexture.getSize().x, 0.f);
        }

        for (Pipe& pipe : pipes) {
            pipe.topPipe.move(-pipeSpeed, 0.f);
            pipe.bottomPipe.move(-pipeSpeed, 0.f);
        }

        // Remove pipes that have moved off-screen
        pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [&](Pipe& p) {
            return p.bottomPipe.getPosition().x + pipeTexture.getSize().x < 0;
            }), pipes.end());


     //--------------------------------UPDATE------------------------------


     //--------------------------------DRAW--------------------------------

        window.clear();
      
        window.draw(background1);
        window.draw(background2);

        for (const auto& pipe : pipes) {
            window.draw(pipe.topPipe);
            window.draw(pipe.bottomPipe);
        }

        window.draw(BirdSprite);

        window.display();

     //--------------------------------DRAW--------------------------------

    }

    return 0;
}