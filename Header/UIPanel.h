#ifndef UIPANEL_H
#define UIPANEL_H

#include "TileMap.h"

class UIPanel {
public:
    enum class BuildingOption {
        None,
        House,
        Factory,
        Middle,
        Middle2,
        TopLeft,
        TopRight,
        BotLeft,
        BotRight
    } selectedOption = BuildingOption::None;

    struct ButtonData {
        std::string m_textureName;
        sf::Vector2f m_positionOffset;
        BuildingOption m_option;
    };

    UIPanel(float t_width = 200.0f, float t_height = 500.0f, sf::Vector2f t_screenSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
        : width(t_width), height(t_height), screenSize(t_screenSize), m_hovered(false) {
        panelShape.setSize(sf::Vector2f(width, height));
        panelShape.setFillColor(sf::Color(100, 100, 100, 200)); // Semi-transparent
        panelShape.setPosition(sf::Vector2f(screenSize.x - t_width / 10.0f, screenSize.y - height));

        buttonSetup();
    }

    void update(const sf::RenderWindow& t_window);
    void render(sf::RenderWindow& t_window);
    void processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map);

    void handleMouseClick(const sf::Vector2f& mousePos);
    BuildingOption getSelectedOption() const { return selectedOption; }
    void resetSelection() { selectedOption = BuildingOption::None; }
    bool hovered() const { return m_hovered; }

private:
    
    void buttonSetup();

    float width;
    float height;
    float UI_SHRINK_WIDTH = 5.0f;
    sf::Vector2f screenSize;
    sf::RectangleShape panelShape;
    bool m_hovered;

    std::unordered_map<BuildingOption, sf::RectangleShape> buttons;

    std::vector<ButtonData> buttonConfigs = {
        {"house", sf::Vector2f(10.0f, 20.0f), BuildingOption::House},
        {"factory", sf::Vector2f(10.0f, 70.0f), BuildingOption::Factory},
        {"middle", sf::Vector2f(10.0f, 120.0f), BuildingOption::Middle},
        {"middle2", sf::Vector2f(60.0f, 120.0f), BuildingOption::Middle2},
        {"top left", sf::Vector2f(10.0f, 170.0f), BuildingOption::TopLeft},
        {"top right", sf::Vector2f(60.0f, 170.0f), BuildingOption::TopRight},
        {"bottom left", sf::Vector2f(10.0f, 220.0f), BuildingOption::BotLeft},
        {"bottom right", sf::Vector2f(60.0f, 220.0f), BuildingOption::BotRight}

    };
};

#endif // !UIPANEL_H