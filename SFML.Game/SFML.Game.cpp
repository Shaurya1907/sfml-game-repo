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

int main() {

    //-------------------------------INITIALIZE-------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500, 700), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close, settings);

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
    bird.Initialize();
    bird.Load();

    Pipes pipes;
    pipes.Initialize();
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
    score.Reset();

    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("Assets/Texture/gameover.png")) {
        std::cout << "Failed to load gameover.png\n";
    }

    sf::Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setPosition(110.f, 150.f);
    gameOverSprite.setScale(1.5f, 1.5f);

    sf::Texture restartTexture;
    if (!restartTexture.loadFromFile("Assets/Texture/restart.png")) {
        std::cout << "Failed to load restart.png\n";
    }

    sf::Sprite restartSprite(restartTexture);
    restartSprite.setPosition(160.f, 275.f );
    restartSprite.setScale(1.0f, 1.0f);

    //-----------------------------------LOAD-----------------------------

    //main game loop
    while (window.isOpen()) {

     //--------------------------------UPDATE------------------------------

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

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

            if (state == GameState::GameOver)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if(restartSprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x),static_cast<float>(event.mouseButton.y)))
                    {
                        // Reset the game
                        bird.Initialize();
                        pipes.Initialize();
                        score.Reset(); // you'll need to add Reset() in Score class
                        gameOver = false;
                        state = GameState::StartMenu; // back to start screen
                    }
                }
            }

        }

        if (state == GameState::Playing && !gameOver)
        {
            bird.Update();
            background.Update();
            Ground.Update();
            pipes.Update();

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