#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Globals.h"

class Building {
public:
    Building(const sf::Vector2f& position) : m_pos(position) {}

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
    House(const sf::Vector2f& position) : Building(position) {
        m_sprite.setTexture(m_textureManager.getTexture("house"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class Factory : public Building {
public:
    Factory(const sf::Vector2f& position) : Building(position) {
        m_sprite.setTexture(m_textureManager.getTexture("factory"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

#endif