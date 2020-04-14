#include "State_MainMenu.h"
#include "StateManager.h"

State_Pause::State_Pause(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Pause::onCreate()
{
	setTransparent(true);
	
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Pause, "Pause", &State_Pause::resume, this);
}

void State_Pause::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Pause, "Pause");
}

void State_Pause::activate() {}
void State_Pause::deactivate() {}

void State_Pause::update(sf::Time) {}
void State_Pause::draw() {}

/*****************
 * Event methods *
 ****************/

void State_Pause::resume(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Platform);
	m_stateManager->remove(StateType::Pause);
}
