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

		tiles[randY][randX].setType(TileType::Wood);
	}
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

void TileMap::update() {
	// updateWoodConnections();

	for (auto& building : m_buildings) {
		auto* factory = dynamic_cast<Factory*>(building.get());
		if (factory) {
			factory->updateWoodCollection();
		}
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

void TileMap::updateWoodConnections() {
	for (auto& building : m_buildings) {
		auto* factory = dynamic_cast<Factory*>(building.get());
		if (factory) {
			if (isConnectedToWood(worldToTileCoordIndex(factory->pos()), sf::Vector2i(0, 0))) {
				factory->connectToWood();
			}
			else {
				factory->disconnectWood();
			}
		}
	}
}

bool TileMap::isConnectedToWood(const sf::Vector2i& t_pos, const sf::Vector2i t_previousConnection) {
	for (const auto& dir : directions) {
		if (dir == t_previousConnection) {
			continue;
		}

		sf::Vector2i checkPos = t_pos + dir;
		Tile* tile = getTile(checkPos);
		if (tile && tile->getType() == TileType::Wood) {
			return true;
		}
		else if (tile && tile->getType() == TileType::Connection) {
			isConnectedToWood(checkPos, -dir);
		}
	}
	return false;
}