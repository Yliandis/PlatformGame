#include "State_Platform.h"
#include "StateManager.h"

State_Platform::State_Platform(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Platform::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Platform, "Pause", &State_Platform::pause, this);
}

void State_Platform::onDestroy() {}

void State_Platform::activate() {}
void State_Platform::deactivate() {}

void State_Platform::update(sf::Time) {}
void State_Platform::draw() {}

/*****************
 * Event methods *
 ****************/

void State_Platform::pause(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Pause);
}
