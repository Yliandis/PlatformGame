#include "Player.h"

Player::Player(float speed)
: m_body ({48.f, 48.f})
, m_collider(&m_body)
, m_speed (speed)
, m_velocity (0.f, 0.f)
{ }

Player::Player(sf::Texture* texture, float speed)
: m_body ({48.f, 48.f})
, m_collider (&m_body)
, m_speed (speed)
, m_velocity (0.f, 0.f)
{
	m_body.setTexture(texture);
}

void Player::setTexture(sf::Texture* texture)
{
	m_body.setTexture(texture);
}

void Player::update(sf::Time deltaTime)
{
	m_velocity = sf::Vector2f (0.f, 0.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_velocity.y -= m_speed * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_velocity.y += m_speed * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_velocity.x -= m_speed * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_velocity.x += m_speed * deltaTime.asSeconds();
	
	m_body.move(m_velocity);
}

Collider Player::getCollider()
{
	return m_collider;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_body, states);
}
