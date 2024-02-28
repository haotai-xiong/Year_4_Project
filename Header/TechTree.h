#ifndef TECHTREE_H
#define TECHTREE_H

#include "Globals.h"

class TechTree {
public:
    TechTree(sf::RenderWindow& window)
        : m_window(window), menuVisible(false) {
        // Setup the button
        button.setSize(sf::Vector2f(100, 50));
        button.setPosition(900, 10); // Position it at the top-left corner
        button.setFillColor(sf::Color::White);

        // Setup the menu background
        menu.setSize(sf::Vector2f(300, 400));
        menu.setPosition(50, 50);
        menu.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

        menuText.setFont(m_textureManager.getFont("cherii"));
        menuText.setString("Tech Tree");
        menuText.setCharacterSize(24);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition(60, 60);
    }

    void update(sf::Event event) {
        // Toggle menu visibility on button click
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuVisible = !menuVisible;
                }
            }
        }
    }

    void render() {
        m_window.draw(button); // Always draw the button
        if (menuVisible) {
            m_window.draw(menu);
            m_window.draw(menuText);
        }
    }

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape button;
    sf::RectangleShape menu;
    sf::Text menuText;
    sf::Font font;
    bool menuVisible;
};

#endif // !TECHTREE_H