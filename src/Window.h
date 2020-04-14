#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

#include "EventManager.h"

class Window : private sf::NonCopyable
{
	public:
		
		Window();
		Window(sf::Vector2u, const std::string&);
		~Window();
		
		void beginDraw();
		void draw(sf::Drawable&);
		void endDraw();
		
		void processEvents();
		void update();
		
		bool isOpen() const;
		
		sf::RenderWindow* getRenderWindow();
		EventManager* getEventManager();
		
	private:
		
		void setup(sf::Vector2u, const std::string&);
		
		void create();
		void destroy();
		
		void close(EventDetails*);
		void toggleFullscreen(EventDetails*);
		
	private:
		
		sf::RenderWindow m_window;
		
		EventManager m_eventManager;
		
		sf::Vector2u m_size;
		std::string m_name;
		
		bool m_isOpen;
		bool m_isFullscreen;
};

#endif // WINDOW_H
