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
        loadTexture("house", "../Assets/Project/wood.png");
        loadTexture("factory", "../Assets/Project/red.png");
        loadTexture("recycling center", "../Assets/Project/Recycling Center.png");
        loadTexture("landfill", "../Assets/Project/Landfill.png");
        loadTexture("plant", "../Assets/Project/plant.png");
        // connections
        loadTexture("middle", "../Assets/Project/Connection/middle.png");
        loadTexture("middle2", "../Assets/Project/Connection/middle2.png");
        loadTexture("top left", "../Assets/Project/Connection/top_left.png");
        loadTexture("top right", "../Assets/Project/Connection/top_right.png");
        loadTexture("bottom left", "../Assets/Project/Connection/bottom_left.png");
        loadTexture("bottom right", "../Assets/Project/Connection/bottom_right.png");
    }
    ~TextureManager() {}

    void loadTexture(const std::string name, const std::string filename) {
        sf::Texture texture;
        texture.loadFromFile(filename);
        textures[name] = texture;
    }

    sf::Texture& getTexture(const std::string name) {
        return textures.at(name);
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
};

#endif // TEXTURE_MANAGER_H
