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
		
		Player(float speed, float jumpHeight);
		Player(sf::Texture*, float speed, float jumpHeight);
		void setTexture(sf::Texture*);
		
		void update(sf::Time);
		void onCollision(sf::Vector2f);
		
		Collider getCollider();
		
	private:
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		
		sf::RectangleShape m_body;
		Collider m_collider;
		
		float m_speed;
		sf::Vector2f m_velocity;
		
		bool m_canJump;
		float m_jumpHeight;
		
		//sf::RectangleShape m_preHitBox;
};

#endif // PLAYER_H
