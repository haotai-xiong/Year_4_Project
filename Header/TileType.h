#ifndef TILETYPE_H
#define TILETYPE_H

#include <unordered_map>
#include "Globals.h"

enum class TileType {
	Traversable,
	NonTraversable
};

extern std::unordered_map<TileType, sf::Color> tileTypeToColor;

#endif