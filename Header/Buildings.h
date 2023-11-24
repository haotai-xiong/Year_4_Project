#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Globals.h"

class Building {
public:
    Building(const sf::Vector2f& t_pos, std::string t_textureName) : m_pos(t_pos) {}

    virtual ~Building() {}

    sf::Vector2f pos() const { return m_pos; }
    void pos(sf::Vector2f& t_pos) { m_pos = std::move(t_pos); }
    
    void resizeToTileSize() {
        float scaleX = static_cast<float>(TILE_SIZE) / m_sprite.getLocalBounds().width;
        float scaleY = static_cast<float>(TILE_SIZE) / m_sprite.getLocalBounds().height;
        m_sprite.setScale(scaleX, scaleY);
    }

    virtual void render(sf::RenderWindow& t_window) const {
        t_window.draw(m_sprite);
    }

protected:
    sf::Vector2f m_pos;
    sf::Sprite m_sprite;
};

class House : public Building {
public:
    House(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class Factory : public Building {
public:
    Factory(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }

    void connectToWood() {
        hasWoodConnection = true;
    }

    void disconnectWood() {
        hasWoodConnection = false;
    }

    void updateWoodCollection() {
        if (hasWoodConnection) {
            woodAmount += woodCollectionRate;
        }

        if (0 == woodAmount % 50) {
            std::cout << "Wood Amount " << woodAmount << std::endl;
        }
    }

private:
    bool hasWoodConnection = false;
    static constexpr int woodCollectionRate = 1;
};

class Connection : public Building {
public:
    Connection(const sf::Vector2f& t_pos, std::string t_textureName) : Building(t_pos, t_textureName) {
        m_sprite.setTexture(m_textureManager.getTexture(t_textureName));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

#endif