#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    explicit Engine(int width = sf::VideoMode::getDesktopMode().width-100, int height = sf::VideoMode::getDesktopMode().height);

    void run();
private:

    void handleEvent();
    void update();
    void render();
    sf::Texture texture;
    sf::RenderWindow window;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
};



#endif //ENGINE_H