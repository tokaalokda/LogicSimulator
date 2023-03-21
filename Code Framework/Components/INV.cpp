#include "INV.h"

INV::INV(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	ComponentType = T_NOT;
}


void INV::Operate()
{
	if ((m_InputPins[0].getStatus() == LOW))
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}


// Function Draw
// Draws 2-input AND gate
void INV::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawINV(*m_pGfxInfo, selected);
}

//returns status of outputpin
int INV::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int INV::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void INV::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
