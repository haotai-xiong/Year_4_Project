#include "TileType.h"

std::unordered_map<TileType, sf::Color> tileTypeToColor = {
	{TileType::Traversable, TraversableColor},
	{TileType::NonTraversable, NonTraversableColor}
};