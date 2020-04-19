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
		
		Collider(sf::RectangleShape& rect, Style style = Style::Together)
		: m_bodies {&rect}
		, m_style (style)
		{ }
		
		template <class It>
		Collider(It first, It last, Style style = Style::Together)
		: m_style (style)
		{
			setBodies(first, last);
		}
		
		template <class It>
		void setBodies(It first, It last)
		{
			for (auto it = first ; it != last ; ++it)
			{
				m_bodies.push_back(&*it);
			}
		}
		
		void clean();
		
		bool checkCollision(Collider&, sf::Vector2f& direction, float push);
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
