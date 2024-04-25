#ifndef TUTORIALUI_H
#define TUTORIALUI_H

#include "Globals.h"

class TutorialUI {
public:
    TutorialUI() {
        // instruction text attributes init
        text.setFont(m_textureManager.getFont("cherii"));
        text.setCharacterSize(30.0f);
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
        text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
        text.setFillColor(sf::Color::Black);

        // panel init
        instructionPanel.setSize(sf::Vector2f(500.0f, 500.0f));
        instructionPanel.setFillColor(sf::Color(255, 255, 255, 150));
        instructionPanel.setOrigin(sf::Vector2f(instructionPanel.getGlobalBounds().width / 2.0f, instructionPanel.getGlobalBounds().height / 2.0f));
        instructionPanel.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
        // button init
        nextInstructionButton.setSize(sf::Vector2f(120.0f, 40.0f));
        nextInstructionButton.setFillColor(sf::Color(255, 255, 255, 150));
        nextInstructionButton.setOrigin(sf::Vector2f(nextInstructionButton.getGlobalBounds().width / 2.0f, nextInstructionButton.getGlobalBounds().height / 2.0f));
        nextInstructionButton.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 225.0f));
        showInstructionButton.setSize(sf::Vector2f(80.0f, 40.0f));
        showInstructionButton.setFillColor(sf::Color(255, 255, 255, 150));
        showInstructionButton.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 65.0f));
        goToMainGameButton.setSize(sf::Vector2f(80.0f, 40.0f));
        goToMainGameButton.setFillColor(sf::Color(255, 255, 255, 150));
        goToMainGameButton.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 110.0f));
        // button text init
        nextInstructionText.setFont(m_textureManager.getFont("cherii"));
        nextInstructionText.setCharacterSize(15.0f);
        nextInstructionText.setString("Next Instruction");
        nextInstructionText.setOrigin(sf::Vector2f(nextInstructionText.getGlobalBounds().width / 2.0f, nextInstructionText.getGlobalBounds().height / 2.0f));
        nextInstructionText.setPosition(nextInstructionButton.getPosition());
        nextInstructionText.setFillColor(sf::Color::Black);
        showInstructionText.setFont(m_textureManager.getFont("cherii"));
        showInstructionText.setCharacterSize(15.0f);
        showInstructionText.setString("Show\nInstruction");
        showInstructionText.setPosition(showInstructionButton.getPosition());
        showInstructionText.setFillColor(sf::Color::Black);
        goToMainGameText.setFont(m_textureManager.getFont("cherii"));
        goToMainGameText.setCharacterSize(15.0f);
        goToMainGameText.setString("PLAY");
        goToMainGameText.setPosition(goToMainGameButton.getPosition());
        goToMainGameText.setFillColor(sf::Color::Black);

        // vector string init
        instructions.push_back("WELCOME TO MY GAME\nECOSYNTH!\nIN HERE YOU WILL\nEXPERIENCE WITH\nCOOLEST FEATURES EVER!");
        instructions.push_back("THE GOAL IS BUILDING AND\nPROTECTING YOUR\nBUILDINGS AT THE SAME TIME");
        instructions.push_back("Press WASD for movement\nSpace for shooting\nUse Left Mouse Click\nTo interact with UI");
        instructions.push_back("I have several basic menu here");
        instructions.push_back("On the top of the screen is where\nYou find the resource you hold");
        instructions.push_back("On the right top of the screen is\nTECHTREE for weapons\nYou can upgrade the weapon\nWhen you reach the requirements");
        instructions.push_back("On the right of the screen is\nWhere you buy the buildings\nLeft Click to choose\nThen Left click the map to build");

        // Initialize with default text if needed
        if (!instructions.empty()) {
            text.setString(instructions[currentIndex]);
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
        }
    }

    void render(sf::RenderWindow& t_window) const {
        t_window.draw(goToMainGameButton);
        t_window.draw(goToMainGameText);
        t_window.draw(showInstructionButton);
        t_window.draw(showInstructionText);
        if (showInstruction) {
            t_window.draw(instructionPanel);
            t_window.draw(text);
            t_window.draw(nextInstructionButton);
            t_window.draw(nextInstructionText);
        }
    }

    void update(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (showInstructionButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    showInstruction = !showInstruction;
                }
                else if (nextInstructionButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
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
            text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f));
        }
    }

    bool& getGoToMainGame() { return goToMainGame; }

private:
    sf::Font font;
    sf::Text text;
    std::vector<std::string> instructions;
    size_t currentIndex = 0;

    sf::RectangleShape instructionPanel;
    sf::RectangleShape showInstructionButton;
    sf::Text showInstructionText;
    sf::RectangleShape nextInstructionButton;
    sf::Text nextInstructionText;
    sf::RectangleShape goToMainGameButton;
    sf::Text goToMainGameText;
    bool goToMainGame = false;
    bool showInstruction = false;
};

#endif