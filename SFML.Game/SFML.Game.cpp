#include <SFML/Graphics.hpp>
#include <algorithm> 
#include<iostream>

#include"Bird.h"
#include"Pipes.h"
#include"Background.h"



int main() {

    //-------------------------------INITIALIZE-------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Floppy Bird", sf::Style::Default, settings);

    //--------------------------------INITIALIZE-------------------------

    //----------------------------------LOAD-----------------------------

    Background background;
    background.Initialize();
    background.Load();


    Bird bird;
    bird.Initialize();
    bird.Load();

    Pipes pipes;
    pipes.Initialize();
    pipes.Load();
 
    //-----------------------------------LOAD-----------------------------

    //main game loop
    while (window.isOpen()) {

     //--------------------------------UPDATE------------------------------

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
           
        }

        bird.Update();
        pipes.Update();
        background.Update();
       

     //--------------------------------UPDATE------------------------------


     //--------------------------------DRAW--------------------------------

        window.clear();
      
        background.Draw(window);

        pipes.Draw(window);

        bird.Draw(window);

        window.display();

     //--------------------------------DRAW--------------------------------

    }

    return 0;
}