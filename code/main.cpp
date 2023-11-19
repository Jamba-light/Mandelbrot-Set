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

    ComplexPlane plane(width,height);

    sf::Font font;
    if (!font.loadFromFile("coolvetica.ttf"))
        return(-1);
    sf::Text firstText;
    sf::Text secondText;


    while (window.isOpen())
    {
        /*
        ****************************************
        Prompt the user
        ****************************************
        */
        
        firstText.setFont(font);
        firstText.setCharacterSize(50);
        firstText.setFillColor(sf::Color::White);
        firstText.setPosition(0,0);
        plane.loadText(firstText);
   

        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            //Zoom out
            if (event.mouseButton.button == Mouse::Right)
            {
                Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.x);
                plane.zoomOut();
                plane.setCenter(mousePosition);
            }

            //Zoom in
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.x);
                plane.zoomIn();
                plane.setCenter(mousePosition);
            }

            if (event.MouseMoved)
            {
                //plane.setMouseLocation(Mouse getPosition(window);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        plane.updateRender();


        window.clear();
        
        window.draw(firstText);
        window.display();

       
    }
}
