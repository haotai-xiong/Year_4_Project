#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	m_weather(m_window),
	m_techTreeMenu(m_window),
	m_tutorialTechTreeMenu(m_window),
	m_gameState(Game::State::Menu)
{
	startMenuInit();
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
			if (m_gameState == Game::State::Game) {
				saveGameDataToFile();
			}
			m_exitGame = true;
		}
		// user pressed a key
		if (sf::Event::KeyPressed == newEvent.type) {
			processKeys(newEvent);
		}
		// game state
		if (m_gameState == Game::State::Game) {
			m_uiPanel.processEvent(newEvent, m_window, m_testMap, enemies, workers);
			m_techTreeMenu.update(newEvent, m_player);
			m_player.processEvent(newEvent);
		}
		else if (m_gameState == Game::State::Tutorial) {
			m_tutorialUIPanel.processEvent(newEvent, m_window, m_testMap, enemies, workers);
			m_tutorialTechTreeMenu.update(newEvent, m_player);
			m_tutorialPlayer.processEvent(newEvent);
			m_tutorialUI.update(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event) {
	if (sf::Keyboard::Escape == t_event.key.code) {
		if (m_gameState == Game::State::Game) {
			saveGameDataToFile();
		}
		m_exitGame = true;
	}
	else if (sf::Keyboard::C == t_event.key.code) {
		++eventState;
		m_eventText.show();
	}
	else if (sf::Keyboard::R == t_event.key.code && m_gameState == Game::State::Game) {
		std::filesystem::remove(m_fileName);
		saveGameData(m_player);
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
	case State::Tutorial:
		TutorialUpdate(t_deltaTime);
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
	case State::Tutorial:
		TutorialRender();
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
	if (m_clock.getElapsedTime().asSeconds() >= summonInterval && m_gameState == Game::State::Game) {
		int enemyNumber = wasteAmount / 50;
		//enemyNumber = 1; // test
		for (int i = 0; i < enemyNumber; i++) {
			enemies.push_back(std::make_unique<Enemy>());
		}
		m_clock.restart();
	}
	else if (m_clock.getElapsedTime().asSeconds() >= 10.0f && m_gameState == Game::State::Tutorial) {
		int enemyNumber = 1; // test
		for (int i = 0; i < enemyNumber; i++) {
			m_tutorialEnemies.push_back(std::make_unique<Enemy>());
		}
		m_clock.restart();
	}
}

void Game::MenuUpdate(sf::Time t_deltaTime)
{
	m_startMenu.update(m_window, t_deltaTime);
}

void Game::MenuRender()
{
	m_startMenu.render(m_window);
}

void Game::GameUpdate(sf::Time t_deltaTime)
{
	if (fileExists() && !m_dataLoaded) {
		m_dataLoaded = true;
		m_currentData = loadSavedData();
		m_player.setPosition(m_currentData.playerPos);
		for (int i = 0; i < m_currentData.buildings_size; i++) {
			if (m_currentData.buildings_type[i] == "Factory") {
				m_testMap.addBuilding<Factory>(m_currentData.buildings_pos[i], stringToTileType(m_currentData.buildings_type[i]), m_currentData.buildings_texture[i]);
				workers.push_back(std::make_unique<Worker>());
			}
			else if (m_currentData.buildings_type[i] == "Tower") {
				m_testMap.addBuilding<Tower>(m_currentData.buildings_pos[i], stringToTileType(m_currentData.buildings_type[i]), m_currentData.buildings_texture[i]);
			}
		}
	}

	m_player.update(t_deltaTime);
	m_uiPanel.update(m_window);
	m_testMap.update(m_weather);
	for (auto& enemy : enemies) {
		enemy->update(m_testMap.getBuildings(), m_testMap, m_weather, m_player.getHealth());
		m_player.weaponInteration(enemy.get());
	}
	for (auto& worker : workers) {
		worker->update(t_deltaTime, m_testMap.getBuildings(), m_testMap);
	}
	m_player.weaponUpdate(t_deltaTime);
	summonEnemy();
	m_weather.update(t_deltaTime);
	m_eventText.update();

	if (m_exitGame) {
		m_window.close();
	}
}

void Game::GameRender() {
	m_testMap.render(m_window);
	for (auto& enemy : enemies) {
		enemy->render(m_window);
	}
	for (auto& worker : workers) {
		worker->render(m_window);
	}
	m_uiPanel.render(m_window);
	m_weather.render();
	m_player.render(m_window);
	m_player.weaponRender(m_window);
	m_techTreeMenu.render();
	m_eventText.render(m_window);
}

void Game::TutorialUpdate(sf::Time t_deltaTime) {
	if (m_tutorialUI.getGoToMainGame())
	{
		m_gameState = Game::State::Game;
		m_testMap.buildingInit();
		workers.clear();
	}

	m_tutorialPlayer.update(t_deltaTime);
	m_tutorialUIPanel.update(m_window);
	m_testMap.update(m_weather);
	for (auto& enemy : m_tutorialEnemies) {
		enemy->update(m_testMap.getBuildings(), m_testMap, m_weather, m_player.getHealth());
		m_tutorialPlayer.weaponInteration(enemy.get());
	}
	for (auto& worker : workers) {
		worker->update(t_deltaTime, m_testMap.getBuildings(), m_testMap);
	}
	m_tutorialPlayer.weaponUpdate(t_deltaTime);
	summonEnemy();
	m_weather.update(t_deltaTime);
	m_eventText.update();

	if (m_exitGame) {
		m_window.close();
	}
}

void Game::TutorialRender() {
	m_testMap.render(m_window);
	for (auto& enemy : m_tutorialEnemies) {
		enemy->render(m_window);
	}
	for (auto& worker : workers) {
		worker->render(m_window);
	}
	m_tutorialUIPanel.render(m_window);
	m_weather.render();
	m_tutorialPlayer.render(m_window);
	m_tutorialPlayer.weaponRender(m_window);
	m_tutorialTechTreeMenu.render();
	m_eventText.render(m_window);
	m_tutorialUI.render(m_window);
}

void Game::startMenuInit() {
	m_startMenu.addItem("play_button", [&]() { m_gameState = Game::State::Tutorial; });
	m_startMenu.addItem("exit_button", [&]() { m_window.close(); });
}

void Game::saveGameData(Player t_player) {
	m_currentData.buildings_pos.clear();
	m_currentData.buildings_type.clear();
	m_currentData.buildings_texture.clear();

	m_currentData.playerPos = t_player.getPos();
	// building save
	m_currentData.buildings_size = m_testMap.getBuildings().size();
	std::cout << m_currentData.buildings_size << std::endl;
	for (int i = 0; i < m_testMap.getBuildings().size(); i++) {
		m_currentData.buildings_pos.push_back(m_testMap.getBuildings().at(i)->pos());
		std::cout << "Saved x: " + std::to_string(m_currentData.buildings_pos[i].x) << std::endl;
		m_currentData.buildings_type.push_back(tileTypeToString(m_testMap.getTile(worldToTileCoordIndex(m_currentData.buildings_pos[i]))->getType()));
		m_currentData.buildings_texture.push_back(m_testMap.getBuildings().at(i)->textureName());
	}
}

void Game::saveGameDataToFile() const {
	std::ofstream file(m_fileName);
	if (file.is_open()) {
		file << "PlayerPositionX: " << m_currentData.playerPos.x << std::endl;
		file << "PlayerPositionY: " << m_currentData.playerPos.y << std::endl;
		// building save
		file << "BuildingSize: " << m_currentData.buildings_size << std::endl;
		for (int i = 0; i < m_currentData.buildings_size; i++) {
			file << "buildings_posX" + std::to_string(i) + ": " << m_currentData.buildings_pos[i].x << std::endl;
			file << "buildings_posY" + std::to_string(i) + ": " << m_currentData.buildings_pos[i].y << std::endl;
			file << "buildings_type" + std::to_string(i) + ": " << m_currentData.buildings_type[i] << std::endl;
			file << "buildings_texture" + std::to_string(i) + ": " << m_currentData.buildings_texture[i] << std::endl;
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file for saving." << std::endl;
	}
}

SaveData Game::loadSavedData() {
	std::ifstream file(m_fileName);
	SaveData data;
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key;
			std::getline(iss, key, ':');
			std::string value;
			iss >> std::ws;
			std::getline(iss, value);

			if (key.find("PlayerPositionX") != std::string::npos) {
				data.playerPos.x = std::stof(value);
			}
			else if (key.find("PlayerPositionY") != std::string::npos) {
				data.playerPos.y = std::stof(value);
			}
			// Buildings
			else {
				auto underscorePos = key.find_last_of("_");
				if (underscorePos != std::string::npos) {
					size_t startIndex = key.find_last_not_of("0123456789") + 1;
					std::string indexStr = key.substr(startIndex);
					int index = std::stoi(indexStr);
					std::string propertyName = key.substr(0, startIndex);

					// Resize vectors if necessary
					if (propertyName.find("buildings_posX") != std::string::npos) {
						if (data.buildings_pos.size() <= index) data.buildings_pos.resize(index + 1);
						data.buildings_pos[index].x = std::stof(value);
					}
					else if (propertyName.find("buildings_posY") != std::string::npos) {
						if (data.buildings_pos.size() <= index) data.buildings_pos.resize(index + 1);
						data.buildings_pos[index].y = std::stof(value);
					}
					else if (propertyName.find("buildings_type") != std::string::npos) {
						if (data.buildings_type.size() <= index) data.buildings_type.resize(index + 1);
						data.buildings_type[index] = value;
					}
					else if (propertyName.find("buildings_texture") != std::string::npos) {
						if (data.buildings_texture.size() <= index) data.buildings_texture.resize(index + 1);
						data.buildings_texture[index] = value;
					}
				}
			}
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file for loading." << std::endl;
	}

	// Update buildings_size based on loaded data
	data.buildings_size = data.buildings_pos.size();

	return data;
}

bool Game::fileExists() {
	std::ifstream file(m_fileName);
	return file.good();
}

std::string Game::tileTypeToString(TileType type) {
	switch (type) {
	case TileType::Traversable: return "Traversable";
	case TileType::NonTraversable: return "NonTraversable";
	case TileType::House: return "House";
	case TileType::Factory: return "Factory";
	case TileType::RecyclingCenter: return "RecyclingCenter";
	case TileType::Landfill: return "Landfill";
	case TileType::Plant: return "Plant";
	case TileType::Wood: return "Wood";
	case TileType::Tower: return "Tower";
	case TileType::Connection: return "Connection";
	}
}

TileType Game::stringToTileType(std::string& t_string) {
	static const std::unordered_map<std::string, TileType> stringToType = {
		{"Traversable", TileType::Traversable},
		{"NonTraversable", TileType::NonTraversable},
		{"House", TileType::House},
		{"Factory", TileType::Factory},
		{"RecyclingCenter", TileType::RecyclingCenter},
		{"Landfill", TileType::Landfill},
		{"Plant", TileType::Plant},
		{"Wood", TileType::Wood},
		{"Tower", TileType::Tower},
		{"Connection", TileType::Connection}
	};

	auto it = stringToType.find(t_string);
	if (it != stringToType.end()) {
		return it->second;
	}
	else {
		std::cerr << "Unknown TileType string: " << t_string << std::endl;
		return TileType::Traversable;
	}
}

void Game::winOrLose() {
	if (m_player.getHealth() <= 0) {
		m_gameState = Game::State::Lose;
	}
	else if (enemyKilled > 1100) {
		m_gameState = Game::State::Win;
	}
}