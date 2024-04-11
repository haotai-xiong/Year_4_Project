#include "Player.h"

Player::Player()
{
	// load texture
	if (!m_texture.loadFromFile("../Assets/Project/Character/Player.png"))
	{
		std::cout << "error loading player texture\n";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f,
		m_sprite.getGlobalBounds().height / 2.0f));
	m_position = sf::Vector2f(200.0f, 200.0f);
	m_sprite.setPosition(m_position);

	// weapon init
	setCurrentWeapon(Weapon::Type::baseGun);
}

void Player::update(const sf::Time& deltaTime)
{
	if (movements())
	{
		boundDetection();
	}
	// weaponUpdate(deltaTime);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
	// weaponRender(t_window);
	animate();
}

void Player::processEvent(sf::Event& t_event)
{
	if (t_event.type == sf::Event::KeyPressed && t_event.key.code == sf::Keyboard::Space && Weapon::Type::heavyLaserGun == m_currentWeapon) {
		m_heavyLaserGun.restartChargeClock();
		m_heavyLaserGun.startCharging();
	}
	if (t_event.type == sf::Event::KeyReleased && t_event.key.code == sf::Keyboard::Space && Weapon::Type::heavyLaserGun == m_currentWeapon) {
		m_heavyLaserGun.release(m_position, m_playerDirection);
	}
}

bool& Player::movements()
{
	m_moving = true;
	m_previousPosition = m_position;
	if (!m_laserGun.active() && !m_heavyLaserGun.active()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) // move up
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // move up
		{
			m_currentYFrame = 2;
			m_position.y -= m_speed;
			m_playerDirection = sf::Vector2f(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // move down
		{
			m_currentYFrame = 3;
			m_position.y += m_speed;
			m_playerDirection = sf::Vector2f(0, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // move left
		{
			m_currentYFrame = 1;
			m_position.x -= m_speed;
			m_playerDirection = sf::Vector2f(-1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // move right
		{
			m_currentYFrame = 0;
			m_position.x += m_speed;
			m_playerDirection = sf::Vector2f(1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // shooting
		{
			m_moving = false;
			m_shooting = true;
			weaponControl();
		}
		else
		{
			// reset x frame
			m_currentXFrame = 0;
			m_frameCounter = 0.0f;
			// animate();
			m_moving = false;
			m_shooting = false;
		}
		// animate();
		m_sprite.setPosition(m_position);
	}

	return m_moving;
}

void Player::animate()
{
	if ((m_moving || m_shooting) && !m_laserGun.active())
	{
		m_frameCounter += m_frameIncrement;
		m_currentXFrame = static_cast<int>(m_frameCounter) % 4;
	}
	else if (m_laserGun.active())
	{
		m_currentXFrame = 2;
	}
	m_sprite.setTextureRect(sf::IntRect(m_currentXFrame * TILE_SIZE, m_currentYFrame * TILE_SIZE,
		TILE_SIZE, TILE_SIZE));
}

sf::Sprite& Player::getBody()
{
	return m_sprite;
}

void Player::boundDetection()
{
	if (m_position.x < m_sprite.getGlobalBounds().width / 2.0f) // left bound
	{
		m_position.x = m_sprite.getGlobalBounds().width / 2.0f;
	}
	else if (m_position.x > SCREEN_WIDTH - m_sprite.getGlobalBounds().width / 2.0f) // right bound
	{
		m_position.x = SCREEN_WIDTH - m_sprite.getGlobalBounds().width / 2.0f;
	}
	
	if (m_position.y < m_sprite.getGlobalBounds().height / 2.0f) // top bound
	{
		m_position.y = m_sprite.getGlobalBounds().height / 2.0f;
	}
	else if (m_position.y > SCREEN_HEIGHT - m_sprite.getGlobalBounds().height / 2.0f) // bottom bound
	{
		m_position.y = SCREEN_HEIGHT - m_sprite.getGlobalBounds().height / 2.0f;
	}
}

void Player::collisionDetection(sf::Sprite& t_wallSprite)
{
}

void Player::wallDectection(sf::RectangleShape& t_area)
{
	if (m_sprite.getGlobalBounds().intersects(t_area.getGlobalBounds()))
	{
		m_position = m_previousPosition;
		m_sprite.setPosition(m_position);
	}
}

void Player::indexUpdate()
{
}

void Player::weaponControl()
{
	m_currentXFrame = 3;
	switch (m_currentWeapon)
	{
	case Weapon::Type::baseGun:
		m_baseGun.fire(m_position, m_playerDirection);
		break;
	case Weapon::Type::gravityGun:
		m_gravityGun.fire(m_position, m_playerDirection);
		break;
	case Weapon::Type::laserGun:
		m_laserGun.fire(m_position, m_playerDirection);
		break;
	default:
		break;
	}
}

void Player::weaponUpdate(const sf::Time& deltaTime)
{
	switch (m_currentWeapon)
	{
		case Weapon::Type::baseGun:
			m_baseGun.update(deltaTime);
			break;
		case Weapon::Type::gravityGun:
			m_gravityGun.update(deltaTime);
			break;
		case Weapon::Type::laserGun:
			m_laserGun.update(deltaTime);
			break;
		case Weapon::Type::heavyLaserGun:
			m_heavyLaserGun.update(deltaTime);
			break;
		default:
			break;
	}
}

void Player::weaponInteration(Enemy* t_enemy)
{
	switch (m_currentWeapon)
	{
	case Weapon::Type::baseGun:
		break;
	case Weapon::Type::gravityGun:
		if (m_gravityGun.getShape().getGlobalBounds().intersects(t_enemy->getSprite().getGlobalBounds())) {
			t_enemy->inGravity(m_gravityGun.getPosition(), true);
		}
		break;
	case Weapon::Type::laserGun:
		break;
	default:
		break;
	}
}

void Player::weaponRender(sf::RenderWindow& t_window)
{
	switch (m_currentWeapon)
	{
		case Weapon::Type::baseGun:
			m_baseGun.render(t_window);
			break;
		case Weapon::Type::gravityGun:
			m_gravityGun.render(t_window);
			break;
		case Weapon::Type::laserGun:
			m_laserGun.render(t_window);
			break;
		case Weapon::Type::heavyLaserGun:
			m_heavyLaserGun.render(t_window);
			break;
		default:
			break;
	}
}