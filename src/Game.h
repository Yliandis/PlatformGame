#ifndef GAME_H
#define GAME_H

#include "Window.h"

class Game : private sf::NonCopyable
{
	public:
		
		Game();
		void run();
		
	private:
		
		void processEvents();
		void update();
		void render();
	private:
		
		Window m_window;
};

#endif // GAME_H
