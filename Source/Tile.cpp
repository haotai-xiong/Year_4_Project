#include "Tile.h"

Tile::Tile(int t_x, int t_y, TileType t_type) : m_x(t_x), m_y(t_y), m_type(t_type)
{
	m_rect.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
	m_rect.setPosition(t_x * TILE_WIDTH, t_y * TILE_HEIGHT);
}

int Tile::getX() const
{
	return m_x;
}

int Tile::getY() const
{
	return m_y;
}

TileType Tile::getType() const
{
	return m_type;
}

void Tile::setType(TileType t_type)
{
	this->m_type = t_type;
}

void Tile::render(sf::RenderWindow& t_window)
{
	m_rect.setFillColor(tileTypeToColor[this->m_type]);
	t_window.draw(m_rect);
}