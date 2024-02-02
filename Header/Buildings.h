#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Globals.h"

class Building {
public:
    Building(const sf::Vector2f& t_pos, std::string t_textureName) : m_pos(t_pos), m_weakLevel(0) {}

    virtual ~Building() {}

    sf::Vector2f pos() const { return m_pos; }
    void pos(sf::Vector2f& t_pos) { m_pos = std::move(t_pos); }
    int weakLevel() const { return m_weakLevel; }
    void weakLevel(int t_level) { m_weakLevel = t_level; }

    virtual void render(sf::RenderWindow& t_window) const {
        t_window.draw(m_sprite);
    }

protected:
    sf::Vector2f m_pos;
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
    }

};

class Factory : public Building {
public:
    Factory(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
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
            woodAmount += woodCollectRate;
            wasteAmount += wasteGenerateRate;
        }

        if (0 == woodAmount % 200 && 0 != woodAmount) {
            std::cout << "Wood Amount " << woodAmount << std::endl;
            std::cout << "Waste Amount " << wasteAmount << std::endl;
        }
    }

private:
    bool hasWoodConnection = false;
    static constexpr int woodCollectRate = 1;
    static constexpr int wasteGenerateRate = 1;
};

class Landfill : public Building {
public:
    Landfill(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 4;
    }

    void woodToEnergy() {
        if (woodAmount / woodConsumeRate > 0)
        {
            woodAmount -= woodConsumeRate;
            energyAmount += energyGenerateRate;

            if (0 == energyAmount % 100) {
                std::cout << "Energy Amount " << energyAmount << std::endl;
            }
        }
    }

    void metalToEnergy() {
        if (metalAmount / metalConsumeRate > 0)
        {
            metalAmount -= metalConsumeRate;
            energyAmount += energyGenerateRate;

            if (0 == energyAmount % 100) {
                std::cout << "Energy Amount " << energyAmount << std::endl;
            }
        }
    }

private:
    static constexpr int woodConsumeRate = 500;
    static constexpr int metalConsumeRate = 500;
    static constexpr int energyGenerateRate = 100;
};

class RecyclingCenter : public Building {
public:
    RecyclingCenter(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize(m_sprite);
        m_sprite.setPosition(m_pos);
        m_weakLevel = 3;
    }
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
    }
};

#endif