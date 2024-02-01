#ifndef ENEMY_H
#define ENEMY_H

#include "Buildings.h"
#include "TileMap.h"

class Enemy {
public:
    Enemy() : m_target(nullptr) {
        m_sprite.setTexture(m_textureManager.getTexture("Enemy_Sample"));
        resizeToTileSize(m_sprite);
        //m_sprite.setOrigin(sf::Vector2f(25.0f, 25.0f));
        m_sprite.setPosition(200.0f, 200.0f);
    }

    void update(const std::vector<std::unique_ptr<Building>>& t_buildings, TileMap& t_map);
    void render(sf::RenderWindow& t_window) const;

private:
    sf::Sprite m_sprite;
    Building* m_target;
    float m_speed = 0.5f;
    float m_viewDistance = 50.0f;

    void findClosestBuilding(const std::vector<std::unique_ptr<Building>>& t_buildings);
    void moveToTarget(TileMap& t_map);
    bool rayIntersectsObstacle(const sf::Vector2f& t_direction, float t_distance, TileMap& t_map);
    sf::Vector2f rotateVector(const sf::Vector2f& t_vector, float t_angleDegrees);
};

#endif // !ENEMY_H
