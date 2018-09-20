#include"Xbox360Controller.h";

Xbox360Controller::Xbox360Controller()
{
	m_currentState.A = false;
	m_currentState.B = false;
	m_currentState.X = false;
	m_currentState.Y = false;
	m_currentState.LB = false;
	m_currentState.RB = false;
	m_currentState.LeftThumbStickClick = false;
	m_currentState.RightThumbStickClick = false;
	m_currentState.DpadUp = false;
	m_currentState.DpadDown = false;
	m_currentState.DpadLeft = false;
	m_currentState.DpadRight = false;
	m_currentState.Start = false;
	m_currentState.Back = false;
}

Xbox360Controller::~Xbox360Controller()
{
}

//Text positions and text strings are set inside each button or analog or trigger press
void Xbox360Controller::update()
{
	//making sure a controller is connected 
	if (isConnected())
	{
		connect();
		//mapping for the A button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 0))
		{
			m_currentState.A = true;
		}
		else
		{
			m_currentState.A = false;
		}
		//mapping for the B button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 1))
		{
			m_currentState.B = true;
		}
		else
		{
			m_currentState.B = false;
		}
		//mapping for the X button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 2))
		{
			m_currentState.X = true;
		}
		else
		{
			m_currentState.X = false;
		}
		//mapping for the Y button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 3))
		{
			m_currentState.Y = true;
		}
		else
		{
			m_currentState.Y = false;
		}
		//mapping for the LB button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 4))
		{
			m_currentState.LB = true;
		}
		else
		{
			m_currentState.LB = false;
		}
		//mapping for the RB button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 5))
		{
			m_currentState.RB = true;
		}
		else
		{
			m_currentState.RB = false;
		}
		//mapping for the back button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 6))
		{
			m_currentState.Back = true;
		}
		//mapping for the start button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 7))
		{
			m_currentState.Start = true;
		}
		else
		{
			m_currentState.Start = false;
		}
		//mapping for the left joystick button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 8))
		{
			m_currentState.LeftThumbStickClick = true;
		}
		else
		{
			m_currentState.LeftThumbStickClick = false;
		}
		//mapping for the left joystick button and setting current state to true
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 9))
		{
			m_currentState.RightThumbStickClick = true;
		}
		else
		{
			m_currentState.RightThumbStickClick = false;
		}

		//DPAD SECTION
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) > m_dPadThreshold)
		{
			m_currentState.DpadUp = true;
		}
		else
		{
			m_currentState.DpadUp = false;
		}
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) < -m_dPadThreshold)
		{
			m_currentState.DpadDown = true;
		}
		else
		{
			m_currentState.DpadDown = false;
		}
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) < -m_dPadThreshold)
		{
			m_currentState.DpadLeft = true;
		}
		else
		{
			m_currentState.DpadLeft = false;
		}
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) > m_dPadThreshold)
		{
			m_currentState.DpadRight = true;
		}
		else
		{
			m_currentState.DpadRight = false;
		}

		//Analog Section
		//Left Stick
		m_currentState.LeftThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::X);
		m_currentState.LeftThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Y);
		//Right Stick
		m_currentState.RightThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::R);
		m_currentState.RightThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::U);
		//Left Stick Moved
		//checks to see im the thumbstick position is less or greater than the deadzone which is set at 15 to determine direction. eg a minus numer on x-axis is left.This is the same for the right stick
		if (m_currentState.LeftThumbStick.x > m_analogThreshold || m_currentState.LeftThumbStick.x < -m_analogThreshold || m_currentState.LeftThumbStick.y > m_analogThreshold ||
			m_currentState.LeftThumbStick.y < -m_analogThreshold)
		{
			m_analogMoved[0] = true;
		}
		else
		{
			m_analogMoved[0] = false;
		}
		//Right Stick Moved
		if (m_currentState.RightThumbStick.x > m_analogThreshold || m_currentState.RightThumbStick.x < -m_analogThreshold || m_currentState.RightThumbStick.y > m_analogThreshold ||
			m_currentState.RightThumbStick.y < -m_analogThreshold)
		{
			m_analogMoved[1] = true;
		}
		else
		{
			m_analogMoved[1] = false;
		}

		//Trigger Section
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) < 0)
		{
			m_currentState.RTrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) * -1.0f;
			m_currentState.LTrigger = 0;
		}
		else if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) > 0)
		{
			m_currentState.LTrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z);
			m_currentState.RTrigger = 0;
		}
		if ((sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) == -0.001526 && sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) > 0) ||
			(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) >= -0.001526 && sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) < 0))
		{
			m_currentState.LTrigger = 0;
			m_currentState.RTrigger = 0;
		}
		//Left Trigger
		if (m_currentState.LTrigger > 0)
		{
			m_triggerPressed[0] = true;
		}
		else
		{
			m_triggerPressed[0] = false;
		}
		//Right Trigger
		if (m_currentState.RTrigger > 0)
		{
			m_triggerPressed[1] = true;
		}
		else
		{
			m_triggerPressed[1] = false;
		}
		/*m_previousState = m_currentState;*/
	}
}

//checks if controller is connected
bool Xbox360Controller::isConnected()
{
	if (sf::Joystick::isConnected(0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//sets the joystick index for multiple controller support
bool Xbox360Controller::connect()
{
	for (int i = 0; i < 8; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			if (i == 0)
			{
				sf_Joystick_index = i;
			}
			else
			{
				sf_Joystick_index = i - 1;
			}
			return true;
		}
		else
		{
			false;
		}
	}
}