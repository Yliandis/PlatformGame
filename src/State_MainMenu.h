#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include "BaseState.h"
#include "EventManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class State_MainMenu : public BaseState
{
	public:
		
		State_MainMenu(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void mouseLeft(EventDetails*);
		
	private:
		
		sf::Texture m_backgroundTexture;
		sf::Texture m_titleTexture;
		sf::Texture m_buttonTexture;
		sf::Sprite m_backgroundSprite;
		sf::Sprite m_titleSprite;
		sf::Sprite m_buttonSprite [3];
		
		sf::Font m_font;
		sf::Text m_buttonText [3];
};

#endif // STATEMAINMENU_H
