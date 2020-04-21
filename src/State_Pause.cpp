#include "State_MainMenu.h"
#include "StateManager.h"

State_Pause::State_Pause(StateManager* stateManager)
: BaseState (stateManager)
{
	sf::RenderWindow* window = m_stateManager->getContext()->m_window->getRenderWindow();
	
	m_view.reset({0.f, 0.f, float(window->getSize().x), float(window->getSize().y)});
}

void State_Pause::onCreate()
{
	setTransparent(true);
	
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Pause, "Pause", &State_Pause::resume, this);
	
	m_texture.loadFromFile("media/textures/Pause.png");
	m_font.loadFromFile("media/fonts/Seagram.ttf");
	
	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();
	
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2.f, m_texture.getSize().y / 2.f);
	m_sprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString("Pause");
	m_text.setCharacterSize(30);
	
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void State_Pause::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Pause, "Pause");
}

void State_Pause::activate() {}

void State_Pause::deactivate() {}

void State_Pause::update(sf::Time) {}

void State_Pause::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->getRenderWindow()->setView(m_view);
	
	window->draw(m_sprite);
	window->draw(m_text);
}

/*****************
 * Event methods *
 ****************/

void State_Pause::resume(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Platform);
	m_stateManager->remove(StateType::Pause);
}
