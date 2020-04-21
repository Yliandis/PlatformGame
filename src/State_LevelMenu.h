#ifndef STATELEVELMENU_H
#define STATELEVELMENU_H

#include "BaseState.h"
#include "EventManager.h"
#include "Graph.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

enum class Level
{
	Egypte,
	Future,
	Steampunk,
	ImperialJapan,
	Cthulhu,
	MiddleAge
};

class State_LevelMenu : public BaseState
{
	public:
		
		State_LevelMenu(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void backToMenu(EventDetails*);
		void mouseClick(EventDetails*);
		
	private:
		
		Graph m_graph;
		
		sf::Texture m_pathTexture;
		sf::Texture m_levelTexture;
		
		sf::View m_view;
};

#endif // STATELEVELMENU_H
