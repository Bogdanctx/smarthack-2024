#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>

class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& Instance();

    sf::Font &getFont(const std::string &key);
    sf::Texture& getTexture(const std::string &key);
    const std::vector<std::string>& getFacts() const;
    sf::SoundBuffer &getSound(const std::string &soundName);

    void load();
private:
    ResourceManager();

    void loadTexture(const std::string &textureName);
    void loadFont(const std::string &fontName);
    void loadSound(const std::string &sound_name);

private:
    std::unordered_map<std::string, sf::Font> m_fonts{};
    std::unordered_map<std::string, sf::Texture> m_textures{};
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds{};
};
#endif //RESOURCEMANAGER_H
