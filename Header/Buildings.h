#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Globals.h"

class Building {
public:
    Building(const sf::Vector2f& t_pos) : m_pos(t_pos) {}

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
    House(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("house"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class Factory : public Building {
public:
    Factory(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("factory"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class MidConnection : public Building {
public:
    MidConnection(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("middle"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class TopLeftConnection : public Building {
public:
    TopLeftConnection(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("top left"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class TopRightConnection : public Building {
public:
    TopRightConnection(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("top right"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class BottomLeftConnection : public Building {
public:
    BottomLeftConnection(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("bottom left"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

class BottomRightConnection : public Building {
public:
    BottomRightConnection(const sf::Vector2f& t_pos) : Building(t_pos) {
        m_sprite.setTexture(m_textureManager.getTexture("bottom right"));
        resizeToTileSize();
        m_sprite.setPosition(m_pos);
    }
};

#endif