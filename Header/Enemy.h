#ifndef ENEMY_H
#define ENEMY_H

#include "Buildings.h"

class Enemy {
public:
    Enemy() : m_target(nullptr) {
        m_sprite.setTexture(m_textureManager.getTexture("Enemy_Sample"));
        resizeToTileSize(m_sprite);
    }

    void update(const std::vector<std::shared_ptr<Building>>& t_buildings);
    void render(sf::RenderWindow& t_window) const;

private:
    sf::Sprite m_sprite;
    std::shared_ptr<Building> m_target;
    float m_speed = 5.0f;

    void findClosestBuilding(const std::vector<std::shared_ptr<Building>>& t_buildings);
    void moveToTarget();
};

#endif // !ENEMY_H
