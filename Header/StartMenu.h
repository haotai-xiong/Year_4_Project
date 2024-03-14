#ifndef STARTMENU_H
#define STARTMENU_H

#include "Starfield.h"

struct MenuItem {
    sf::Text text;
    sf::Sprite buttonSprite;
    std::function<void()> action;

    MenuItem(const sf::Font& font, const std::string& title, const std::function<void()>& action)
        : action(action) {
        // text.setFont(font);
        // text.setString(title);
        // text.setCharacterSize(24);
        buttonSprite.setTexture(m_textureManager.getTexture(title));
        buttonSprite.setOrigin(sf::Vector2f(buttonSprite.getGlobalBounds().width / 2.0f, buttonSprite.getGlobalBounds().height / 2.0f));
    }
};

class StartMenu {

public:
    StartMenu() {
        background.setTexture(m_textureManager.getTexture("menu_background"));
        background.setOrigin(sf::Vector2f(background.getGlobalBounds().width / 2.0f, background.getGlobalBounds().height / 2.0f));
        background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
    }

    void addItem(const std::string& title, const std::function<void()>& action) {
        float y = 500 + items.size() * 200;
        items.emplace_back(m_textureManager.getFont("cherii"), title, action);
        // items.back().text.setPosition(500, y);
        items.back().buttonSprite.setPosition(sf::Vector2f(500.0f, y));
    }

    void update(sf::RenderWindow& t_window) {
        sf::Vector2f mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
        for (auto& item : items) {
            // hover effect - change text color
            /*
            if (item.text.getGlobalBounds().contains(mousePos)) {
                item.text.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    item.action();
                }
            }
            else {
                item.text.setFillColor(sf::Color::White);
            }
            */
            if (item.buttonSprite.getGlobalBounds().contains(mousePos)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    item.action();
                }
            }
        }

        m_starfield.Update();
    }

    void render(sf::RenderWindow& t_window) {
        t_window.draw(background);
        m_starfield.Render(t_window);
        for (const auto& item : items) {
            t_window.draw(item.text);
            t_window.draw(item.buttonSprite);
        }
    }

private:
    std::vector<MenuItem> items;
    sf::Sprite background;
    Starfield m_starfield;
};

#endif // !STARTMENU_H