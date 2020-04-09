#include "Window.h"

Window::Window()
: m_isOpen (true)
, m_isFullscreen (false)
{
	setup({640u, 480u}, "Window");
}

Window::Window(sf::Vector2u size, const std::string& name)
: m_isOpen (true)
, m_isFullscreen (false)
{
	setup(size, name);
}

Window::~Window()
{
	destroy();
}

void Window::beginDraw()
{
	m_window.clear();
}

void Window::draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::endDraw()
{
	m_window.display();
}

void Window::processEvents()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
	{
		m_eventManager.handleEvent(event);
	}
}

void Window::update()
{
	m_eventManager.update();
}

/***********
 * Getters *
 **********/

bool Window::isOpen() const
{
	return m_isOpen;
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &m_window;
}

EventManager* Window::getEventManager()
{
	return &m_eventManager;
}

/*******************
 * Private methods *
 ******************/

void Window::setup(sf::Vector2u size, const std::string& name)
{
	m_size = size;
	m_name = name;
	
	m_eventManager.addCallback("Window_close", &Window::close, this);
	m_eventManager.addCallback("Window_close2", &Window::close, this);
	m_eventManager.addCallback("Toggle_fullscreen", &Window::toggleFullscreen, this);
	
	create();
}

void Window::create()
{
	sf::Uint32 style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create(sf::VideoMode (m_size.x, m_size.y), m_name, style);
}

void Window::destroy()
{
	m_window.close();
}

/*****************
 * Event methods *
 ****************/

void Window::close(EventDetails* details)
{
	m_isOpen = false;
}

void Window::toggleFullscreen(EventDetails* details)
{
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}
