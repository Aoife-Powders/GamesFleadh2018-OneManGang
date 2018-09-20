#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;
};

class Xbox360Controller
{
private:
	//deadzones for analogs and triggers
	const int m_dPadThreshold = 50;
	const int m_analogThreshold = 15;
public:
	//the number of the joystick connected
	int sf_Joystick_index;
	GamePadState m_currentState;
	GamePadState m_previousState;
	//array of bools to see if the analogs or triggers have been pressed
	bool m_analogMoved[2];
	bool m_triggerPressed[2];

	Xbox360Controller();
	~Xbox360Controller();
	void Xbox360Controller::update();
	bool isConnected();
	bool connect();
};
