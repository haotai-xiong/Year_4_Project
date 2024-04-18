#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Enemy.h"
#include <cstdlib>

class Player
{
private:
	// sprite attributes
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_previousPosition;

	// animation attributes
	float m_frameIncrement{ 0.004 };
	float m_frameCounter{ 0 };
	int m_currentXFrame{ 0 };
	int m_currentYFrame{ 0 };

	// gameplay attributes
	sf::RectangleShape m_healthBar;
	int m_health = 100;
	bool m_alive = true;
	bool m_moving = false;
	bool m_shooting = false;
	int m_speed = 4;
	sf::Vector2f m_playerDirection = sf::Vector2f(0.0f, 0.0f);

	// weapon attributes
	Weapon::Type m_currentWeapon;
	BaseGun m_baseGun;
	GravityGun m_gravityGun;
	LaserGun m_laserGun;
	HeavyLaserGun m_heavyLaserGun;
	int m_weaponLevel = 1;

public:
	Player(); // default constructor
	bool& movements();
	void animate();

	void setPosition(sf::Vector2f& t_pos) { m_position = t_pos; };
	sf::Vector2f& getPos() { return m_position; };
	sf::Vector2f& getPreviousPos() { return m_previousPosition; }

	sf::Sprite& getBody();
	void boundDetection();
	void collisionDetection(sf::Sprite& t_wallSprite);
	void wallDectection(sf::RectangleShape& t_area);
	void weaponControl();

	void update(const sf::Time& deltaTime);
	void render(sf::RenderWindow& t_window);
	void processEvent(sf::Event& t_event);
	void indexUpdate();
	void weaponUpdate(const sf::Time& deltaTime);
	void weaponInteration(Enemy* t_enemy);
	void weaponRender(sf::RenderWindow& t_window);

	void setSpeed(int t_speed) { m_speed = t_speed; }
	int& getSpeed() { return m_speed; }
	void setHealth(int& t_health) { m_health = t_health; }
	int& getHealth() { return m_health; }
	void setFrameIncrement(float t_frameIncrement) { m_frameIncrement = t_frameIncrement; }
	float& getFrameIncrement() { return m_frameIncrement; }
	bool& isMoving() { return m_moving; }
	void setCurrentWeapon(Weapon::Type t_weapon) { m_currentWeapon = t_weapon; }
	void setWeaponLevel(int t_level) { m_weaponLevel = t_level; }
	int getWeaponLevel() { return m_weaponLevel; }
};

#endif // !PLAYER_H