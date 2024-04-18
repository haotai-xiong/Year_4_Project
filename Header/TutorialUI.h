#ifndef TUTORIALUI_H
#define TUTORIALUI_H

#include "Globals.h"

class TutorialUI {
public:
    TutorialUI() {
        // text attributes init
        text.setFont(m_textureManager.getFont("cherii"));
        text.setCharacterSize(25.0f);
        text.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 25.0f));
        text.setFillColor(sf::Color::White);

        // button init
        nextInstructionButton.setSize(sf::Vector2f(80.0f, 40.0f));
        nextInstructionButton.setFillColor(sf::Color(255, 255, 255, 150));
        nextInstructionButton.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 65.0f));
        goToMainGameButton.setSize(sf::Vector2f(80.0f, 40.0f));
        goToMainGameButton.setFillColor(sf::Color(255, 255, 255, 150));
        goToMainGameButton.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 110.0f));

        // vector string init
        instructions.push_back("1");
        instructions.push_back("2");
        instructions.push_back("3");
        instructions.push_back("4");
        instructions.push_back("5");

        // Initialize with default text if needed
        if (!instructions.empty()) {
            text.setString(instructions[currentIndex]);
        }
    }

    void render(sf::RenderWindow& t_window) const {
        t_window.draw(text);
        t_window.draw(nextInstructionButton);
        t_window.draw(goToMainGameButton);
    }

    void update(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (nextInstructionButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    nextInstruction();
                }
                else if (goToMainGameButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    goToMainGame = true;
                }
            }
        }
    }

    void nextInstruction() {
        if (!instructions.empty()) {
            currentIndex = (currentIndex + 1) % instructions.size();
            text.setString(instructions[currentIndex]);
        }
    }

    bool& getGoToMainGame() { return goToMainGame; }

private:
    sf::Font font;
    sf::Text text;
    std::vector<std::string> instructions;
    size_t currentIndex = 0;

    sf::RectangleShape nextInstructionButton;
    sf::RectangleShape goToMainGameButton;
    bool goToMainGame = false;
};

#endif