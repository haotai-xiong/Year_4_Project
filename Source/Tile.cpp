#include "Tile.h"

Tile::Tile(int t_x, int t_y, TileType t_type) : m_x(t_x), m_y(t_y), m_type(t_type)
{
	m_rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	m_rect.setPosition(t_x * TILE_SIZE, t_y * TILE_SIZE);
	m_rect.setFillColor(tileTypeToColor[this->m_type]);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(0.5f);
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
	m_rect.setFillColor(tileTypeToColor[this->m_type]);
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_rect);
}