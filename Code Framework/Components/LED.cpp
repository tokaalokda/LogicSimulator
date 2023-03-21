#include "LED.h"

LED::LED(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	ComponentType = T_LED;
	selected = 1;
	
}


void LED::Operate()
{
	if ((m_InputPins[0].getStatus() == HIGH))
		isON = HIGH;
	else
		isON = LOW;
}


// Function Draw

void LED::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawLED(*m_pGfxInfo, selected, isON);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return  m_InputPins[0].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	isON = s;
}

int LED::getStatus() {
	return isON;
}
