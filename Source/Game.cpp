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
	m_techTreeMenu(m_window),
	m_gameState(Game::State::Menu)
{
	startMenuInit();
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
		m_techTreeMenu.update(newEvent, m_player);
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
	switch (m_gameState)
	{
	case State::Menu:
		MenuUpdate(t_deltaTime);
		break;
	case State::Game:
		GameUpdate(t_deltaTime);
		break;
	case State::Win:
		break;
	case State::Lose:
		break;
	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render() {
	m_window.clear(sf::Color::Black);

	switch (m_gameState)
	{
	case State::Menu:
		MenuRender();
		break;
	case State::Game:
		GameRender();
		break;
	case State::Win:
		break;
	case State::Lose:
		break;
	default:
		break;
	}

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

void Game::MenuUpdate(sf::Time t_deltaTime)
{
	m_startMenu.update(m_window);
}

void Game::MenuRender()
{
	m_startMenu.render(m_window);
}

void Game::GameUpdate(sf::Time t_deltaTime)
{
	m_player.update(t_deltaTime);
	m_uiPanel.update(m_window);
	m_testMap.update(m_weather);
	for (auto& enemy : enemies) {
		enemy->update(m_testMap.getBuildings(), m_testMap, m_weather);
		m_player.weaponInteration(enemy.get());
	}
	m_player.weaponUpdate(t_deltaTime);
	summonEnemy();
	m_weather.update(t_deltaTime);

	if (m_exitGame) {
		m_window.close();
	}
}

void Game::GameRender()
{
	m_testMap.render(m_window);
	for (auto& enemy : enemies) {
		enemy->render(m_window);
	}
	m_uiPanel.render(m_window);
	m_weather.render();
	m_player.render(m_window);
	m_player.weaponRender(m_window);
	m_techTreeMenu.render();
}

void Game::startMenuInit()
{
	m_startMenu.addItem("play_button", [&]() { m_gameState = Game::State::Game; });
	m_startMenu.addItem("exit_button", [&]() { m_window.close(); });
}