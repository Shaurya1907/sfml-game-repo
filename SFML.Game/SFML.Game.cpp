#include <SFML/Graphics.hpp>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 2.5.1", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(375, 275);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
