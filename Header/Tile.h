#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
public:
	Tile(int t_x, int t_y, TileType t_type);
	int getX() const;
	int getY() const;
	TileType getType() const;
	void setType(TileType t_type);
	void render(sf::RenderWindow& t_window);

private:
	int m_x, m_y; // X & Y index
	TileType m_type;
	sf::RectangleShape m_rect;
};

#endif