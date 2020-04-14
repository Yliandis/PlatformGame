#include "State_Platform.h"
#include "StateManager.h"

State_Platform::State_Platform(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Platform::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Platform, "Pause", &State_Platform::pause, this);
	eventManager->addCallback(StateType::Platform, "Back_state", &State_Platform::backToMenu, this);
}

void State_Platform::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Platform, "Pause");
	eventManager->removeCallback(StateType::Platform, "Back_state");
}

void State_Platform::activate() {}
void State_Platform::deactivate() {}

void State_Platform::update(sf::Time) {}
void State_Platform::draw() {}

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
