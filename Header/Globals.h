#ifndef GLOBALS_H
#define GLOBALS_H

#include "TextureManager.h"

inline int SCREEN_WIDTH = 1000;
inline int SCREEN_HEIGHT = 1000;
inline int TILE_SIZE = 40;
inline sf::Color TraversableColor = sf::Color::Transparent;
inline sf::Color NonTraversableColor = sf::Color::Color(204, 0, 102);
inline TextureManager m_textureManager;

#endif // !GLOBALS_HPP

