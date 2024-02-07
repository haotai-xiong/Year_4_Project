#ifndef UIPANEL_H
#define UIPANEL_H

#include "Enemy.h"

class UIPanel {
public:
    enum class BuildingOption {
        None,
        House,
        Factory,
        RecyclingCenter,
        Landfill,
        Plant,
        Tower
    } selectedOption = BuildingOption::None;

    struct ButtonData {
        std::string m_textureName;
        sf::Vector2f m_positionOffset;
        BuildingOption m_option;
    };

    UIPanel(float t_width = 200.0f, float t_height = 500.0f, sf::Vector2f t_screenSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
        : width(t_width), height(t_height), screenSize(t_screenSize), m_hovered(false) {
        panelShape.setSize(sf::Vector2f(width, height));
        panelShape.setFillColor(sf::Color(100, 100, 100, 192)); // Semi-transparent
        panelShape.setPosition(sf::Vector2f(screenSize.x - t_width / 10.0f, screenSize.y - height));

        buttonSetup();
        resourcePanelSetup();
    }

    void update(const sf::RenderWindow& t_window);
    void render(sf::RenderWindow& t_window);
    void processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map, Enemy t_enemy[], int t_enemySize);

    void handleMouseClick(const sf::Vector2f& mousePos);
    BuildingOption getSelectedOption() const { return selectedOption; }
    void resetSelection() { selectedOption = BuildingOption::None; }
    bool hovered() const { return m_hovered; }

private:
    
    void buttonSetup();
    void resourcePanelSetup();
    void resourcePanelUpdate();

    float width;
    float height;
    float UI_SHRINK_WIDTH = 5.0f;
    sf::Vector2f screenSize;
    sf::RectangleShape panelShape;
    bool m_hovered;

    std::unordered_map<BuildingOption, sf::RectangleShape> buttons;
    std::unordered_map<BuildingOption, sf::Text> texts;

    std::vector<ButtonData> buttonConfigs = {
        {"house", sf::Vector2f(10.0f, 20.0f), BuildingOption::House},
        {"factory", sf::Vector2f(10.0f, 80.0f), BuildingOption::Factory},
        {"landfill", sf::Vector2f(10.0f, 140.0f), BuildingOption::Landfill},
        {"recycling center", sf::Vector2f(10.0f, 200.0f), BuildingOption::RecyclingCenter},
        {"plant", sf::Vector2f(10.0f, 260.0f), BuildingOption::Plant},
        {"tower", sf::Vector2f(10.0f, 320.0f), BuildingOption::Tower},
    };
    
    // UI Panel for resources and time
    sf::RectangleShape m_resourcePanel;
    sf::Text m_woodText;
    sf::Text m_metalText;
    sf::Text m_energyText;
    sf::Text m_wasteText;
    sf::Text m_prosperityText;
};

#endif // !UIPANEL_H