#ifndef STATECREDITS_H
#define STATECREDITS_H

#include "BaseState.h"
#include "EventManager.h"

class State_Credits : public BaseState
{
	public:
		
		State_Credits(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void backToMenu(EventDetails*);
};

#endif // STATECREDITS_H
