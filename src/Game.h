#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "StateManager.h"

class Game : private sf::NonCopyable
{
	public:
		
		Game();
		void run();
		
	private:
		
		void processEvents();
		void update(sf::Time);
		void render();
		
		void lateUpdate();
		
	private:
		
		Window m_window;
		StateManager m_stateManager;
		
		SharedContext m_context;
};

#endif // GAME_H
