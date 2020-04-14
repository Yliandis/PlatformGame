#ifndef STATEPLATFORM_H
#define STATEPLATFORM_H

#include "BaseState.h"
#include "EventManager.h"

class State_Platform : public BaseState
{
	public:
		
		State_Platform(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void backToMenu(EventDetails*);
		void pause(EventDetails*);
};

#endif // STATEPLATFORM_H
