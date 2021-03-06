#include "Player.h"

Player::Player(float speed, float jumpHeight)
: m_body ({48.f, 48.f})
, m_collider(m_body)
, m_speed (speed)
, m_velocity (0.f, 0.f)
, m_canJump (false)
, m_jumpHeight (jumpHeight)
{ }

Player::Player(sf::Texture* texture, float speed, float jumpHeight)
: m_body ({48.f, 48.f})
, m_collider (m_body)
, m_speed (speed)
, m_velocity (0.f, 0.f)
, m_canJump (false)
, m_jumpHeight (jumpHeight)
{
	m_body.setTexture(texture);
}

void Player::setTexture(sf::Texture* texture)
{
	m_body.setTexture(texture);
}

void Player::update(sf::Time deltaTime)
{
	float gravity = 9.81f * 120.f;
	
	m_velocity.x *= 0.2f; // gradual slowdown
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_velocity.x -= m_speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_velocity.x += m_speed;
	
	if (m_canJump && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_velocity.y = -sqrtf(2.f * gravity * m_jumpHeight); // jump impulse
	}
	m_canJump = false;
	
	m_velocity.y += gravity * deltaTime.asSeconds();
	
	m_body.move(m_velocity * deltaTime.asSeconds());
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f) // left collision
	{
		m_velocity.x = 0.f;
	}
	else if (direction.x > 0.f) // right collision
	{
		m_velocity.x = 0.f;
	}
	
	if (direction.y < 0.f) // top collision
	{
		// if coming from bot, stop movement
		if (m_velocity.y < 0.f)
		{
			m_velocity.y = 0.f;
		}
	}
	else if (direction.y > 0.f) // bottom collision
	{
		m_velocity.y = 0.f;
		m_canJump = true;
	}
}

Collider& Player::getCollider()
{
	return m_collider;
}

void Player::setPosition(sf::Vector2f position)
{
	m_body.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
	return m_body.getPosition();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_body, states);
}
