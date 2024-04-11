#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Weather.h"

class Building {
public:
    Building(const sf::Vector2f& t_pos, std::string t_textureName) : m_pos(t_pos), m_weakLevel(0), m_textureName(t_textureName) {}
    virtual ~Building() {}

    sf::Vector2f pos() const { return m_pos; }
    void pos(sf::Vector2f& t_pos) { m_pos = std::move(t_pos); }
    sf::Sprite sprite() const { return m_sprite; }
    int weakLevel() const { return m_weakLevel; }
    void weakLevel(int t_level) { m_weakLevel = t_level; }
    std::string textureName() const { return m_textureName; }

    virtual void render(sf::RenderWindow& t_window) const {
        t_window.draw(m_sprite);
    }

protected:
    sf::Vector2f m_pos;
    std::string m_textureName;
    sf::Sprite m_sprite;
    int m_weakLevel;
};

class House : public Building {
public:
    House(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 2;
        woodAmount -= woodCost;
    }

private:
    int woodCost = 500;
};

class Factory : public Building {
public:
    Factory(const sf::Vector2f& t_pos, std::string t_textureName) 
        : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 10;
    }

    void connectToWood() {
        hasWoodConnection = true;
    }

    void disconnectWood() {
        hasWoodConnection = false;
    }

    void updateWoodCollection() const {
        if (hasWoodConnection) {
            if (eventState == Event::Thunder) {
                woodAmount += woodCollectRateThunder;
                wasteAmount += wasteGenerateRate;
            }
            else {
                woodAmount += woodCollectRate;
                wasteAmount += wasteGenerateRate;
            }
        }

        if (0 == woodAmount % 200 && 0 != woodAmount) {
            std::cout << "Wood Amount " << woodAmount << std::endl;
            std::cout << "Waste Amount " << wasteAmount << std::endl;
        }
    }

    bool workerAssigned = false;

private:
    bool hasWoodConnection = false;
    static constexpr int woodCollectRate = 2;
    static constexpr int woodCollectRateThunder = 1;
    static constexpr float wasteGenerateRate = 0.05f;
};

class Landfill : public Building {
public:
    Landfill(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 0));
        m_sprite.setPosition(m_pos);
        m_weakLevel = 4;
    }

    void woodToEnergy() {
        if (woodAmount / woodConsumeRate > 0) {
            m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 25.5 * landfillClock.getElapsedTime().asSeconds()));
            if (landfillClock.getElapsedTime().asSeconds() >= 10.0f) {
                landfillClock.restart();
                woodAmount -= woodConsumeRate;
                energyAmount += energyGenerateRate;

                if (0 == energyAmount % 100) {
                    std::cout << "Energy Amount " << energyAmount << std::endl;
                }
            }
        }
        else {
            m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, 255));
        }
    }

    /*
    void metalToEnergy() {
        if (metalAmount / woodTriggerNumber > 0)
        {
            metalAmount -= metalConsumeRate;
            energyAmount += energyGenerateRate;

            if (0 == energyAmount % 100) {
                std::cout << "Energy Amount " << energyAmount << std::endl;
            }
        }
    }
    */

private:
    static constexpr int woodConsumeRate = 300;
    static constexpr int metalConsumeRate = 500;
    static constexpr int energyGenerateRate = 100;
    sf::Clock landfillClock;
};

class RecyclingCenter : public Building {
public:
    RecyclingCenter(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 3;
    }

    void wasteToEnegy() {

    }

private:
    sf::Clock recyclock;
};

class Plant : public Building {
public:
    Plant(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 1;
    }
};

class Connection : public Building {
public:
    Connection(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
    }
};

class Tower : public Building {
public:
    Tower(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 0;
        woodAmount -= m_woodCost;

        m_emitter.setRadius(m_radius); 
        m_emitter.setOrigin(m_radius, m_radius);
        m_emitter.setPosition(sf::Vector2f(m_pos.x + 20.0f, m_pos.y + 20.0f));
        m_emitter.setOutlineColor(sf::Color::White);
        m_emitter.setOutlineThickness(3.0f);
        m_emitter.setFillColor(sf::Color::Transparent);
    }

    void drawEmit(sf::RenderWindow& t_window) {
        m_emitter.setRadius(m_radius);
        m_emitter.setOrigin(m_radius, m_radius);
        m_emitter.setPosition(sf::Vector2f(m_pos.x + 20.0f, m_pos.y + 20.0f));
        t_window.draw(m_emitter);

        m_radius += growthRate;

        if (m_radius >= m_MAXRADIUS)
        {
            m_radius = 1.0f;
        }
    }

    float MAXRADIUS() const { return m_MAXRADIUS; }

private:
    sf::CircleShape m_emitter;
    float m_radius = 1.0f;
    float growthRate = 0.01f;
    float m_MAXRADIUS = 80.0f;
    int m_woodCost = 1000;
};

#endif