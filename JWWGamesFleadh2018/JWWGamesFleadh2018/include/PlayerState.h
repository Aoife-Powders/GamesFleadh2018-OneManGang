#ifndef PLAYERSTATE
#define PLAYERSTATE

#include <iostream>
#include <typeinfo>

#include <PlayerAnimation.h>
#include <Xbox360Controller.h>

class PlayerState
{
public:
	virtual void handleInput() {}

	virtual void update() {}

	virtual void idle(PlayerAnimation * t_animation)
	{
		std::cout << "State::Idling" << std::endl;
	}

	virtual void Jumping(PlayerAnimation * t_animation)
	{
		std::cout << "State::jumping" << std::endl;
	}
};
#endif // !PLAYERSTATE