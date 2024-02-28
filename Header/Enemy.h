#ifndef ENEMY_H
#define ENEMY_H

#include "TileMap.h"
#include "Weather.h"

class Enemy {
public:
    Enemy() : m_target(nullptr) {
        m_sprite.setTexture(m_textureManager.getTexture("Enemy_Sample"));
        resizeToTileSize(m_sprite);
        //m_sprite.setOrigin(sf::Vector2f(25.0f, 25.0f));
        m_sprite.setPosition(generateRandomPosition());
    }

    void update(const std::vector<std::unique_ptr<Building>>& t_buildings, TileMap& t_map, Weather& t_weather);
    void render(sf::RenderWindow& t_window) const;

    void findClosestBuilding(const std::vector<std::unique_ptr<Building>>& t_buildings);

private:
    sf::Sprite m_sprite;
    Building* m_target;
    float m_speed = 0.5f;
    float m_viewDistance = 75.0f;

    void moveToTarget(TileMap& t_map, Weather& t_weather);
    bool rayIntersectsObstacle(const sf::Vector2f& t_direction, float t_distance, TileMap& t_map);
    sf::Vector2f rotateVector(const sf::Vector2f& t_vector, float t_angleDegrees);
};

#endif // !ENEMY_H
