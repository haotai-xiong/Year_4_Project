#ifndef STARFIELD_H
#define STARFIELD_H

#include "Globals.h"

class Starfield
{
private:
    std::vector<sf::ConvexShape> stars;
    std::vector<sf::Vector2f> velocities;



public:
    Starfield() { Init(); }

	void Init()
	{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disX(0, SCREEN_WIDTH);
        std::uniform_int_distribution<> disY(0, SCREEN_HEIGHT);
        std::uniform_int_distribution<> disColor(0, 255);
        std::uniform_int_distribution<> disColorA(0, 127);
        std::uniform_real_distribution<> disAngle(-std::numbers::pi, std::numbers::pi);
        std::uniform_real_distribution<> disSpeed(10, 100);
        for (int i = 0; i < 66; i++)
        {
            sf::ConvexShape star(10);
            for (unsigned int i = 0; i < 10; ++i) {
                float radius = (i % 2 == 0) ? 10 : 5;
                float angle = i * std::numbers::pi / 5 - std::numbers::pi / 2;

                star.setPoint(i, sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius));
            }

            star.setFillColor(sf::Color(disColor(gen), disColor(gen), disColor(gen), disColorA(gen)));
            star.setPosition(disX(gen), disY(gen));
            stars.push_back(star);

            // float angle = disAngle(gen);
            float angle = -std::numbers::pi / 4.0f;
            float speed = disSpeed(gen);
            velocities.push_back(sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed));
        }
	}

    void Update()
    {
        for (int i = 0; i < stars.size(); i++)
        {
            sf::Vector2f position = stars[i].getPosition();
            sf::Vector2f velocity = velocities[i];
            position += velocity * 0.1f; // Adjust this factor to control the speed of the stars

            // Wrap the stars around the screen if they go off the edges
            if (position.x < 0) position.x = SCREEN_WIDTH;
            if (position.y < 0) position.y = SCREEN_HEIGHT;
            if (position.x > SCREEN_WIDTH) position.x = 0;
            if (position.y > SCREEN_HEIGHT) position.y = 0;

            stars[i].setPosition(position);
        }
    }

    void Render(sf::RenderWindow& t_window)
    {
        for (const auto& star : stars)
        {
            t_window.draw(star);
        }
    }
};

#endif // !STARFIELD_H