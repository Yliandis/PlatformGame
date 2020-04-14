#ifndef STATESETTINGS_H
#define STATESETTINGS_H

#include "BaseState.h"
#include "EventManager.h"

class State_Settings : public BaseState
{
	public:
		
		State_Settings(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void backToMenu(EventDetails*);
};

#endif // STATESETTINGS_H
