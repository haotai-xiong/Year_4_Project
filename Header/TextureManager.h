#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class TextureManager {
public:
    TextureManager() {
        loadTexture("house", "../Assets/Project/wood.png");
        loadTexture("factory", "../Assets/Project/red.png");
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
