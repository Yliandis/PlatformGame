#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "BaseState.h"
#include "EventManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class State_Intro : public BaseState
{
	public:
	
		State_Intro(StateManager* stateManager);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void passIntro(EventDetails*);
		
	private:
		
		sf::Texture m_backgroundTexture;
		sf::Texture m_introTexture;
		sf::Sprite m_backgroundSprite;
		sf::Sprite m_introSprite;
		sf::Font m_font;
		sf::Text m_text;
		float m_timePassed;
};

#endif // STATEINTRO_H
