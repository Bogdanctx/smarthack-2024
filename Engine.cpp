#include "Engine.h"

Engine::Engine(int width, int height) :
        window(sf::VideoMode(width, height), "Visualizer")
{
    texture.loadFromFile("resources/cautz.jpg");
    sprite.setTexture(texture);
    font.loadFromFile("resources/Arial regular.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("Rafinarie");

}


void Engine::run()
{
    while(window.isOpen())//merge cat tmp e open
    {
        handleEvent();
        update();
        render();
    }
}

void Engine::render()
{
    window.clear(sf::Color::Black);//intre astea intra renderingul
    window.draw(text);
    window.draw(sprite);
    sprite.move(sf::Vector2f(0.1, 0.f));
    window.display();
}

void Engine::update()
{

}

void Engine::handleEvent()
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        switch(event.type)//switch pt orice interactiune
        {
            case sf::Event::Closed:
            {
                window.close();
            }
            case sf::Event::MouseWheelScrolled: {
                window.close();
        }
            case sf::Event::KeyPressed: {
                if(event.key.code == sf::Keyboard::Escape) {

                }
            }


            default:
                break;
        }
    }
}
