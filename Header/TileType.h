#ifndef TILETYPE_H
#define TILETYPE_H

#include <unordered_map>
#include "Globals.h"

enum class TileType {
	Traversable,
	NonTraversable,
	House,
	Factory,
	RecyclingCenter,
	Landfill,
	Wood,
	Connection
};

inline std::unordered_map<TileType, sf::Color> tileTypeToColor = {
	{TileType::Traversable, TraversableColor},
	{TileType::Wood, NonTraversableColor}
};

#endif