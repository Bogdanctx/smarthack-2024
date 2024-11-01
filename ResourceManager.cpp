#include "ResourceManager.h"
#include <filesystem>

ResourceManager::ResourceManager() {}

void ResourceManager::load()
{
    // loadTextures("ceva.png");

    // loadSounds("ceva.wav");

    // loadFonts("ceva.ttf");
}


void ResourceManager::loadSound(const std::string& sound_name) {
    const std::filesystem::path path = std::filesystem::path("resources") / "sounds" / sound_name;
    sf::SoundBuffer sound;

    if(!sound.loadFromFile(path.string())) {
        throw std::runtime_error(sound_name + " missing or corrupted\n");
    }
    m_sounds[sound_name] = sound;
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& soundName) {
    return m_sounds[soundName];
}

void ResourceManager::loadFont(const std::string &fontName) {
    const std::filesystem::path path = std::filesystem::path("resources") / "fonts" / fontName;
    sf::Font font;

    if(!font.loadFromFile(path.string())) {
        throw std::runtime_error(fontName + " missing or corrupted.\n");
    }

    m_fonts[fontName] = font;
}

sf::Font& ResourceManager::getFont(const std::string &key) {
    return m_fonts.at(key);
}

void ResourceManager::loadTexture(const std::string &textureName) {
    const std::filesystem::path path = std::filesystem::path("resources") / "general_textures" / textureName;
    sf::Texture texture;

    if(!texture.loadFromFile(path.string())) {
        throw std::runtime_error(textureName + " missing or corrupted.\n");
    }

    m_textures[textureName] = texture;
}

sf::Texture& ResourceManager::getTexture(const std::string &key) {
    return m_textures.at(key);
}

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}