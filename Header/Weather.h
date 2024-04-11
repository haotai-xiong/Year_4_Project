#ifndef WEATHER_H
#define WEATHER_H

#include "Globals.h"

class Weather {
public:

    Weather(sf::RenderWindow& renderWindow) : window(renderWindow), distribution(0, renderWindow.getSize().x)
    {
        // Initialize rain
        for (int i = 0; i < rainLimit; ++i) {
            sf::RectangleShape rainDrop(sf::Vector2f(1, 10));
            rainDrop.setPosition(distribution(generator), distribution(generator) % renderWindow.getSize().y);
            rainDrop.setFillColor(sf::Color(196,211,223));
            rainDrops.push_back(rainDrop);
        }

        // Initialize thunder overlay
        thunderOverlay.setSize(sf::Vector2f(renderWindow.getSize()));
        thunderOverlay.setFillColor(sf::Color(255, 255, 255, 180));
    }

    void update(sf::Time deltaTime) {
        if (eventState == Event::Rainy) {
            updateRain();
        }
        else if (eventState == Event::Thunder && !isThundering) {
            sf::Time tempWaitTime = sf::seconds(std::rand() / static_cast<float>(10) + 1);
            if (thunderClock.getElapsedTime() >= tempWaitTime) {
                startThunder(); // Start thunder effect
            }
        }
        else if (eventState == Event::Thunder && isThundering) {
            if (thunderClock.getElapsedTime() >= thunderDuration) {
                isThundering = false; // End thunder effect
            }
        }
    }

    void render() {
        if (eventState == Event::Rainy) {
            for (auto& rainDrop : rainDrops) {
                window.draw(rainDrop);
            }
        }
        else if (eventState == Event::Thunder && isThundering) {
            window.draw(thunderOverlay);
        }
    }

private:
    sf::RenderWindow& window;

    // Rain effect members
    int rainLimit = 500;
    std::vector<sf::RectangleShape> rainDrops;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    // Thunder effect members
    bool isThundering = true;
    sf::Clock thunderClock;
    sf::Time thunderDuration = sf::seconds(0.2f);
    sf::RectangleShape thunderOverlay;

    void updateRain() {
        for (auto& rainDrop : rainDrops) {
            rainDrop.move(0, 5); // Raindrop speed
            if (rainDrop.getPosition().y > window.getSize().y) {
                rainDrop.setPosition(distribution(generator), 0);
            }
        }
    }

    void startThunder() {
        isThundering = true;
        thunderClock.restart();
    }
};

#endif // !WEATHER_H