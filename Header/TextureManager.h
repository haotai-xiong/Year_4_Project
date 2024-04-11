#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <iomanip>
#include <sstream>
#include <random>
#include <numbers>
#include <fstream>
#include <sstream>

class TextureManager {
public:
    TextureManager() {
        // buildings
        loadTexture("house", "../Assets/Project/Building/brown.png");
        loadTexture("factory", "../Assets/Project/Building/red.png");
        loadTexture("recycling center", "../Assets/Project/Building/Recycling Center.png");
        loadTexture("landfill", "../Assets/Project/Building/Landfill.png");
        loadTexture("plant", "../Assets/Project/Building/plant.png");
        loadTexture("tower", "../Assets/Project/Building/tower3.png");
        loadTexture("wood", "../Assets/Project/Building/wood.png");
        loadTexture("projectile", "../Assets/Project/Building/Projectile.png");
        // enemy
        loadTexture("Enemy_Sample", "../Assets/Project/Character/enemy_sample.png");
        loadTexture("Worker_Sample", "../Assets/Project/Character/worker_sample.png");
        // fonts
        loadFont("cheril", "../Assets/Project/Font/CHERL.TTF");
        loadFont("cherii", "../Assets/Project/Font/CHERI.TTF");
        // menu
        loadTexture("menu_background", "../Assets/Project/Menu/background.png");
        loadTexture("play_button", "../Assets/Project/Menu/play.png");
        loadTexture("exit_button", "../Assets/Project/Menu/exit.png");
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
