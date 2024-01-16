#ifndef ENEMY_H
#define ENEMY_H

#include "Buildings.h"

class Enemy {
public:
    Enemy() : m_target(nullptr) {
        m_sprite.setTexture(m_textureManager.getTexture("Enemy_Sample"));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(200.0f, 200.0f);
    }

    void update(const std::vector<std::unique_ptr<Building>>& t_buildings);
    void render(sf::RenderWindow& t_window) const;

private:
    sf::Sprite m_sprite;
    Building* m_target;
    float m_speed = 0.5f;

    void findClosestBuilding(const std::vector<std::unique_ptr<Building>>& t_buildings);
    void moveToTarget();
};

#endif // !ENEMY_H
