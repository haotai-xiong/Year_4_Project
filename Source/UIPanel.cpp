#include "UIPanel.h"

void UIPanel::update(const sf::RenderWindow& t_window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
    m_hovered = panelShape.getGlobalBounds().contains(mousePos);
    float targetX = hovered() ? screenSize.x - width : screenSize.x - width / 10.0f;
    float panelX = panelShape.getPosition().x;
    float speed = 10.0f;
    panelX += (targetX - panelX) / speed;
    panelShape.setPosition(sf::Vector2f(panelX, screenSize.y - height));

    for (const auto& config : buttonConfigs) {
        auto& button = buttons[config.m_option];
        button.setPosition(panelShape.getPosition() + config.m_positionOffset);

        auto& text = texts[config.m_option];
        text.setPosition(panelShape.getPosition() + config.m_positionOffset + sf::Vector2f(0.0f, 40.0f));
    }
}

void UIPanel::render(sf::RenderWindow& t_window) {
    t_window.draw(panelShape);

    for (const auto& [option, button] : buttons) {
        t_window.draw(button);
    }

    for (const auto& [option, text] : texts) {
        t_window.draw(text);
    }
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
                    t_map.addBuilding<House>(worldPos, TileType::House, "house");
                }
                else if (selectedOption == UIPanel::BuildingOption::Factory) {
                    t_map.addBuilding<Factory>(worldPos, TileType::Factory, "factory");
                }
                else if (selectedOption == UIPanel::BuildingOption::RecyclingCenter) {
                    t_map.addBuilding<RecyclingCenter>(worldPos, TileType::RecyclingCenter, "recycling center");
                }
                else if (selectedOption == UIPanel::BuildingOption::Landfill) {
                    t_map.addBuilding<Landfill>(worldPos, TileType::Landfill, "landfill");
                }
                else if (selectedOption == UIPanel::BuildingOption::Plant) {
                    t_map.addBuilding<Plant>(worldPos, TileType::Plant, "plant");
                }
                else if (selectedOption == UIPanel::BuildingOption::Tower) {
                    t_map.addBuilding<Plant>(worldPos, TileType::Tower, "tower");
                }
                t_map.updateWoodConnections();
                // Reset the selection after placing a building
                resetSelection();
            }
        }
    }
}

void UIPanel::handleMouseClick(const sf::Vector2f& mousePos) {
    for (const auto& [option, button] : buttons) {
        if (button.getGlobalBounds().contains(mousePos)) {
            selectedOption = option;
        }
    }
}

void UIPanel::buttonSetup() {
    for (const auto& config : buttonConfigs) {
        sf::RectangleShape button;
        button.setSize(sf::Vector2f(width / UI_SHRINK_WIDTH, TILE_SIZE));
        button.setTexture(&m_textureManager.getTexture(config.m_textureName));
        buttons[config.m_option] = button;

        sf::Text text;
        text.setFont(m_textureManager.getFont("cherii"));
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(15.0f);
        text.setString(config.m_textureName);
        texts[config.m_option] = text;
    }
}