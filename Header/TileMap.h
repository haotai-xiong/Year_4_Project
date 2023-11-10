#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tile.h"
#include "Buildings.h"

class TileMap {
public:
	TileMap();
	Tile* getTile(int t_x, int t_y);
	void setTile(int t_x, int t_y, TileType t_type);
	void render(sf::RenderWindow& t_window);

    void addHouse(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<House>(worldToTileCoordPos(t_pos)));
    }

    void addFactory(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<Factory>(worldToTileCoordPos(t_pos)));
    }

    // Render all buildings
    void renderBuildings(sf::RenderWindow& window) {
        for (const auto& building : m_buildings) {
            building->render(window);
        }
    }

private:
	std::vector<std::vector<Tile>> tiles;
	int width_Num = SCREEN_WIDTH / TILE_SIZE;
	int height_Num = SCREEN_HEIGHT / TILE_SIZE;

    std::vector<std::unique_ptr<Building>> m_buildings;
};

#endif