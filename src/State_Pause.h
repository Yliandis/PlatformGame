#ifndef STATEPAUSE_H
#define STATEPAUSE_H

#include "BaseState.h"
#include "EventManager.h"

class State_Pause : public BaseState
{
	public:
		
		State_Pause(StateManager*);
		
		virtual void onCreate();
		virtual void onDestroy();
		
		virtual void activate();
		virtual void deactivate();
		
		virtual void update(sf::Time);
		virtual void draw();
		
	private:
		
		void resume(EventDetails*);
		
};

#endif // STATEPAUSE_H
