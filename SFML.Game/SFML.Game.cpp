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
    sf::RenderWindow window(sf::VideoMode(500, 700), "Flappy Bird", sf::Style::Default, settings);

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

        bird.Draw(window);

        if (state == GameState::StartMenu)
        {
            window.draw(messageSprite);
        }

        if (state == GameState::Playing)
        {
            score.Draw(window);
        }

        window.display();

     //--------------------------------DRAW--------------------------------

    }

    return 0;
}