#ifndef GAME_H
#define GAME_H

#include "UIPanel.h"
#include "Enemy.h"

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

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	TileMap m_testMap;
	UIPanel m_uiPanel;
	Enemy m_testEnemy[1];
};

#endif // !GAME_HPP

