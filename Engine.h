#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    explicit Engine(int width = 800, int height = 600);

    void run();
private:

    void handleEvent();
    void update();
    void render();

    sf::RenderWindow window;
};



#endif //ENGINE_H