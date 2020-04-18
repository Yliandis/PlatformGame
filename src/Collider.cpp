#include "Collider.h"

Collider::Collider(sf::RectangleShape* body)
: m_body (body)
{ }

void Collider::move(float dx, float dy)
{
	m_body->move(dx, dy);
}

bool Collider::checkCollision(Collider& other, float push)
{
	sf::Vector2f thisPosition = getCenter();
	sf::Vector2f thisHalfSize = getHalfSize();
	sf::Vector2f otherPosition = other.getCenter();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	
	float intersectX = fabs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
	float intersectY = fabs(deltaY) - (thisHalfSize.y + otherHalfSize.y);
	
	if (intersectX < 0.f && intersectY < 0.f)
	{
		push = std::min(std::max(push, 0.f), 1.f);
		
		if (intersectX > intersectY)
		{
			if (deltaX > 0.f)
			{
				move(intersectX * (1 - push), 0.f);
				other.move(-intersectX * push, 0.f);
			}
			else
			{
				move(-intersectX * (1 - push), 0.f);
				other.move(intersectX * push, 0.f);
			}
		}
		else
		{
			if (deltaY > 0.f)
			{
				move(0.f, intersectY * (1 - push));
				other.move(0.f, -intersectY * push);
			}
			else
			{
				move(0.f, -intersectY * (1 - push));
				other.move(0.f, intersectY * push);
			}
		}
		
		return true;
	}
	
	return false;
}

sf::Vector2f Collider::getCenter() const
{
	return m_body->getPosition() + (getHalfSize() - m_body->getOrigin());
}

sf::Vector2f Collider::getHalfSize() const
{
	return m_body->getSize() / 2.f;
}
