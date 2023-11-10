#ifndef UIPANEL_H
#define UIPANEL_H

#include "Globals.h"

class UIPanel {
public:

    enum class BuildingOption {
        None,
        House,
        Factory
    } selectedOption = BuildingOption::None;

    UIPanel(float t_width = 200.0f, float t_height = 500.0f, sf::Vector2f t_screenSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
        : width(t_width), height(t_height), screenSize(t_screenSize), hovered(false) {
        panelShape.setSize(sf::Vector2f(width, height));
        panelShape.setFillColor(sf::Color(100, 100, 100, 200)); // Semi-transparent
        panelShape.setPosition(sf::Vector2f(screenSize.x - t_width / 10.0f, screenSize.y - height));

        // Set up the house button
        houseButton.setSize(sf::Vector2f(width / 4.0f , TILE_SIZE));
        houseButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 20));
        houseButton.setTexture(&m_textureManager.getTexture("house"));

        // Set up the factory button
        factoryButton.setSize(sf::Vector2f(width / 4.0f, TILE_SIZE));
        factoryButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 70));
        factoryButton.setTexture(&m_textureManager.getTexture("factory"));
    }

    void update(const sf::RenderWindow& window) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        hovered = panelShape.getGlobalBounds().contains(mousePos);
        float targetX = isHovered() ? screenSize.x - width : screenSize.x - width / 10.0f;
        float panelX = panelShape.getPosition().x;
        float speed = 10.0f;
        panelX += (targetX - panelX) / speed;

        panelShape.setPosition(sf::Vector2f(panelX, screenSize.y - height));
        houseButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 20)));
        factoryButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 70)));
    }

    void render(sf::RenderWindow& t_window) {
        t_window.draw(panelShape);
        t_window.draw(houseButton);
        t_window.draw(factoryButton);
    }

    bool isHovered() const {
        return hovered;
    }
    
    void handleMouseClick(const sf::Vector2f& mousePos) {
        if (houseButton.getGlobalBounds().contains(mousePos)) {
            selectedOption = BuildingOption::House;
        }
        else if (factoryButton.getGlobalBounds().contains(mousePos)) {
            selectedOption = BuildingOption::Factory;
        }
    }

    BuildingOption getSelectedOption() const {
        return selectedOption;
    }

    void resetSelection() {
        selectedOption = BuildingOption::None;
    }

    void processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map) {
        if (sf::Event::MouseButtonPressed == t_event.type) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
            if (isHovered()) {
                handleMouseClick(mousePos);
            }
            else {
                auto selectedOption = getSelectedOption();
                if (selectedOption != UIPanel::BuildingOption::None) {
                    sf::Vector2f worldPos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
                    if (selectedOption == UIPanel::BuildingOption::House) {
                        t_map.addHouse(worldPos);
                    }
                    else if (selectedOption == UIPanel::BuildingOption::Factory) {
                        t_map.addFactory(worldPos);
                    }
                    // Reset the selection after placing a building
                    resetSelection();
                }
            }
        }
    }

private:

    float width;
    float height;
    sf::Vector2f screenSize;
    sf::RectangleShape panelShape;
    bool hovered;

    sf::RectangleShape houseButton;
    sf::RectangleShape factoryButton;
};

#endif // !UIPANEL_H