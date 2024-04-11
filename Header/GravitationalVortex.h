#ifndef GRAVITATIONALVORTEX_H
#define GRAVITATIONALVORTEX_H

#include <SFML/Graphics.hpp>
#include <numbers>

class GravitationalVortex {

public:
    GravitationalVortex(float initialRadius = 50.0f, float maxRadius = 100.0f, float duration = 5.0f)
        : initialRadius(initialRadius), maxRadius(maxRadius), duration(duration) {
        shape.setRadius(initialRadius);
        shape.setOrigin(initialRadius, initialRadius);
        shape.setFillColor(sf::Color(128, 0, 128, 128));
        // shape.setPosition(-100, -100); // Start off-screen or hidden
    }

    void activate(const sf::Vector2f& t_position) {
        if (!isActive) {
            position = t_position;
            shape.setPosition(position);
            isActive = true;
            animationClock.restart();
        }
    }

    void update() {
        if (!isActive) return;

        float elapsedTime = animationClock.getElapsedTime().asSeconds();
        if (elapsedTime > duration) {
            // shape.setPosition(-100, -100); // Move off-screen or hide after animation
            isActive = false;
            return;
        }

        // Animate radius to pulse
        float radius = initialRadius + (sin(elapsedTime * std::numbers::pi * 2 / duration) + 1) / 2 * (maxRadius - initialRadius);
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);

        // Animate color to fade
        sf::Color color = shape.getFillColor();
        color.a = static_cast<sf::Uint8>((1 - elapsedTime / duration) * 255);
        shape.setFillColor(color);
    }

    void render(sf::RenderWindow& t_window) const {
        if (isActive) {
            t_window.draw(shape);
        }
    }

    const sf::Vector2f& getPosition() const { return position; }
    float getRadius() const { return radius; }
    sf::CircleShape getShape() { return shape; }
    float getDuration() { return duration; }

private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float radius = 100.0f;
    sf::Clock lifetime;
    float duration = 5.0f;
    bool isActive = false;
    sf::Clock animationClock;
    float initialRadius;
    float maxRadius;
};

#endif // !GRAVITATIONALVORTEX_H