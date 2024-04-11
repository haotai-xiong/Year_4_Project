#ifndef WORKER_H
#define WORKER_H

#include "TileMap.h"

class Worker {
public:
    enum class Status {
        born,
        headToWood,
        farming,
        backToFactory
    };

    sf::Sprite sprite;
    bool factoryAssigned = false;
    Building* targetFactory;
    sf::Vector2f targetWood;
    sf::Clock workClock;
    Status _status = Worker::Status::born;

    Worker() {
        sprite.setTexture(m_textureManager.getTexture("Worker_Sample"));
        resizeToTileSize(sprite);
        sprite.setScale(sprite.getScale() / 1.5f);
    }

    void update(const sf::Time& t_deltaTime, const std::vector<std::unique_ptr<Building>>& t_buildings, TileMap& t_map) {
        findFactory(t_buildings);

        switch (_status)
        {
        case Worker::Status::born:
            if (factoryAssigned) {
                findClosetWood(t_map);
            }
            break;
        case Worker::Status::headToWood:
            moveTowardsTargetWood(t_deltaTime);
            break;
        case Worker::Status::farming:
            farming();
            break;
        case Worker::Status::backToFactory:
            moveTowardsTargetFactory(t_deltaTime);
            break;
        default:
            break;
        }
    }

    void render(sf::RenderWindow& t_window) const {
        t_window.draw(sprite);
    }

    void findFactory(const std::vector<std::unique_ptr<Building>>& t_buildings) {
        if (!factoryAssigned) {
            for (auto& building : t_buildings) {
                auto* factory = dynamic_cast<Factory*>(building.get());
                if (factory && !factory->workerAssigned) {
                    factory->workerAssigned = true;
                    targetFactory = factory;
                    factoryAssigned = true;
                    sprite.setPosition(targetFactory->pos());
                    break;
                }
            }
        }
    }

private:
    float m_speed = 20.0f;

    void findClosetWood(TileMap& t_map) {
        auto closestIt = std::min_element(t_map.getWoods().begin(), t_map.getWoods().end(),
            [this](const sf::Vector2f& t_left, const sf::Vector2f& t_right) {
                return distance(t_left, sprite.getPosition()) <
                    distance(t_right, sprite.getPosition());
            });

        targetWood = sf::Vector2f(closestIt->x, closestIt->y);
        _status = Worker::Status::headToWood;
    }

    void moveTowardsTargetWood(const sf::Time& deltaTime) {
        sf::Vector2f currentPosition = sprite.getPosition();
        sf::Vector2f direction = targetWood - currentPosition;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;

        sf::Vector2f step = direction * m_speed * deltaTime.asSeconds();
        sprite.move(step);

        if (distance(sprite.getPosition(), targetWood) < TILE_SIZE / 2.0f) {
            workClock.restart();
            _status = Worker::Status::farming;
        }
    }

    void moveTowardsTargetFactory(const sf::Time& deltaTime) {
        sf::Vector2f currentPosition = sprite.getPosition();
        sf::Vector2f direction = targetFactory->pos() - currentPosition;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;

        sf::Vector2f step = direction * m_speed * deltaTime.asSeconds();
        sprite.move(step);

        if (distance(sprite.getPosition(), targetFactory->pos()) < TILE_SIZE / 2.0f) {
            woodAmount += 200;
            wasteAmount += 20;
            workClock.restart();
            _status = Worker::Status::headToWood;
        }
    }

    void farming() {
        if (workClock.getElapsedTime().asSeconds() > 5.0f) {
            _status = Worker::Status::backToFactory;
        }
    }
};

#endif // !WORKER_H