#ifndef GLOBALS_H
#define GLOBALS_H

#include "TextureManager.h"

inline int SCREEN_WIDTH = 1000;
inline int SCREEN_HEIGHT = 1000;
inline int TILE_SIZE = 40;
inline sf::Color TraversableColor = sf::Color::Transparent;
inline sf::Color NonTraversableColor = sf::Color::Color(204, 0, 102);
inline TextureManager m_textureManager;

inline sf::Vector2f worldToTileCoordPos(const sf::Vector2f& t_point) {
    int tileX = static_cast<int>(t_point.x) / TILE_SIZE;
    int tileY = static_cast<int>(t_point.y) / TILE_SIZE;

    return sf::Vector2f(tileX * TILE_SIZE, tileY * TILE_SIZE);
}

inline sf::Vector2i worldToTileCoordIndex(const sf::Vector2f& t_point) {
    int tileX = static_cast<int>(t_point.x) / TILE_SIZE;
    int tileY = static_cast<int>(t_point.y) / TILE_SIZE;

    return sf::Vector2i(tileX, tileY);
}

inline const std::vector<sf::Vector2i> directions = {
        sf::Vector2i(0, -1),  // up
        sf::Vector2i(0, 1),   // down
        sf::Vector2i(-1, 0),  // left
        sf::Vector2i(1, 0)    // right
};

inline int woodAmount = 0;

#endif // !GLOBALS_HPP