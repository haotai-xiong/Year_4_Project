#ifndef GAME_H
#define GAME_H

#include "SaveData.h"

class Game
{

public:

	enum class State {
		Menu,
		Tutorial,
		Game,
		Win,
		Lose
	} m_gameState;

	Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void MenuUpdate(sf::Time t_deltaTime);
	void MenuRender();
	void GameUpdate(sf::Time t_deltaTime);
	void GameRender();

	void startMenuInit();
	void summonEnemy();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	// tutorial game
	Player m_tutorialPlayer;
	TileMap m_tutorialMap;
	UIPanel m_tutorialUIPanel;
	EventUI m_tutorialEventText;
	std::vector<std::unique_ptr<Enemy>> m_tutorialEnemies;
	std::vector<std::unique_ptr<Worker>> m_tutorialWorkers;
	// main game
	TileMap m_testMap;
	UIPanel m_uiPanel;
	EventUI m_eventText;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Worker>> workers;
	Weather m_weather;
	TechTree m_techTreeMenu;
	Player m_player;
	StartMenu m_startMenu;

	sf::Clock m_clock;

	// save system
	SaveData m_currentData;
	bool m_dataLoaded = false;
	std::string m_fileName = "savedData.txt";
	void saveGameData(Player t_player);
	void saveGameDataToFile() const;
	SaveData loadSavedData();
	bool fileExists();


	std::string tileTypeToString(TileType type);
	TileType stringToTileType(std::string& t_string);
};

#endif // !GAME_HPP