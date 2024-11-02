#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    explicit Engine(int width = sf::VideoMode::getDesktopMode().width-100, int height = sf::VideoMode::getDesktopMode().height);
    int mod;
    void run();
private:

    void handleEvent();
    void update();
    void render();
    sf::Texture texture;
    sf::RenderWindow window;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text,text2;
    void Generate_Rafinarii() {
        //DECLARARI
        int i,nr_rafinarii=100//va fi luat din setu de date
        ,width,height,width_offset,height_offset,x=0,y=100,hsprite,wsprite;
        float scale;
        width=sf::VideoMode::getDesktopMode().width-100;
        height=sf::VideoMode::getDesktopMode().height-100;
        width_offset=300;
        height_offset=400;
        wsprite=sprite.getTexture()->getSize().x * sprite.getScale().x;
        hsprite=sprite.getTexture()->getSize().x * sprite.getScale().y;
        scale=0.87;
        i=nr_rafinarii;
        text2.setFont(font);
        text2.setCharacterSize(24);
        text2.setFillColor(sf::Color::White);
        text2.setString(std::to_string(scale));

        //Actual code
        while(i>-1) {

            sprite.setPosition(sf::Vector2f(x, y));
            x=x+width_offset;

            if(x>=width-(150*scale)) {
                y=y+height_offset;
                x=0;
            }
            if(y>=height-200) {
                window.clear();
                sprite.setScale(sf::Vector2f(scale, scale));
                width_offset=width_offset*0.96;
                height_offset=height_offset*0.93;
                x=0;
                y=100;
                i=nr_rafinarii;
                scale=scale*0.97;
                window.clear();
            }

            if(i<nr_rafinarii)
                window.draw(sprite);
            window.draw(text2);
            i--;
        }
        }


};



#endif //ENGINE_H