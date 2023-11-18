//Students: Kyle Stowell & Cesar Gutierrez
#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    unsigned int width = VideoMode::getDesktopMode().width / 2;
    unsigned int height = VideoMode::getDesktopMode().height / 2;
    VideoMode vm(width, height);
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);

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
        firstText.setString("");
        firstText.setCharacterSize();
        firstText.setFillColor(sf::Color::);
        firstText.setPosition(,);

        secondText.setFont(font);
        secondText.setString("");
        secondText.setCharacterSize();
        secondText.setFillColor(sf::Color::);
        secondText.setPosition(,);

    }
}