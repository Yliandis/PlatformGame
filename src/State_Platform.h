#ifndef STATEPLATFORM_H
#define STATEPLATFORM_H

#include "BaseState.h"
#include "EventManager.h"
#include "Board.h"
#include "Player.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

class State_Platform : public BaseState
{
	public:
		
		State_Platform(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
		void loadLevel();
		void updateView();
		
	private:
		
		void backToMenu(EventDetails*);
		void pause(EventDetails*);
		
	private:
		
		Board m_board;
		Player m_player;
		
		sf::Texture m_playerTexture;
		
		std::vector<sf::RectangleShape> m_worldBounds;
		Collider m_worldCollider;
		
		sf::View m_view;
};

#endif // STATEPLATFORM_H
