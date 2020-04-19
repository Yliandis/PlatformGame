#include "State_Platform.h"
#include "StateManager.h"

State_Platform::State_Platform(StateManager* stateManager)
: BaseState (stateManager)
, m_board ()
, m_player (150.f, 150.f)
{ }

void State_Platform::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Platform, "Pause", &State_Platform::pause, this);
	eventManager->addCallback(StateType::Platform, "Back_state", &State_Platform::backToMenu, this);
	
	m_playerTexture.loadFromFile("media/textures/Player.png");
	m_player.setTexture(&m_playerTexture);
	
	// TODO set the position of the player

}

void State_Platform::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Platform, "Pause");
	eventManager->removeCallback(StateType::Platform, "Back_state");
}

void State_Platform::activate()
{
	m_board.loadFromFile("media/config/levels/Test.save");
}

void State_Platform::deactivate() {}

void State_Platform::update(sf::Time deltaTime)
{
	m_player.update(deltaTime);
	
	sf::Vector2f direction;
	for (auto collider : m_board.getColliders())
	{
		if (m_player.getCollider().checkCollision(collider, direction, 0.f))
		{
			m_player.onCollision(direction);
		}
	}
}

void State_Platform::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->draw(m_board);
	window->draw(m_player);
}

/*****************
 * Event methods *
 ****************/

void State_Platform::backToMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::LevelMenu);
}

void State_Platform::pause(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Pause);
}
