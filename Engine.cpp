#include "Engine.h"

Engine::Engine(int width, int height) :
        window(sf::VideoMode(width, height), "Visualizer")
{
    texture.loadFromFile("resources/rafinarie-nobg.png");
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
    //1=rafinarii, 2=storage, 3=clienti, 0=run
    switch (mod) {
        case 1: {
            Generate_Rafinarii();
            break;
        }
        case 2: {
            window.clear(sf::Color::Blue);
            break;
        }
        default: break;
    }





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
                switch (event.key.code) {
                    case sf::Keyboard::Num1: {
                        mod=1;
                        break;
                    }
                    case sf::Keyboard::Num2: {
                        mod=2;
                        break;
                    }
                }

            }


            default:
                break;
        }
    }
}
