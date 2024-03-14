#ifndef TECHTREE_H
#define TECHTREE_H

#include "Player.h"

class TechTree {
public:
    TechTree(sf::RenderWindow& window)
        : m_window(window), menuVisible(false) {
        // Setup the button
        button.setSize(sf::Vector2f(100, 50));
        button.setPosition(900, 10);
        button.setFillColor(sf::Color(255, 255, 255, 150));
        buttonText.setFont(m_textureManager.getFont("cherii"));
        buttonText.setString("Tech Tree");
        buttonText.setCharacterSize(15);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(915, 25);

        // Setup the menu background
        menu.setSize(sf::Vector2f(300, 400));
        menu.setPosition(0, 100);
        menu.setFillColor(sf::Color(100, 100, 100, 192));

        menuText.setFont(m_textureManager.getFont("cherii"));
        menuText.setString("TECH TREE");
        menuText.setCharacterSize(20);
        menuText.setOrigin(sf::Vector2f(menuText.getGlobalBounds().width / 2.0f, menuText.getGlobalBounds().height / 2.0f));
        menuText.setFillColor(sf::Color::Black);
        menuText.setPosition(150, 110);

        // Weapon button init
        weaponButtonInit();
    }

    void update(sf::Event event, Player& t_player) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuVisible = !menuVisible;
                }
                else if (baseGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    t_player.setCurrentWeapon(Weapon::Type::baseGun);
                    menuVisible = !menuVisible;
                }
                else if (gravityGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    t_player.setCurrentWeapon(Weapon::Type::gravityGun);
                    menuVisible = !menuVisible;
                }
                else if (laserGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    t_player.setCurrentWeapon(Weapon::Type::laserGun);
                    menuVisible = !menuVisible;
                }
            }
        }
    }

    void render() {
        m_window.draw(button); // Always draw the button
        m_window.draw(buttonText);
        if (menuVisible) {
            m_window.draw(menu);
            m_window.draw(menuText);
            m_window.draw(baseGunButton);
            m_window.draw(baseGunText);
            m_window.draw(gravityGunButton);
            m_window.draw(gravityGunText);
            m_window.draw(laserGunButton);
            m_window.draw(laserGunText);
        }
    }

    void weaponButtonInit() {
        // Base Gun
        baseGunButton.setSize(sf::Vector2f(75.0f, 30.0f));
        baseGunButton.setOrigin(sf::Vector2f(baseGunButton.getGlobalBounds().width / 2.0f, baseGunButton.getGlobalBounds().height / 2.0f));
        baseGunButton.setPosition(150, 160);
        baseGunButton.setFillColor(sf::Color(255, 255, 255, 150));
        baseGunText.setFont(m_textureManager.getFont("cherii"));
        baseGunText.setString("Base Gun");
        baseGunText.setCharacterSize(15);
        baseGunText.setOrigin(sf::Vector2f(baseGunText.getGlobalBounds().width / 2.0f, baseGunText.getGlobalBounds().height / 2.0f));
        baseGunText.setFillColor(sf::Color::Black);
        baseGunText.setPosition(150.0f, 157.5f);
        // Gravity Gun
        gravityGunButton.setSize(sf::Vector2f(100.0f, 30.0f));
        gravityGunButton.setOrigin(sf::Vector2f(gravityGunButton.getGlobalBounds().width / 2.0f, gravityGunButton.getGlobalBounds().height / 2.0f));
        gravityGunButton.setPosition(50.0f, 250.0f);
        gravityGunButton.setFillColor(sf::Color(255, 255, 255, 150));
        gravityGunText.setFont(m_textureManager.getFont("cherii"));
        gravityGunText.setString("Gravity Gun");
        gravityGunText.setCharacterSize(15);
        gravityGunText.setOrigin(sf::Vector2f(gravityGunText.getGlobalBounds().width / 2.0f, gravityGunText.getGlobalBounds().height / 2.0f));
        gravityGunText.setFillColor(sf::Color::Black);
        gravityGunText.setPosition(50.0f, 247.5f);
        // Laser Gun
        laserGunButton.setSize(sf::Vector2f(100.0f, 30.0f));
        laserGunButton.setOrigin(sf::Vector2f(laserGunButton.getGlobalBounds().width / 2.0f, laserGunButton.getGlobalBounds().height / 2.0f));
        laserGunButton.setPosition(250.0f, 250.0f);
        laserGunButton.setFillColor(sf::Color(255, 255, 255, 150));
        laserGunText.setFont(m_textureManager.getFont("cherii"));
        laserGunText.setString("Laser Gun");
        laserGunText.setCharacterSize(15);
        laserGunText.setOrigin(sf::Vector2f(laserGunText.getGlobalBounds().width / 2.0f, laserGunText.getGlobalBounds().height / 2.0f));
        laserGunText.setFillColor(sf::Color::Black);
        laserGunText.setPosition(250.0f, 247.5f);
    }

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::RectangleShape menu;
    sf::Text menuText;
    sf::Font font;
    bool menuVisible;

    // weapon button on Tech Tree Menu
    sf::RectangleShape baseGunButton;
    sf::Text baseGunText;
    sf::RectangleShape gravityGunButton;
    sf::Text gravityGunText;
    sf::RectangleShape laserGunButton;
    sf::Text laserGunText;
};

#endif // !TECHTREE_H