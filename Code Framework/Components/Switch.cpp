#include "Switch.h"

Switch::Switch(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	ComponentType = T_SWITCH;
	isON = LOW;
	selected = 1;
	
}


void Switch::Operate()
{
	if ((isON == HIGH))
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}


// Function Draw

void Switch::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawSWITCH(*m_pGfxInfo, selected, isON);
}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{
	return  -1;	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Switch::setInputPinStatus(int n, STATUS s)
{
	isON = s;
}

int Switch::getStatus() {
	return isON;
}
