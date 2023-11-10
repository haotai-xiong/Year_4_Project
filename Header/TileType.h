#ifndef TILETYPE_H
#define TILETYPE_H

#include <unordered_map>
#include "Globals.h"

enum class TileType {
	Traversable,
	NonTraversable,
	House,
	Factory
};

inline std::unordered_map<TileType, sf::Color> tileTypeToColor = {
	{TileType::Traversable, TraversableColor},
	{TileType::NonTraversable, NonTraversableColor}
};

#endif