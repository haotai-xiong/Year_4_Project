#include "Enemy.h"

void Enemy::update(const std::vector<std::shared_ptr<Building>>& t_buildings) {
    if (!m_target) {
        findClosestBuilding(t_buildings);
    }

    if (m_target) {
        moveToTarget();
    }
}

void Enemy::render(sf::RenderWindow& t_window) const {
    t_window.draw(m_sprite);
}

void Enemy::findClosestBuilding(const std::vector<std::shared_ptr<Building>>& t_buildings) {
    if (t_buildings.empty()) {
        m_target = nullptr;
        return;
    }

    auto closestIt = std::min_element(t_buildings.begin(), t_buildings.end(),
        [this](const std::shared_ptr<Building>& t_left, const std::shared_ptr<Building>& t_right) {
            return distance(m_sprite.getPosition(), t_left->pos()) <
                distance(m_sprite.getPosition(), t_right->pos());
        });

    m_target = *closestIt;
}

void Enemy::moveToTarget() {
    sf::Vector2f direction = m_target->pos() - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
        m_sprite.move(direction * m_speed);
    }
}