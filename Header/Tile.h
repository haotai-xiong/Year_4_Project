#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
public:
	Tile(sf::Vector2i t_pos, TileType t_type);
	// int getX() const;
	// int getY() const;
	sf::Vector2i getPos();
	TileType getType() const;
	void setType(TileType t_type);
	void render(sf::RenderWindow& t_window);

private:
	sf::Vector2i m_pos; // X & Y index
	TileType m_type;
	sf::RectangleShape m_rect;
};

#endif