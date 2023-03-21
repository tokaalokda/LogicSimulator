#include "XNOR2.h"

XNOR2::XNOR2(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	ComponentType = T_XNOR2;
}


void XNOR2::Operate()
{
	//caclulate the output status as the ORing of the two input pins
	if (m_InputPins[0].getStatus() == m_InputPins[1].getStatus())
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}


// Function Draw
// Draws 2-input AND gate
void XNOR2::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawXNOR2(*m_pGfxInfo, selected);
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
