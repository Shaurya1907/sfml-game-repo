#include <SFML/Graphics.hpp>
#include <algorithm> 
#include<iostream>

#include"Bird.h"
#include"Pipes.h"
#include"Background.h"
#include"ground.h"
#include "Score.h"

enum class GameState
{
    StartMenu,
    Playing,
    GameOver
};

void updateRestartButtonPosition(const sf::View& view, sf::Sprite& button)
{
    sf::Vector2f center = view.getCenter();
    button.setPosition(center.x, center.y); // dead center in world coords
   
}

int main() {

    //-------------------------------INITIALIZE-------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500, 700), "Flappy Bird", sf::Style::Default | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(60);

    sf::View view(sf::FloatRect(0.f, 0.f, 500.f, 700.f));
    window.setView(view);

    sf::Texture restartTexture;
    if (!restartTexture.loadFromFile("Assets/Texture/restart.png")) {
        std::cout << "Failed to load restart.png\n";
    }

    bool gameOver = false;

    //--------------------------------INITIALIZE-------------------------

    //----------------------------------LOAD-----------------------------
  
    Background background;
    background.Initialize();
    background.Load();

    ground Ground;
    Ground.Initialize();
    Ground.Load();

    Bird bird;
    bird.Load();

    Pipes pipes;
    pipes.Load();
 
    GameState state = GameState::StartMenu;
    sf::Texture messageTexture;
    if (!messageTexture.loadFromFile("Assets/Texture/message.png")) {
        std::cout << "Failed to load message texture!" << std::endl;
    }

    sf::Sprite messageSprite(messageTexture);
    messageSprite.setPosition(
        (500 - messageTexture.getSize().x) / 2.f,  // center horizontally
        100.f                                     // y position
    );
    
    Score score;
    score.Load("Assets/Texture/Numbers"); // path to folder with 0.png ... 9.png

    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("Assets/Texture/gameover.png")) {
        std::cout << "Failed to load gameover.png\n";
    }

    sf::Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setPosition(110.f, 150.f);
    gameOverSprite.setScale(1.5f, 1.5f);

    sf::Sprite restartSprite(restartTexture);
    restartSprite.setScale(1.0f, 1.0f);

    // Set origin to center so position works correctly
    restartSprite.setOrigin(
        restartSprite.getLocalBounds().width / 2.f,
        restartSprite.getLocalBounds().height / 2.f
    );

    restartSprite.setPosition(250.f, 350.f);

    sf::Clock deltaClock;

    //-----------------------------------LOAD-----------------------------

    //main game loop
    while (window.isOpen()) {

     //--------------------------------UPDATE------------------------------

        float deltaTime = deltaClock.restart().asSeconds(); // Time in seconds

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // Keep the world size fixed (500x700) so aspect ratio is preserved
                view.setSize(500.f, 700.f);
                view.setCenter(250.f, 350.f); // Center of the 500x700 world


                // Calculate the new aspect ratio
                float windowRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                float viewRatio = 500.f / 700.f; // base aspect ratio

                sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

                if (windowRatio > viewRatio) // window too wide
                {
                    float width = viewRatio / windowRatio;
                    viewport.left = (1.f - width) / 2.f;
                    viewport.width = width;
                }
                else if (windowRatio < viewRatio) // window too tall
                {
                    float height = windowRatio / viewRatio;
                    viewport.top = (1.f - height) / 2.f;
                    viewport.height = height;
                }

                view.setViewport(viewport); // add black bars if needed
                window.setView(view);

                updateRestartButtonPosition(view, restartSprite);
            }

            // Start menu input
            if (state == GameState::StartMenu)
            {
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) ||
                    (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
                {
                    state = GameState::Playing;
                }
            }

            // Game playing input
            if (state == GameState::Playing && !gameOver)
            {
                pipes.CheckScore(bird.GetBounds(), score);


                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) ||
                    (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
                {
                    bird.Flap();
                }
            }

            // Game over input
            if (state == GameState::GameOver) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // Convert mouse position to view coordinates
                    sf::Vector2f mouseViewPos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);

                    if (restartSprite.getGlobalBounds().contains(mouseViewPos)) {
                        bird.Initialize();
                        pipes.Initialize();
                        score.Reset();
                        gameOver = false;
                        state = GameState::StartMenu;
                    }
                }
            }
        }

        if (state == GameState::Playing && !gameOver)
        {
            bird.Update(deltaTime);
            background.Update(deltaTime);
            Ground.Update(deltaTime);
            pipes.Update(deltaTime);

            void CheckScore(const sf::FloatRect & birdBounds, Score & score);

            // Collision check
            if (pipes.CheckCollision(bird.GetBounds()))
            {
                gameOver = true;
                state = GameState::GameOver;
            }
            if (bird.GetBounds().top + bird.GetBounds().height >= Ground.GetTopY())
            {
                gameOver = true;
                state = GameState::GameOver;
            }
       
        }
   
     //--------------------------------UPDATE------------------------------


     //--------------------------------DRAW--------------------------------

        window.clear();
      
        background.Draw(window);

        pipes.Draw(window);

        Ground.Draw(window);
        if (state == GameState::Playing || state == GameState::GameOver)
        {
            bird.Draw(window);
        }

        if (state == GameState::StartMenu)
        {
            window.draw(messageSprite);
        }

        if (state == GameState::Playing)
        {
            score.Draw(window);
        }

        if (state == GameState::GameOver)
        {
            window.draw(gameOverSprite);

            // Draw final score
            score.Draw(window);

            // Draw restart button
            window.draw(restartSprite);
        }

        window.display();

     //--------------------------------DRAW--------------------------------

    }

    return 0;
}