#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "SharedContext.h"
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Settings.h"
#include "State_Credits.h"
#include "State_LevelMenu.h"
#include "State_Platform.h"
#include "State_Pause.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

enum class StateType
{
	Intro = 1,
	MainMenu,
	Settings,
	Credits,
	LevelMenu,
	Platform,
	Pause
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
	public:
		
		StateManager(SharedContext*);
		~StateManager();
		
		void update(sf::Time);
		void draw();
		
		void processRequests();
		
		void switchTo(StateType);
		void remove(StateType);
		
		bool hasState(StateType) const;
		SharedContext* getContext();
		
	private:
		
		void createState(StateType);
		void removeState(StateType);
		
		template <typename T>
		void registerState(StateType);
		
	private:
		
		SharedContext* m_context;
		StateContainer m_states;
		TypeContainer m_toRemove;
		StateFactory m_stateFactory;
};

template <typename T>
void StateManager::registerState(StateType type)
{
	m_stateFactory[type] = [this]() -> BaseState* { return new T(this); };
}

#endif // STATEMANAGER_H
