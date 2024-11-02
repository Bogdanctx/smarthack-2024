#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    explicit Engine(int width = sf::VideoMode::getDesktopMode().width-100, int height = sf::VideoMode::getDesktopMode().height);
    int mod;
    int engine_grafic=1;//1=se ruleaza engine grafic
    void run();
private:

    void handleEvent();
    void update();
    void render();
    sf::Texture texture_rafinarie,texture_clienti,texture_storage;
    sf::RenderWindow window;
    sf::Sprite sprite_rafinarie,sprite_clienti,sprite_storage;
    sf::Font font;
    sf::Text titlul,val_raf,val_cli,val_storage;//se iau din json

    void Generate_Rafinarii(std::string titlu,std::string valoare) {
        //DECLARARI
        int i,nr_rafinarii=20,//va fi luat din setu de date
        width,height,width_offset,height_offset,x=0,y=100,hsprite,wsprite;
        float scale;
        width=sf::VideoMode::getDesktopMode().width-100;
        height=sf::VideoMode::getDesktopMode().height-100;
        width_offset=300;
        height_offset=700;
        wsprite=sprite_rafinarie.getTexture()->getSize().x * sprite_rafinarie.getScale().x;
        hsprite=sprite_rafinarie.getTexture()->getSize().x * sprite_rafinarie.getScale().y;
        scale=0.87;
        i=nr_rafinarii;
        titlul.setFont(font);
        titlul.setCharacterSize(38);
        titlul.setFillColor(sf::Color::White);
        titlul.setString(titlu);
        val_raf.setFont(font);
        val_raf.setFillColor(sf::Color::White);

        //Actual code
        while(i>-1) {
            val_raf.setCharacterSize(50*scale);
            val_raf.setString(valoare);
            val_raf.setPosition(sf::Vector2f(x, y));
            sprite_rafinarie.setPosition(sf::Vector2f(x, y));
            x=x+width_offset;
            if(x>=width-(150*scale)) {
                y=y+height_offset;
                x=0;

            }
            if(y>=height-200) { //scalare cand e plin ecranul
                window.clear();
                sprite_rafinarie.setScale(sf::Vector2f(scale, scale));
                val_raf.setScale(sf::Vector2f(scale, scale));
                width_offset=width_offset*0.96;
                height_offset=height_offset*0.93;
                x=0;
                y=100;
                i=nr_rafinarii;
                scale=scale*0.97;
                window.clear();
            }

            if(i<nr_rafinarii) {
                window.draw(sprite_rafinarie);
                window.draw(val_raf);
            }
            window.draw(titlul);
            i--;
        }
        }
    void Generate_Client(std::string titlu,std::string valoare) {
        //DECLARARI
        int i,nr_clienti=100,//va fi luat din setu de date
        width,height,width_offset,height_offset,x=0,y=100,hsprite,wsprite;
        float scale;
        width=sf::VideoMode::getDesktopMode().width-100;
        height=sf::VideoMode::getDesktopMode().height-100;
        width_offset=300;
        height_offset=800;
        wsprite=sprite_rafinarie.getTexture()->getSize().x * sprite_rafinarie.getScale().x;
        hsprite=sprite_rafinarie.getTexture()->getSize().x * sprite_rafinarie.getScale().y;
        scale=0.87;
        i=nr_clienti;
        titlul.setFont(font);
        titlul.setCharacterSize(38);
        titlul.setFillColor(sf::Color::White);
        titlul.setString(titlu);
        val_cli.setFont(font);
        val_cli.setFillColor(sf::Color::White);

        //Actual code
        while(i>-1) {
            val_cli.setCharacterSize(70*scale);
            val_cli.setString(valoare);
            val_cli.setPosition(sf::Vector2f(x, y-20));
            sprite_clienti.setPosition(sf::Vector2f(x, y));
            x=x+width_offset;
            if(x>=width-(150*scale)) {
                y=y+height_offset;
                x=0;

            }
            if(y>=height-200) { //scalare cand e plin ecranul
                window.clear();
                sprite_clienti.setScale(sf::Vector2f(scale, scale));
                val_cli.setScale(sf::Vector2f(scale, scale));
                width_offset=width_offset*0.96;
                height_offset=height_offset*0.93;
                x=0;
                y=100;
                i=nr_clienti;
                scale=scale*0.97;
                window.clear();
            }

            if(i<nr_clienti) {
                window.draw(sprite_clienti);
                window.draw(val_cli);
            }
            window.draw(titlul);
            i--;
        }

    }
    void Generate_Storage(std::string titlu,std::string valoare) {
        //DECLARARI
        int i,nr_storage=50,//va fi luat din setu de date
        width,height,width_offset,height_offset,x=0,y=100,hsprite,wsprite;
        float scale;
        width=sf::VideoMode::getDesktopMode().width-100;
        height=sf::VideoMode::getDesktopMode().height-100;
        width_offset=300;
        height_offset=800;
        wsprite=sprite_storage.getTexture()->getSize().x * sprite_storage.getScale().x;
        hsprite=sprite_storage.getTexture()->getSize().x * sprite_storage.getScale().y;
        scale=0.87;
        i=nr_storage;
        titlul.setFont(font);
        titlul.setCharacterSize(38);
        titlul.setFillColor(sf::Color::White);
        titlul.setString(titlu);
        val_storage.setFont(font);
        val_storage.setFillColor(sf::Color::White);

        //Actual code
        while(i>-1) {
            val_storage.setCharacterSize(70*scale);
            val_storage.setString(valoare);
            val_storage.setPosition(sf::Vector2f(x, y-20));
            sprite_storage.setPosition(sf::Vector2f(x, y));
            x=x+width_offset;
            if(x>=width-(150*scale)) {
                y=y+height_offset;
                x=0;

            }
            if(y>=height-200) { //scalare cand e plin ecranul
                window.clear();
                sprite_storage.setScale(sf::Vector2f(scale, scale));
                val_storage.setScale(sf::Vector2f(scale, scale));
                width_offset=width_offset*0.96;
                height_offset=height_offset*0.93;
                x=0;
                y=100;
                i=nr_storage;
                scale=scale*0.97;
                window.clear();
            }

            if(i<nr_storage) {
                window.draw(sprite_storage);
                window.draw(val_storage);
            }
            window.draw(titlul);
            i--;
        }

    }

};



#endif //ENGINE_H