#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "UIPanel.h"
#include "Enemy.h"
#include "Worker.h"
#include "Weather.h"
#include "TechTree.h"
#include "Player.h"
#include "StartMenu.h"
#include <filesystem>
#include "EventUI.h"

struct SaveData {
	sf::Vector2f playerPos;
	int buildings_size;
	std::vector<sf::Vector2f> buildings_pos;
	std::vector<std::string> buildings_type;
	std::vector<std::string> buildings_texture;
};

#endif // SAVEDATA_H