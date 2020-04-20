#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

enum class Style
{
	Together,
	Separated
};

class Collider
{
	public:
		
		Collider(Style style = Style::Together)
		: m_style (style)
		{ }
		
		Collider(sf::RectangleShape& body, Style style = Style::Together)
		: m_bodies {&body}
		, m_style (style)
		{ }
		
		template <class It>
		Collider(It first, It last, Style style = Style::Together)
		: m_style (style)
		{
			pushBodies(first, last);
		}
		
		void pushBody(sf::RectangleShape& body)
		{
			m_bodies.push_back(&body);
		}
		
		template <class It>
		void pushBodies(It first, It last)
		{
			for (auto it = first ; it != last ; ++it)
			{
				m_bodies.push_back(&*it);
			}
		}
		
		void clean();
		
		bool checkCollision(Collider&, float);
		bool checkCollision(Collider&, sf::Vector2f&, float);
		bool checkCollision(Collider&, std::vector<std::pair<std::size_t, std::size_t>>&, float);
		bool checkCollision(Collider&, sf::Vector2f&, std::vector<std::pair<std::size_t, std::size_t>>&, float);
		
		sf::Vector2f pushCalculate(sf::Vector2f intersect, sf::Vector2f delta);
		
		void setStyle(Style);
		Style getStyle() const;
		
		sf::Vector2f getCenter(std::size_t) const;
		sf::Vector2f getHalfSize(std::size_t) const;
		
	private:
		
		std::vector<sf::RectangleShape*> m_bodies;
		
		Style m_style;
};

#endif // COLLIDER_H
