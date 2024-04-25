#ifndef EVENTUI_H
#define EVENTUI_H

#include "TextureManager.h"

class EventUI {
public:
	EventUI() {
		textInit();
	}

    void update() {
        if (isVisible) {
            float elapsedTime = fadeClock.getElapsedTime().asSeconds();
            float alpha = initialAlpha * (1 - elapsedTime / fadeDuration);
            if (alpha < 0) {
                isVisible = false;
                alpha = 0;
            }

            float time = fmod(elapsedTime, fadeDuration) / fadeDuration;
            sf::Uint8 red = static_cast<sf::Uint8>((sin(time * 2 * 3.1415926) * 0.5 + 0.5) * 255);
            sf::Uint8 green = static_cast<sf::Uint8>((sin(time * 2 * 3.1415926 + 2 * 3.1415926 / 3) * 0.5 + 0.5) * 255);
            sf::Uint8 blue = static_cast<sf::Uint8>((sin(time * 2 * 3.1415926 + 4 * 3.1415926 / 3) * 0.5 + 0.5) * 255);
            text.setFillColor(sf::Color(red, green, blue, static_cast<sf::Uint8>(alpha)));
        }
    }

    void render(sf::RenderWindow& t_window) const {
        if (isVisible) {
            t_window.draw(text);
        }
    }


    void show() {
        switch (eventState)
        {
        case Event::None:
            text.setString("");
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
            text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            break;
        case Event::EnemyRaging:
            text.setString("ENEMY RAGING!\nDOUBLE SPEEDING!");
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
            text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            break;
        case Event::Rainy:
            text.setString("BIG RAINY!\nENEMY GOT SLOWED!");
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
            text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            break;
        case Event::Thunder:
            text.setString("THUNDERING!");
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
            text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            break;
        }

        isVisible = true;
        fadeClock.restart();
    }

private:
	void textInit() {
		text.setFont(m_textureManager.getFont("cherii"));
		text.setString("");
		text.setCharacterSize(60.0f);
		text.setFillColor(sf::Color(255, 255, 255, initialAlpha));
	}

	sf::Text text;
	sf::Clock fadeClock;
	bool isVisible = false;
	float fadeDuration = 3.0f;
	float initialAlpha = 255.0f;
};

#endif // !EVENTUI_H