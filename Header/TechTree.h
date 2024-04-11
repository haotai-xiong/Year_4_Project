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
        menu.setSize(sf::Vector2f(400, 400));
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
        requirementsInit();
    }

    void update(sf::Event event, Player& t_player) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuVisible = !menuVisible;
                }
                else if (baseGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    t_player.setWeaponLevel(1); // test purpose
                    t_player.setCurrentWeapon(Weapon::Type::baseGun);
                    menuVisible = !menuVisible;
                }
                else if (gravityGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
                    && t_player.getWeaponLevel() == 1) {
                    t_player.setWeaponLevel(2);
                    t_player.setCurrentWeapon(Weapon::Type::gravityGun);
                    menuVisible = !menuVisible;
                }
                else if (laserGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
                    && t_player.getWeaponLevel() == 1) {
                    t_player.setWeaponLevel(2);
                    t_player.setCurrentWeapon(Weapon::Type::laserGun);
                    menuVisible = !menuVisible;
                }
                else if (heavyLaserGunButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
                    && t_player.getWeaponLevel() == 2) {
                        t_player.setWeaponLevel(3);
                    t_player.setCurrentWeapon(Weapon::Type::heavyLaserGun);
                    menuVisible = !menuVisible;
                }
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            if (gravityGunButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                showRequirementWindow = true;
                requirementWindow.setPosition(event.mouseMove.x + 10.0f, event.mouseMove.y + 10.0f);
                woodText.setString("Wood: " + std::to_string(requirements["gravityGun"][0]));
                woodText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 5.0f);
                wasteText.setString("Waste Less Than: " + std::to_string(requirements["gravityGun"][1]));
                wasteText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 25.0f);
                enemyKilledText.setString("Enemy Killed: >" + std::to_string(requirements["gravityGun"][2]));
                enemyKilledText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 45.0f);
                prosperityText.setString("Prosperity: >" + std::to_string(requirements["gravityGun"][3]));
                prosperityText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 65.0f);
            }
            else if (laserGunButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                showRequirementWindow = true;
                requirementWindow.setPosition(event.mouseMove.x + 10.0f, event.mouseMove.y + 10.0f);
                woodText.setString("Wood: " + std::to_string(requirements["laserGun"][0]));
                woodText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 5.0f);
                wasteText.setString("Waste Less Than: " + std::to_string(requirements["laserGun"][1]));
                wasteText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 25.0f);
                enemyKilledText.setString("Enemy Killed: >" + std::to_string(requirements["laserGun"][2]));
                enemyKilledText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 45.0f);
                prosperityText.setString("Prosperity: >" + std::to_string(requirements["laserGun"][3]));
                prosperityText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 65.0f);
            }
            else if (heavyLaserGunButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                showRequirementWindow = true;
                requirementWindow.setPosition(event.mouseMove.x + 10.0f, event.mouseMove.y + 10.0f);
                woodText.setString("Wood: " + std::to_string(requirements["heavyLaserGun"][0]));
                woodText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 5.0f);
                wasteText.setString("Waste Less Than: " + std::to_string(requirements["heavyLaserGun"][1]));
                wasteText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 25.0f);
                enemyKilledText.setString("Enemy Killed: >" + std::to_string(requirements["heavyLaserGun"][2]));
                enemyKilledText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 45.0f);
                prosperityText.setString("Prosperity: >" + std::to_string(requirements["heavyLaserGun"][3]));
                prosperityText.setPosition(requirementWindow.getPosition().x + 5.0f, requirementWindow.getPosition().y + 65.0f);
            }
            else {
                showRequirementWindow = false;
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
            m_window.draw(heavyLaserGunButton);
            m_window.draw(heavyLaserGunText);
            if (showRequirementWindow)
            {
                m_window.draw(requirementWindow);
                m_window.draw(woodText);
                m_window.draw(wasteText);
                m_window.draw(enemyKilledText);
                m_window.draw(prosperityText);
            }
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
        // Heavy Laser Gun
        heavyLaserGunButton.setSize(sf::Vector2f(150.0f, 30.0f));
        heavyLaserGunButton.setOrigin(sf::Vector2f(heavyLaserGunButton.getGlobalBounds().width / 2.0f, heavyLaserGunButton.getGlobalBounds().height / 2.0f));
        heavyLaserGunButton.setPosition(250.0f, 350.0f);
        heavyLaserGunButton.setFillColor(sf::Color(255, 255, 255, 150));
        heavyLaserGunText.setFont(m_textureManager.getFont("cherii"));
        heavyLaserGunText.setString("Heavy Laser Gun");
        heavyLaserGunText.setCharacterSize(15);
        heavyLaserGunText.setOrigin(sf::Vector2f(heavyLaserGunText.getGlobalBounds().width / 2.0f, heavyLaserGunText.getGlobalBounds().height / 2.0f));
        heavyLaserGunText.setFillColor(sf::Color::Black);
        heavyLaserGunText.setPosition(250.0f, 347.5f);
        // requirement text
        requirementWindow.setSize(sf::Vector2f(220.0f, 100.0f));
        requirementWindow.setFillColor(sf::Color(58, 57, 57, 255));
        woodText.setFont(m_textureManager.getFont("cherii"));
        woodText.setCharacterSize(20);
        woodText.setFillColor(sf::Color::Black);
        wasteText.setFont(m_textureManager.getFont("cherii"));
        wasteText.setCharacterSize(20);
        wasteText.setFillColor(sf::Color::Black);
        enemyKilledText.setFont(m_textureManager.getFont("cherii"));
        enemyKilledText.setCharacterSize(20);
        enemyKilledText.setFillColor(sf::Color::Black);
        prosperityText.setFont(m_textureManager.getFont("cherii"));
        prosperityText.setCharacterSize(20);
        prosperityText.setFillColor(sf::Color::Black);
    }

    // requirements init
    void requirementsInit() {
        // gravity gun
        std::vector<int> gravityReq{ 5000, 500, 50, 0 };
        requirements["gravityGun"] = gravityReq;
        // laser gun
        std::vector<int> laserReq{ 3000, 600, 20, 0 };
        requirements["laserGun"] = laserReq;
        // heavy laser gun
        std::vector<int> heavyLaserReq{ 10000, 200, 100, 300 };
        requirements["heavyLaserGun"] = heavyLaserReq;
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
    sf::RectangleShape heavyLaserGunButton;
    sf::Text heavyLaserGunText;

    // small hover-ish requirement values
    bool showRequirementWindow = false;
    sf::RectangleShape requirementWindow;
    sf::Text woodText;
    sf::Text wasteText;
    sf::Text enemyKilledText;
    sf::Text prosperityText;
    std::unordered_map<std::string, std::vector<int>> requirements; // >= wood resource | <= waste amount | >= enemyKilled | >= prosperity
};

#endif // !TECHTREE_H