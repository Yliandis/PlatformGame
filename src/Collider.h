#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>

class Collider
{
	public:
		
		Collider(sf::RectangleShape*);
		
		void move(float dx, float dy);
		
		bool checkCollision(Collider&, float push);
		
		sf::Vector2f getCenter() const;
		sf::Vector2f getHalfSize() const;
		
	private:
		
		sf::RectangleShape* m_body;
};

#endif // COLLIDER_H
