#ifndef STATEPAUSE_H
#define STATEPAUSE_H

#include "BaseState.h"
#include "EventManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

class State_Pause : public BaseState
{
	public:
		
		State_Pause(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void resume(EventDetails*);
		
	private:
		
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Font m_font;
		sf::Text m_text;
		
		sf::View m_view;
};

#endif // STATEPAUSE_H
