//Students: Kyle Stowell & Cesar Gutierrez
#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace sf;


int main()
{
    unsigned int width = VideoMode::getDesktopMode().width / 2;
    unsigned int height = VideoMode::getDesktopMode().height / 2;
    VideoMode vm(width, height);
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    ComplexPlane plane(width, height);

    sf::Font font;
    if (!font.loadFromFile("coolvetica.ttf"))
        return(-1);
    sf::Text firstText;
    sf::Text secondText;


    while (window.isOpen())
    {
        firstText.setFont(font);
        firstText.setCharacterSize(20);
        firstText.setFillColor(sf::Color::White);
        firstText.setPosition(0, 0);
        plane.loadText(firstText);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                //zoom in
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.y);
                    plane.zoomIn();
                    plane.setCenter(mousePosition);
                }
                //zoom out
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.y);
                    plane.zoomOut();
                    plane.setCenter(mousePosition);
                }
            }
            
            if (event.type == sf::Event::MouseMoved)
            {
                plane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        plane.updateRender();
        plane.loadText(firstText);

        window.clear();
        plane.draw(window, sf::RenderStates::Default);
        window.draw(firstText);
        window.display();
    }
    return 0;
}
