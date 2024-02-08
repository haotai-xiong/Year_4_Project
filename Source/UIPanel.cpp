#include "UIPanel.h"

void UIPanel::update(const sf::RenderWindow& t_window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
    m_hovered = panelShape.getGlobalBounds().contains(mousePos);
    float targetX = hovered() ? screenSize.x - width : screenSize.x - width / 10.0f;
    float panelX = panelShape.getPosition().x;
    float m_speed = 10.0f;
    panelX += (targetX - panelX) / m_speed;
    panelShape.setPosition(sf::Vector2f(panelX, screenSize.y - height));

    for (const auto& config : buttonConfigs) {
        auto& button = buttons[config.m_option];
        button.setPosition(panelShape.getPosition() + config.m_positionOffset);

        auto& text = texts[config.m_option];
        text.setPosition(panelShape.getPosition() + config.m_positionOffset + sf::Vector2f(0.0f, 40.0f));
    }

    resourcePanelUpdate();
}

void UIPanel::render(sf::RenderWindow& t_window) {
    t_window.draw(panelShape);

    for (const auto& [option, button] : buttons) {
        t_window.draw(button);
    }

    for (const auto& [option, text] : texts) {
        t_window.draw(text);
    }

    t_window.draw(m_resourcePanel);
    t_window.draw(m_woodText);
    t_window.draw(m_metalText);
    t_window.draw(m_energyText);
    t_window.draw(m_wasteText);
    t_window.draw(m_prosperityText);
}

void UIPanel::processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map, std::vector<std::unique_ptr<Enemy>>& t_enemies) {
    if (sf::Event::MouseButtonPressed == t_event.type) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(t_window));
        if (hovered()) {
            handleMouseClick(mousePos);
        }
        else {
            auto selectedOption = getSelectedOption();
            if (selectedOption != UIPanel::BuildingOption::None) {
                sf::Vector2f worldPos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
                if (selectedOption == UIPanel::BuildingOption::House
                    && woodAmount >= 500) {
                    t_map.addBuilding<House>(worldPos, TileType::House, "house");
                    prosperity += 50;
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
                /*
                for (auto& enemy : t_enemies)
                {
                    enemy->findClosestBuilding(t_map.getBuildings());
                }
                */
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

void UIPanel::resourcePanelSetup(){
    m_resourcePanel.setSize(sf::Vector2f(height + 100.0f, width / 2.0f));
    m_resourcePanel.setFillColor(sf::Color(100, 100, 100, 192));
    // wood text
    m_woodText.setFont(m_textureManager.getFont("cherii"));
    m_woodText.setFillColor(sf::Color::Black);
    m_woodText.setCharacterSize(18.0f);
    m_woodText.setString("Wood Resource: ");
    m_woodText.setPosition(sf::Vector2f(0.0f, 10.0f));
    // metal text
    m_metalText.setFont(m_textureManager.getFont("cherii"));
    m_metalText.setFillColor(sf::Color::Black);
    m_metalText.setCharacterSize(18.0f);
    m_metalText.setString("Metal Resource: ");
    m_metalText.setPosition(sf::Vector2f(0.0f, 60.0f));
    // energy text
    m_energyText.setFont(m_textureManager.getFont("cherii"));
    m_energyText.setFillColor(sf::Color::Black);
    m_energyText.setCharacterSize(18.0f);
    m_energyText.setString("Energy Resource: ");
    m_energyText.setPosition(sf::Vector2f(200.0f, 10.0f));
    // waste text
    m_wasteText.setFont(m_textureManager.getFont("cherii"));
    m_wasteText.setFillColor(sf::Color::Black);
    m_wasteText.setCharacterSize(18.0f);
    m_wasteText.setString("Waste Resource: ");
    m_wasteText.setPosition(sf::Vector2f(200.0f, 60.0f));
    // prosperity text
    m_prosperityText.setFont(m_textureManager.getFont("cherii"));
    m_prosperityText.setFillColor(sf::Color::Black);
    m_prosperityText.setCharacterSize(18.0f);
    m_prosperityText.setString("Prosperity: ");
    m_prosperityText.setPosition(sf::Vector2f(450.0f, 10.0f));
}

void UIPanel::resourcePanelUpdate()
{
    m_woodText.setString("Wood Resource: " + std::to_string(woodAmount));
    m_metalText.setString("Metal Resource: " + std::to_string(metalAmount));
    m_energyText.setString("Energy Resource: " + std::to_string(energyAmount));
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << wasteAmount;
    std::string formattedWasteAmount = stream.str();
    m_wasteText.setString("Waste Resource: " + formattedWasteAmount);
    m_prosperityText.setString("Prosperity: " + std::to_string(prosperity));
}