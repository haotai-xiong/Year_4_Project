#ifndef GAME_H
#define GAME_H

#include "UIPanel.h"
#include "Enemy.h"
#include "Weather.h"
#include "TechTree.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void summonEnemy();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	TileMap m_testMap;
	UIPanel m_uiPanel;
	std::vector<std::unique_ptr<Enemy>> enemies;
	Weather m_weather;
	TechTree m_techTreeMenu;
	Player m_player;

	sf::Clock m_clock;
};

#endif // !GAME_HPP