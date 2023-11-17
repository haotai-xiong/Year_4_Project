#include "Tile.h"

Tile::Tile(sf::Vector2i t_pos, TileType t_type) : m_pos(t_pos), m_type(t_type)
{
	m_rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	m_rect.setPosition(t_pos.x * TILE_SIZE, t_pos.y * TILE_SIZE);
	m_rect.setFillColor(tileTypeToColor[this->m_type]);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(0.5f);
}

sf::Vector2i Tile::getPos() {
	return m_pos;
}

TileType Tile::getType() const {
	return m_type;
}

void Tile::setType(TileType t_type) {
	this->m_type = t_type;
	m_rect.setFillColor(tileTypeToColor[this->m_type]);
}

void Tile::render(sf::RenderWindow& t_window) {
	t_window.draw(m_rect);
}