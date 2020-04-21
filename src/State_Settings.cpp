#include "State_Settings.h"
#include "StateManager.h"

State_Settings::State_Settings(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Settings::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Settings, "Back_state", &State_Settings::backToMenu, this);
}

void State_Settings::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Settings, "Back_state");
}

void State_Settings::activate() {}

void State_Settings::deactivate() {}

void State_Settings::update(sf::Time) {}
void State_Settings::draw() {}

/*****************
 * Event methods *
 ****************/

void State_Settings::backToMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::MainMenu);
	m_stateManager->remove(StateType::Settings);
}
