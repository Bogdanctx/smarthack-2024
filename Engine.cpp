#include "Engine.h"

Engine::Engine(int width, int height) :
        window(sf::VideoMode(width, height), "Visualizer")
{
    texture_rafinarie.loadFromFile("resources/rafinarie-nobg.png");
    sprite_rafinarie.setTexture(texture_rafinarie);
    font.loadFromFile("resources/Arial regular.ttf");
    texture_clienti.loadFromFile("resources/client-nobg1.png");
    sprite_clienti.setTexture(texture_clienti);
    texture_storage.loadFromFile("resources/oil_tank.png");
    sprite_storage.setTexture(texture_storage);

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
            Generate_Rafinarii("Rafinarii","valoare");
            break;
        }
        case 2: {
            Generate_Client("Client","valoare");
            break;
        }
        case 3: {
            Generate_Storage("Storage","valoare");
            break;
        }
        case 4: {

        }
        case 5: {

        }
        default: {
            Title_screen();
            break;
        }
    }





    window.display();
}

void Engine::update()
{

}

void Engine::handleEvent() {
    sf::Event event;

    while(window.pollEvent(event)) {
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
                    case sf::Keyboard::Num3: {
                        mod=3;
                        break;
                    }
                    case sf::Keyboard::Num4: {
                        mod=4;
                        break;
                    }
                    case sf::Keyboard::N: {
                        mod=5;
                        break;

                    }


                    default:
                        break;
                }
            }
        }
    }
}