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
        TopLeft,
        TopRight,
        BotLeft,
        BotRight
    } selectedOption = BuildingOption::None;

    UIPanel(float t_width = 200.0f, float t_height = 500.0f, sf::Vector2f t_screenSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
        : width(t_width), height(t_height), screenSize(t_screenSize), m_hovered(false) {
        panelShape.setSize(sf::Vector2f(width, height));
        panelShape.setFillColor(sf::Color(100, 100, 100, 200)); // Semi-transparent
        panelShape.setPosition(sf::Vector2f(screenSize.x - t_width / 10.0f, screenSize.y - height));

        houseButtonSetup();
        factoryButtonSetup();
        connectionButtonSetup();
    }

    void update(const sf::RenderWindow& t_window);
    void render(sf::RenderWindow& t_window);
    void processEvent(sf::Event& t_event, sf::RenderWindow& t_window, TileMap& t_map);

    void handleMouseClick(const sf::Vector2f& mousePos);
    BuildingOption getSelectedOption() const { return selectedOption; }
    void resetSelection() { selectedOption = BuildingOption::None; }
    bool hovered() const { return m_hovered; }

private:
    
    void houseButtonSetup();
    void factoryButtonSetup();
    void connectionButtonSetup();

    float width;
    float height;
    float UI_SHRINK_WIDTH = 5.0f;
    sf::Vector2f screenSize;
    sf::RectangleShape panelShape;
    bool m_hovered;

    sf::RectangleShape houseButton;
    sf::RectangleShape factoryButton;
    sf::RectangleShape midConnectionButton;
    sf::RectangleShape topLeftConnectionButton;
    sf::RectangleShape topRightConnectionButton;
    sf::RectangleShape bottomLeftConnectionButton;
    sf::RectangleShape bottomRightConnectionButton;
};

#endif // !UIPANEL_H