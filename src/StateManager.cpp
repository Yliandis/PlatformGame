#include "StateManager.h"

StateManager::StateManager(SharedContext* sharedContext)
: m_context (sharedContext)
{
	registerState<State_Intro>(StateType::Intro);
	registerState<State_MainMenu>(StateType::MainMenu);
	registerState<State_Settings>(StateType::Settings);
	registerState<State_Credits>(StateType::Credits);
	registerState<State_LevelMenu>(StateType::LevelMenu);
	registerState<State_Platform>(StateType::Platform);
	registerState<State_Pause>(StateType::Pause);
}

StateManager::~StateManager()
{
	for (auto& it : m_states)
	{
		it.second->onDestroy();
		delete it.second;
	}
}

void StateManager::update(sf::Time deltaTime)
{
	if (m_states.empty())
	{
		return;
	}
	
	if (m_states.back().second->isTranscendent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		
		while (it != m_states.begin())
		{
			if (it != m_states.end())
			{
				if (!it->second->isTranscendent())
				{
					break;
				}
			}
			--it;
		}
		
		for ( ; it != m_states.end() ; ++it)
		{
			it->second->update(deltaTime);
		}
	}
	else
	{
		m_states.back().second->update(deltaTime);
	}
}

void StateManager::draw()
{
	if (m_states.empty())
	{
		return;
	}
	
	if (m_states.back().second->isTransparent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		
		while (it != m_states.begin())
		{
			if (it != m_states.end())
			{
				if (!it->second->isTransparent())
				{
					break;
				}
			}
			--it;
		}
		
		for ( ; it != m_states.end() ; ++it)
		{
			it->second->draw();
		}
	}
	else
	{
		m_states.back().second->draw();
	}
}

void StateManager::processRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		removeState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void StateManager::switchTo(StateType type)
{
	m_context->m_eventManager->setCurrentState(type);
	
	for (auto it = m_states.begin() ; it != m_states.end() ; ++it)
	{
		if (it->first == type)
		{
			m_states.back().second->deactivate();
			StateType tempType = it->first;
			BaseState* tempState = it->second;
			m_states.erase(it);
			m_states.emplace_back(tempType, tempState);
			tempState->activate();
			
			return;
		}
	}
	
	// State with type wasn't found
	if (!m_states.empty())
	{
		m_states.back().second->deactivate();
	}
	createState(type);
	m_states.back().second->activate();
}

void StateManager::remove(StateType type)
{
	m_toRemove.push_back(type);
}

bool StateManager::hasState(StateType type) const
{
	for (auto it = m_states.begin() ; it != m_states.end() ; ++it)
	{
		if (it->first == type)
		{
			auto found = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (found == m_toRemove.end())
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

SharedContext* StateManager::getContext()
{
	return m_context;
}

/*******************
 * Private methods *
 ******************/

void StateManager::createState(StateType type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end())
	{
		return;
	}
	
	BaseState* state = newState->second();
	m_states.emplace_back(type, state);
	state->onCreate();
}

void StateManager::removeState(StateType type)
{
	for (auto it = m_states.begin() ; it != m_states.end() ; ++it)
	{
		if (it->first == type)
		{
			it->second->onDestroy();
			delete it->second;
			m_states.erase(it);
			
			return;
		}
	}
}
