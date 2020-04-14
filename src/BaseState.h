#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/System/Time.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;
	
	public:
		
		BaseState(StateManager* stateManager)
		: m_stateManager(stateManager)
		, m_isTransparent (false)
		, m_isTranscendent (false)
		{ }
		virtual ~BaseState()
		{ }
		
		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;
		
		virtual void activate() = 0;
		virtual void deactivate() = 0;
		
		virtual void update(sf::Time) = 0;
		virtual void draw() = 0;
		
		void setTransparent(bool transparent)
		{
			m_isTransparent = transparent;
		}
		bool isTransparent() const
		{
			return m_isTransparent;
		}
		
		void setTranscendent(bool transcendent)
		{
			m_isTranscendent = transcendent;
		}
		bool isTranscendent() const
		{
			return m_isTranscendent;
		}
		
		StateManager* getStateManager()
		{
			return m_stateManager;
		}
		
	protected:
		
		StateManager* m_stateManager;
		bool m_isTransparent;
		bool m_isTranscendent;
};

#endif // BASESTATE_H
