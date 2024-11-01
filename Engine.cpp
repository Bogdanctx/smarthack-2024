#include "Engine.h"

Engine::Engine(int width, int height) :
        window(sf::VideoMode(width, height), "App name")
{

}


void Engine::run()
{
    sound.play();
    while(window.isOpen())
    {
        handleEvent();
        update();
        render();
    }
}

void Engine::render()
{
    window.clear();



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
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
            }
        }
    }
}

