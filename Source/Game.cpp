#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	m_weather(m_window),
	m_techTreeMenu(m_window)
{
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen()) {
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents() {
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent)) {
		// window message 
		if ( sf::Event::Closed == newEvent.type) {
			m_exitGame = true;
		}
		// user pressed a key
		if (sf::Event::KeyPressed == newEvent.type) {
			processKeys(newEvent);
		}
		m_uiPanel.processEvent(newEvent, m_window, m_testMap, enemies);
		m_techTreeMenu.update(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event) {
	if (sf::Keyboard::Escape == t_event.key.code) {
		m_exitGame = true;
	}
	else if (sf::Keyboard::C == t_event.key.code) {
		m_weather.switchWeather();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime) {
	m_uiPanel.update(m_window);
	m_testMap.update(m_weather);
	for (auto& enemy : enemies) {
		enemy->update(m_testMap.getBuildings(), m_testMap, m_weather);
	}

	if (m_exitGame) {
		m_window.close();
	}
	summonEnemy();
	m_weather.update(t_deltaTime);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render() {
	m_window.clear(sf::Color::Black);

	m_testMap.render(m_window);
	for (auto& enemy : enemies) {
		enemy->render(m_window);
	}
	m_uiPanel.render(m_window);
	m_weather.render();
	m_techTreeMenu.render();

	m_window.display();
}

void Game::summonEnemy()
{
	if (m_clock.getElapsedTime().asSeconds() >= summonInterval) {
		int enemyNumber = wasteAmount / 50;
		for (int i = 0; i < enemyNumber; i++) {
			enemies.push_back(std::make_unique<Enemy>());
		}
		m_clock.restart();
	}
}