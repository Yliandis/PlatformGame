#include "Collider.h"

void Collider::clean()
{
	std::size_t size = m_bodies.size();
	
	for (std::size_t i = 0 ; i < size ; ++i)
	{
		m_bodies.pop_back();
	}
}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push)
{
	/*
	 * Calculating each collision with associated intersections
	 */
	
	std::vector<std::pair<std::size_t, std::size_t>> collidedShapes;
	std::vector<sf::Vector2f> collisionIntersects;
	std::vector<sf::Vector2f> collisionDeltas;
	
	for (std::size_t i = 0 ; i < m_bodies.size() ; ++i)
	{
		for (std::size_t j = 0 ; j < other.m_bodies.size(); ++j)
		{
			sf::Vector2f thisCenter = getCenter(i);
			sf::Vector2f thisHalfSize = getHalfSize(i);
			sf::Vector2f otherCenter = other.getCenter(j);
			sf::Vector2f otherHalfSize = other.getHalfSize(j);
			
			float deltaX = otherCenter.x - thisCenter.x;
			float deltaY = otherCenter.y - thisCenter.y;
			
			float intersectX = fabs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
			float intersectY = fabs(deltaY) - (thisHalfSize.y + otherHalfSize.y);
			
			if (intersectX < 0.f && intersectY < 0.f)
			{
				collidedShapes.emplace_back(i, j);
				collisionIntersects.emplace_back(intersectX, intersectY);
				collisionDeltas.emplace_back(deltaX, deltaY);
			}
		}
	}
	
	bool result = !collidedShapes.empty();
	
	/*
	 * Pushing and calculating collisions
	 * while there's no more
	 */
	
	while (!collidedShapes.empty())
	{
		/*
		 * Choosing which area is the more important to push first
		 */
		
		float maxArea = 0.f;
		std::size_t maxAreaIndex;
		
		for (std::size_t i = 0 ; i < collisionIntersects.size() ; ++i)
		{
			sf::Vector2f intersect = collisionIntersects[i];
			float area = intersect.x * intersect.y;
			
			if (area > maxArea)
			{
				maxArea = area;
				maxAreaIndex = i;
			}
		}
		
		/*
		 * Doing the push for the more important collision
		 */
		
		std::vector<sf::RectangleShape*> thisToPush;
		std::vector<sf::RectangleShape*> otherToPush;
		
		if (getStyle() == Style::Together)
		{
			thisToPush = m_bodies;
		}
		else
		{
			thisToPush.push_back(m_bodies[collidedShapes[maxAreaIndex].first]);
		}
		if (other.getStyle() == Style::Together)
		{
			otherToPush = other.m_bodies;
		}
		else
		{
			otherToPush.push_back(other.m_bodies[collidedShapes[maxAreaIndex].second]);
		}
		
		sf::Vector2f pushValue = pushCalculate(collisionIntersects[maxAreaIndex], collisionDeltas[maxAreaIndex]);
		direction += pushValue;
		
		for (sf::RectangleShape* shape : thisToPush)
		{
			shape->move(pushValue * (1 - push));
		}
		for (sf::RectangleShape* shape : otherToPush)
		{
			shape->move(pushValue * (-push));
		}
		
		/*
		 * Erase this collision from the stack
		 */
		
		collidedShapes.erase(collidedShapes.begin() + maxAreaIndex);
		collisionIntersects.erase(collisionIntersects.begin() + maxAreaIndex);
		collisionDeltas.erase(collisionDeltas.begin() + maxAreaIndex);
		
		/*
		 * Calculating new intersections and deltas
		 * Removing invalidated collisions
		 */
		
		std::vector<std::pair<std::size_t, std::size_t>> toRemove;
		
		for (std::size_t i = 0 ; i < collidedShapes.size() ; ++i)
		{
			std::pair<std::size_t, std::size_t> index = collidedShapes[i];
			
			sf::Vector2f thisCenter = getCenter(index.first);
			sf::Vector2f thisHalfSize = getHalfSize(index.first);
			sf::Vector2f otherCenter = other.getCenter(index.second);
			sf::Vector2f otherHalfSize = other.getHalfSize(index.second);
			
			float deltaX = otherCenter.x - thisCenter.x;
			float deltaY = otherCenter.y - thisCenter.y;
			
			float intersectX = fabs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
			float intersectY = fabs(deltaY) - (thisHalfSize.y + otherHalfSize.y);
			
			if (intersectX < 0.f && intersectY < 0.f)
			{
				collisionIntersects[i] = {intersectX, intersectY};
				collisionDeltas[i] = {deltaX, deltaY};
			}
			else
			{
				toRemove.push_back(index);
			}
		}
		
		for (std::size_t i = toRemove.size() ; i > 0 ; --i)
		{
			auto found = std::find(collidedShapes.begin(), collidedShapes.end(), toRemove[i-1]);
			
			if (found != collidedShapes.end())
			{
				std::size_t removeIndex = found - collidedShapes.begin();
				
				collisionIntersects.erase(collisionIntersects.begin() + removeIndex);
				collisionDeltas.erase(collisionDeltas.begin() + removeIndex);
				
				collidedShapes.erase(found);
			}
		}
	}
	
	return result;
}

sf::Vector2f Collider::pushCalculate(sf::Vector2f intersect, sf::Vector2f delta)
{
	if (intersect.x > intersect.y)
	{
		if (delta.x > 0.f)
		{
			return {intersect.x, 0.f};
		}
		else
		{
			return {-intersect.x, 0.f};
		}
	}
	else if (intersect.y > intersect.x)
	{
		if (delta.y > 0.f)
		{
			return {0.f, intersect.y};
		}
		else
		{
			return {0.f, -intersect.y};
		}
	}
	
	return {0.f, 0.f};
}

void Collider::setStyle(Style style)
{
	m_style = style;
}

Style Collider::getStyle() const
{
	return m_style;
}

sf::Vector2f Collider::getCenter(std::size_t index) const
{
	sf::RectangleShape* piece = m_bodies[index];
	
	return piece->getPosition() + getHalfSize(index) - piece->getOrigin();
}

sf::Vector2f Collider::getHalfSize(std::size_t index) const
{
	return m_bodies[index]->getSize() / 2.f;
}
