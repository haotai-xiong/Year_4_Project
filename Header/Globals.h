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

#endif // !GLOBALS_HPP