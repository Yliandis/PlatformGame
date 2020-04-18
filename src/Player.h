#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "Collider.h"

class Player : public sf::Drawable
{
	public:
		
		Player(float);
		Player(sf::Texture*, float);
		void setTexture(sf::Texture*);
		
		void update(sf::Time);
		
		Collider getCollider();
		
	private:
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		
		sf::RectangleShape m_body;
		Collider m_collider;
		
		float m_speed;
		sf::Vector2f m_velocity;
};

#endif // PLAYER_H
