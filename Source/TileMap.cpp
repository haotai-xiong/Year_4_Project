#include "TileMap.h"

TileMap::TileMap() {
	tiles.resize(height_Num, std::vector<Tile>(width_Num, Tile(0, 0, TileType::Traversable)));
	for (int y = 0; y < height_Num; y++) {
		for (int x = 0; x < width_Num; x++) {
			tiles[y][x] = Tile(x, y, TileType::Traversable);
		}
	}

	// random generating numbers to set non-traversable tiles for testing purpose
	for (int i = 0; i < 20; i++) {
		int randX = rand() % width_Num;
		int randY = rand() % height_Num;

		tiles[randY][randX].setType(TileType::NonTraversable);
	}
}

Tile* TileMap::getTile(int t_x, int t_y) {
	if (t_x >= 0 && t_x < width_Num && t_y >= 0 && t_y < height_Num) {
		return &tiles[t_y][t_x];
	}
	return nullptr;
}

void TileMap::setTile(int t_x, int t_y, TileType t_type) {
	if (Tile* tile = getTile(t_x, t_y)) {
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
}
