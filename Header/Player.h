#include "Globals.h"
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
	int m_health = 10;
	bool m_alive;
	bool m_moving;
	bool m_mining;
	int m_speed = 4;

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

	void update();
	void render(sf::RenderWindow& t_window);
	void indexUpdate();

	void setSpeed(int t_speed) { m_speed = t_speed; }
	int& getSpeed() { return m_speed; }
	void setHealth(int& t_health) { m_health = t_health; }
	int& getHealth() { return m_health; }
	void setFrameIncrement(float t_frameIncrement) { m_frameIncrement = t_frameIncrement; }
	float& getFrameIncrement() { return m_frameIncrement; }
	bool& isMoving() { return m_moving; }
	bool& isMining() { return m_mining; }
};