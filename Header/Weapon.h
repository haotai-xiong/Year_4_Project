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
        heavyLaserGun
    };

    virtual ~Weapon() = default;
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void render(sf::RenderWindow& t_window) = 0;
    // virtual void fire(const sf::Vector2f& t_startPosition, const sf::Vector2f& t_targetPosition) = 0;
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
                bullet.getPosition().y >= 0 && bullet.getPosition().y <= SCREEN_HEIGHT &&
                velocity != sf::Vector2f(0.0f, 0.0f)) {
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

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) {
        if (fireClock.getElapsedTime().asSeconds() >= fireInterval && bullets.size() < bulletLimit) {
            sf::CircleShape newBullet = bulletShape;
            newBullet.setPosition(position);
            bullets.push_back(std::make_pair(newBullet, direction * speed));
            fireClock.restart();
        }
    }

    bool checkCollision(sf::Sprite t_sprite, bool t_enemyAlive) {
        for (auto& [bullet, velocity] : bullets) {
            if (bullet.getGlobalBounds().intersects(t_sprite.getGlobalBounds()) && t_enemyAlive &&
                velocity != sf::Vector2f(0.0f, 0.0f)) {
                velocity = sf::Vector2f(0.0f, 0.0f);
                return true;
            }
        }
        return false;
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

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) {
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

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction) {
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

    sf::RectangleShape& getBeam() { return beam; }
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


/// <summary>
/// Heavy Laser Gun
/// </summary>
class HeavyLaserGun : public Weapon {
public:
    HeavyLaserGun() {
        laserBeam.setFillColor(sf::Color::Red);
    }

    void update(const sf::Time& deltaTime) override {
        if (isCharging) {
            chargeTime = chargeClock.getElapsedTime().asSeconds();
        }
        else if (isReleasing) {
            chargeClock.restart();
            // adjust the beam's size based on charge time
            float thickness = std::min(50.0f, 1.0f + chargeTime * 10.0f);
            float length = 50.0f + chargeTime * 100.0f;
            laserBeam.setSize(sf::Vector2f(length, thickness));
            laserBeam.setOrigin(0, thickness / 2.0f);

            float elapsedTime = fadeClock.getElapsedTime().asSeconds();
            float alpha = static_cast<float>(initialAlpha) * (1 - (elapsedTime / fadeDuration));
            alpha = std::max(alpha, 0.0f);

            sf::Color currentColor = laserBeam.getFillColor();
            currentColor.a = static_cast<sf::Uint8>(alpha);
            laserBeam.setFillColor(currentColor);

            if (elapsedTime >= fadeDuration) {
                isReleasing = false;
                chargeClockRestarted = false;
                resetBeamColor();
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        if (isReleasing) {
            window.draw(laserBeam);
        }
    }

    void startCharging() {
        if (!isReleasing) {
            isCharging = true;
            isReleasing = false;
        }
    }

    void release(sf::Vector2f& t_playerPos, const sf::Vector2f& t_direction) {
        if (isCharging) {
            std::cout << "Firing laser beam with charge time: " << chargeTime << " seconds" << std::endl;

            resetBeam(t_playerPos);
            isCharging = false;
            isReleasing = true;
            fadeClock.restart();

            if (t_direction == sf::Vector2f(0, -1)) { // Up
                laserBeam.setRotation(270); // Rotate beam upwards
            }
            else if (t_direction == sf::Vector2f(0, 1)) { // Down
                laserBeam.setRotation(90); // Rotate beam downwards
            }
            else if (t_direction == sf::Vector2f(1, 0)) { // Right
                laserBeam.setRotation(0); // Default orientation (rightwards)
            }
            else if (t_direction == sf::Vector2f(-1, 0)) { // Left
                laserBeam.setRotation(180); // Rotate beam leftwards
            }
        }
    }

    void restartChargeClock() {
        if (!chargeClockRestarted) {
            chargeClock.restart();
            chargeClockRestarted = true;
        }
    }
    
    sf::RectangleShape& getLaserBeam() { return laserBeam; }
    bool active() const { return isReleasing; }

private:
    sf::RectangleShape laserBeam;
    bool isCharging = false;
    bool isReleasing = false;
    bool chargeClockRestarted = false;
    float chargeTime = 0.0f; // Time in seconds the gun has been charging
    sf::Clock chargeClock;

    float fadeDuration = 2.0f;
    sf::Clock fadeClock;
    int initialAlpha = 255;

    void resetBeamColor() {
        sf::Color color = laserBeam.getFillColor();
        color.a = initialAlpha;
        laserBeam.setFillColor(color);
    }

    void resetBeam(sf::Vector2f& t_playerPos) {
        laserBeam.setSize(sf::Vector2f(200.0f, 1.0f));
        laserBeam.setPosition(t_playerPos);
    }
};

#endif // !WEAPON_H