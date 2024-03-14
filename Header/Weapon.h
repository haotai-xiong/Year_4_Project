#ifndef WEAPON_H
#define WEAPON_H

#include "Globals.h"
#include "GravitationalVortex.h"

/// <summary>
/// Weapon Class
/// </summary>
class Weapon {

public:
    enum class Type {
        baseGun,
        gravityGun,
        laserGun,
    };

    virtual ~Weapon() = default;
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void render(sf::RenderWindow& t_window) = 0;
    virtual void fire(const sf::Vector2f& t_startPosition, const sf::Vector2f& t_targetPosition) = 0;
};

/// <summary>
/// Base Gun
/// </summary>
class BaseGun : public Weapon {

public:
    BaseGun() {
        bulletShape.setRadius(5.0f);
        bulletShape.setFillColor(sf::Color::White);
    }

    void update(const sf::Time& deltaTime) override {
        std::vector<std::pair<sf::CircleShape, sf::Vector2f>> updatedBullets;

        for (auto& [bullet, velocity] : bullets) {
            bullet.move(velocity * deltaTime.asSeconds());

            if (bullet.getPosition().x >= 0 && bullet.getPosition().x <= SCREEN_WIDTH &&
                bullet.getPosition().y >= 0 && bullet.getPosition().y <= SCREEN_HEIGHT) {
                updatedBullets.push_back(std::make_pair(bullet, velocity));
            }
        }

        bullets = std::move(updatedBullets);
    }

    void render(sf::RenderWindow& window) override {
        for (auto& [bullet, velocity] : bullets) {
            window.draw(bullet);
        }
    }

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) override {
        if (fireClock.getElapsedTime().asSeconds() >= fireInterval && bullets.size() < bulletLimit) {
            sf::CircleShape newBullet = bulletShape;
            newBullet.setPosition(position);
            bullets.push_back(std::make_pair(newBullet, direction * speed));
            fireClock.restart();
        }
    }

    int bulletNumber() { return bullets.size(); }

private:
    sf::CircleShape bulletShape;
    std::vector<std::pair<sf::CircleShape, sf::Vector2f>> bullets;
    float speed = 300.0f;
    unsigned int bulletLimit = 10;
    float fireInterval = 0.25f;
    sf::Clock fireClock;
};

/// <summary>
/// Gravity Gun
/// </summary>
class GravityGun : public Weapon {

public:
    GravityGun() : vortex() {}

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) override {
        vortex.activate(position);
    }

    void update(const sf::Time& deltaTime) override {
        vortex.update();
    }

    void render(sf::RenderWindow& t_window) override {
        vortex.render(t_window);
    }

    sf::CircleShape getShape() { return vortex.getShape(); }
    sf::Vector2f getPosition() { return vortex.getPosition(); }
    float getDuration() { return vortex.getDuration(); }

private:
    GravitationalVortex vortex;
};

/// <summary>
/// Laser Gun
/// </summary>
class LaserGun : public Weapon {

public:
    LaserGun() {
        beam.setSize(sf::Vector2f(200.0f, 5.0f));
        beam.setFillColor(sf::Color::Red);
    }

    void update(const sf::Time& deltaTime) override {
        if (m_active) {
            float elapsedTime = fadeClock.getElapsedTime().asSeconds();
            float alpha = static_cast<float>(initialAlpha) * (1 - (elapsedTime / fadeDuration));
            alpha = std::max(alpha, 0.0f);

            sf::Color currentColor = beam.getFillColor();
            currentColor.a = static_cast<sf::Uint8>(alpha);
            beam.setFillColor(currentColor);

            if (elapsedTime >= fadeDuration) {
                m_active = false;
                resetBeamColor();
            }
        }
    }

    void render(sf::RenderWindow& t_window) override {
        if (m_active) {
            t_window.draw(beam);
        }
    }

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) override {
        beam.setPosition(position);
        m_active = true;
        fadeClock.restart();

        if (direction == sf::Vector2f(0, -1)) { // Up
            beam.setRotation(270); // Rotate beam upwards
        }
        else if (direction == sf::Vector2f(0, 1)) { // Down
            beam.setRotation(90); // Rotate beam downwards
        }
        else if (direction == sf::Vector2f(1, 0)) { // Right
            beam.setRotation(0); // Default orientation (rightwards)
        }
        else if (direction == sf::Vector2f(-1, 0)) { // Left
            beam.setRotation(180); // Rotate beam leftwards
        }
    }

    bool active() const { return m_active; }

private:
    sf::RectangleShape beam;
    bool m_active = false;
    float fadeDuration = 2.0f;
    sf::Clock fadeClock;
    int initialAlpha = 255;

    void resetBeamColor() {
        sf::Color color = beam.getFillColor();
        color.a = initialAlpha;
        beam.setFillColor(color);
    }
};

#endif // !WEAPON_H