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
    void update(Weather& t_weather);
    void buildingInit() { m_buildings.clear(); }
    
    template<typename T>
    void addBuilding(const sf::Vector2f t_pos, TileType tileType, const std::string textureName) {
        m_buildings.push_back(std::make_unique<T>(worldToTileCoordPos(t_pos), textureName));
        setTile(worldToTileCoordIndex(t_pos), tileType);
    }

    void renderBuildings(sf::RenderWindow& window) {
        for (const auto& building : m_buildings) {
            building->render(window);

            auto* tower = dynamic_cast<Tower*>(building.get());
            if (tower) {
                tower->drawEmit(window);
            }
        }
    }

    void updateWoodConnections(); 
    const std::vector<std::unique_ptr<Building>>& getBuildings() const { return m_buildings; }
    const std::vector<sf::Vector2f>& getWoods() const { return m_woods; }
    bool isWalkable(const sf::Vector2f& position);


private:
    bool isConnectedToWood(const sf::Vector2i& t_pos);

	std::vector<std::vector<Tile>> tiles;
	int width_Num = SCREEN_WIDTH / TILE_SIZE;
	int height_Num = SCREEN_HEIGHT / TILE_SIZE;

    std::vector<std::unique_ptr<Building>> m_buildings;
    std::vector<sf::Vector2f> m_woods;
};

#endif