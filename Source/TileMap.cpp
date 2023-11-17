#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height_Num, std::vector<Tile>(width_Num, Tile(sf::Vector2i(0, 0), TileType::Traversable)));
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x] = Tile(sf::Vector2i(x, y), TileType::Traversable);
		}
	}

	// random generating numbers to set non-traversable tiles for testing purpose
	for (int i = 0; i < 20; i++) {
		int randX = rand() % width_Num;
		int randY = rand() % height_Num;

		tiles[randY][randX].setType(TileType::NonTraversable);
	}

	addHouse(sf::Vector2f(500.0f, 500.0f));
}

Tile* TileMap::getTile(sf::Vector2i t_pos) {
	if (t_pos.x >= 0 && t_pos.x < width_Num && t_pos.y >= 0 && t_pos.y < height_Num) {
		return &tiles[t_pos.y][t_pos.x];
	}
	return nullptr;
}

void TileMap::setTile(sf::Vector2i t_pos, TileType t_type) {
	if (Tile* tile = getTile(t_pos)) {
		tile->setType(t_type);
	}
}

void TileMap::render(sf::RenderWindow& t_window)
{
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x].render(t_window);
		}
	}
	renderBuildings(t_window);
}