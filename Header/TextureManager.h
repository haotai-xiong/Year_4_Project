#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class TextureManager {
public:
    TextureManager() {
        // buildings
        loadTexture("house", "../Assets/Project/Building/wood.png");
        loadTexture("factory", "../Assets/Project/Building/red.png");
        loadTexture("recycling center", "../Assets/Project/Building/Recycling Center.png");
        loadTexture("landfill", "../Assets/Project/Building/Landfill.png");
        loadTexture("plant", "../Assets/Project/Building/plant.png");
        loadTexture("tower", "../Assets/Project/Building/tower3.png");
        // fonts
        loadFont("cheril", "../Assets/Project/Font/CHERL.TTF");
        loadFont("cherii", "../Assets/Project/Font/CHERI.TTF");
    }
    ~TextureManager() {}

    void loadTexture(const std::string t_name, const std::string t_filename) {
        sf::Texture texture;
        texture.loadFromFile(t_filename);
        textures[t_name] = texture;
    }

    void loadFont(const std::string t_name, const std::string t_filename) {
        sf::Font font;
        font.loadFromFile(t_filename);
        fonts[t_name] = font;
    }

    sf::Texture& getTexture(const std::string t_name) {
        return textures.at(t_name);
    }

    sf::Font& getFont(const std::string t_name) {
        return fonts.at(t_name);
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
};

#endif // TEXTURE_MANAGER_H
