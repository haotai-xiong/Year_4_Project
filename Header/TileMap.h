#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tile.h"
#include "Buildings.h"

class TileMap {
public:
	TileMap();
	Tile* getTile(sf::Vector2i t_pos);
	void setTile(sf::Vector2i t_pos, TileType t_type);
	void render(sf::RenderWindow& t_window);

    void addHouse(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<House>(worldToTileCoordPos(t_pos)));
    }

    void addFactory(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<Factory>(worldToTileCoordPos(t_pos)));
    }
    
    void addMidConnection(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<MidConnection>(worldToTileCoordPos(t_pos)));
    }

    void addTopLeftConnection(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<TopLeftConnection>(worldToTileCoordPos(t_pos)));
    }

    void addTopRightConnection(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<TopRightConnection>(worldToTileCoordPos(t_pos)));
    }

    void addBottomLeftConnection(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<BottomLeftConnection>(worldToTileCoordPos(t_pos)));
    }

    void addBottomRightConnection(const sf::Vector2f& t_pos) {
        m_buildings.push_back(std::make_unique<BottomRightConnection>(worldToTileCoordPos(t_pos)));
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