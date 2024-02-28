#include "Enemy.h"

void Enemy::update(const std::vector<std::unique_ptr<Building>>& t_buildings, TileMap& t_map, Weather& t_weather) {
    if (!m_target) {
        findClosestBuilding(t_buildings);
    }
    if (m_target) {
        moveToTarget(t_map, t_weather);
    }
}

void Enemy::render(sf::RenderWindow& t_window) const {
    t_window.draw(m_sprite);
}

void Enemy::findClosestBuilding(const std::vector<std::unique_ptr<Building>>& t_buildings) {
    if (t_buildings.empty()) {
        m_target = nullptr;
        return;
    }

    auto closestIt = std::min_element(t_buildings.begin(), t_buildings.end(),
        [this](const std::unique_ptr<Building>& t_left, const std::unique_ptr<Building>& t_right) {
            return t_left->weakLevel() >
                t_right->weakLevel();
        });

    m_target = closestIt->get();
}

void Enemy::moveToTarget(TileMap& t_map, Weather& t_weather) {
    sf::Vector2f direction = m_target->pos() - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length; // Normalize the direction vector

        // Check for obstacles in the current direction
        if (rayIntersectsObstacle(direction, m_viewDistance, t_map)) {
            // Try to find a clear path by rotating the direction vector
            const float rotationStep = 45; // Degrees to rotate at each step
            bool pathFound = false;

            for (float angle = rotationStep; angle < 360; angle += rotationStep) {
                // Rotate direction clockwise and counter-clockwise
                sf::Vector2f newDirections[2] = {
                    rotateVector(direction, angle),
                    rotateVector(direction, -angle)
                };

                for (const auto& newDir : newDirections) {
                    if (!rayIntersectsObstacle(newDir, m_viewDistance, t_map)) {
                        direction = newDir;
                        pathFound = true;
                        break;
                    }
                }
                if (pathFound) break;
            }
        }

        // Move in the chosen direction
        if (t_weather.getCurrentWeather() == Weather::Type::Rainy) {
            m_sprite.move(direction * m_speed * 0.5f);
        }
        else {
            m_sprite.move(direction * m_speed);
        }
    }
}


bool Enemy::rayIntersectsObstacle(const sf::Vector2f& t_direction, float t_distance, TileMap& t_map) {
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    sf::Vector2f centerPosition = sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    sf::Vector2f currentPosition = centerPosition;
    sf::Vector2f step = t_direction / 5.0f;

    for (float d = 0; d < t_distance; d += std::sqrt(step.x * step.x + step.y * step.y)) {
        currentPosition += step;
        if (!t_map.isWalkable(currentPosition)) {
            return true;
        }
    }
    return false;
}

sf::Vector2f Enemy::rotateVector(const sf::Vector2f& t_vector, float t_angleDegrees) {
    float rad = t_angleDegrees * (3.14159265f / 180.0f); // Convert degrees to radians
    return sf::Vector2f(
        t_vector.x * cos(rad) - t_vector.y * sin(rad),
        t_vector.x * sin(rad) + t_vector.y * cos(rad)
    );
}