#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    explicit Engine(int width = 1200, int height = 800);

    void run();
private:

    void handleEvent();
    void update();
    void render();
    sf::Texture texture;
    sf::RenderWindow window;
    sf::Sprite sprite;
    sf::Font font;
};



#endif //ENGINE_H