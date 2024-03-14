#ifndef ENEMY_H
#define ENEMY_H

#include "TileMap.h"
#include "Weather.h"
#include "memory.h"

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

    sf::Sprite getSprite() const { return m_sprite; }
    void setAlive(bool t_alive) { alive = t_alive; }
    void inGravity(sf::Vector2f t_gravityCenter, bool t_underGravity) {
        m_gravityCenter = t_gravityCenter;
        m_underGravity = t_underGravity;
    }

private:
    sf::Sprite m_sprite;
    Building* m_target;
    float m_speed = 0.5f;
    float m_viewDistance = 75.0f;
    bool alive = true;
    bool m_underGravity;
    sf::Vector2f m_gravityCenter;
    sf::Clock gravityEffectTimer;

    void moveToTarget(TileMap& t_map, Weather& t_weather);
    void moveToGravityCenter(TileMap& t_map, Weather& t_weather);
    bool rayIntersectsObstacle(const sf::Vector2f& t_direction, float t_distance, TileMap& t_map);
    sf::Vector2f rotateVector(const sf::Vector2f& t_vector, float t_angleDegrees);
    void detectTower(TileMap& t_map);
    void escapeGravity();
};

#endif // !ENEMY_H
