#include "UIPanel.h"

void UIPanel::update(const sf::RenderWindow& t_window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
    m_hovered = panelShape.getGlobalBounds().contains(mousePos);
    float targetX = hovered() ? screenSize.x - width : screenSize.x - width / 10.0f;
    float panelX = panelShape.getPosition().x;
    float speed = 10.0f;
    panelX += (targetX - panelX) / speed;

    panelShape.setPosition(sf::Vector2f(panelX, screenSize.y - height));
    houseButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 20)));
    factoryButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 70)));

    midConnectionButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 120)));
    topLeftConnectionButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 170)));
    topRightConnectionButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(60, 170)));
    bottomLeftConnectionButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(10, 220)));
    bottomRightConnectionButton.setPosition(sf::Vector2f(panelShape.getPosition() + sf::Vector2f(60, 220)));
}

void UIPanel::render(sf::RenderWindow& t_window) {
    t_window.draw(panelShape);
    t_window.draw(houseButton);
    t_window.draw(factoryButton);

    t_window.draw(midConnectionButton);
    t_window.draw(topLeftConnectionButton);
    t_window.draw(topRightConnectionButton);
    t_window.draw(bottomLeftConnectionButton);
    t_window.draw(bottomRightConnectionButton);
}

void UIPanel::processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map) {

    if (sf::Event::MouseButtonPressed == t_event.type) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
        if (hovered()) {
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
                else if (selectedOption == UIPanel::BuildingOption::Middle) {
                    t_map.addMidConnection(worldPos);
                }
                else if (selectedOption == UIPanel::BuildingOption::TopLeft) {
                    t_map.addTopLeftConnection(worldPos);
                }
                else if (selectedOption == UIPanel::BuildingOption::TopRight) {
                    t_map.addTopRightConnection(worldPos);
                }
                else if (selectedOption == UIPanel::BuildingOption::BotLeft) {
                    t_map.addBottomLeftConnection(worldPos);
                }
                else if (selectedOption == UIPanel::BuildingOption::BotRight) {
                    t_map.addBottomRightConnection(worldPos);
                }
                // Reset the selection after placing a building
                resetSelection();
            }
        }
    }
}

void UIPanel::handleMouseClick(const sf::Vector2f& mousePos) {
    if (houseButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::House;
    }
    else if (factoryButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::Factory;
    }
    else if (midConnectionButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::Middle;
    }
    else if (topLeftConnectionButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::TopLeft;
    }
    else if (topRightConnectionButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::TopRight;
    }
    else if (bottomLeftConnectionButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::BotLeft;
    }
    else if (bottomRightConnectionButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = BuildingOption::BotRight;
    }
}

void UIPanel::houseButtonSetup() {
    houseButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    houseButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 20));
    houseButton.setTexture(&m_textureManager.getTexture("house"));
}

void UIPanel::factoryButtonSetup() {
    factoryButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    factoryButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 70));
    factoryButton.setTexture(&m_textureManager.getTexture("factory"));
}

void UIPanel::connectionButtonSetup() {
    midConnectionButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    midConnectionButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 120));
    midConnectionButton.setTexture(&m_textureManager.getTexture("middle"));

    topLeftConnectionButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    topLeftConnectionButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 170));
    topLeftConnectionButton.setTexture(&m_textureManager.getTexture("top left"));

    topRightConnectionButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    topRightConnectionButton.setPosition(panelShape.getPosition() + sf::Vector2f(60, 170));
    topRightConnectionButton.setTexture(&m_textureManager.getTexture("top right"));

    bottomLeftConnectionButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    bottomLeftConnectionButton.setPosition(panelShape.getPosition() + sf::Vector2f(10, 220));
    bottomLeftConnectionButton.setTexture(&m_textureManager.getTexture("bottom left"));

    bottomRightConnectionButton.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
    bottomRightConnectionButton.setPosition(panelShape.getPosition() + sf::Vector2f(60, 220));
    bottomRightConnectionButton.setTexture(&m_textureManager.getTexture("bottom right"));
}