#include "NAND2.h"

NAND2::NAND2(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	ComponentType = T_NAND2;
}


void NAND2::Operate()
{
	//caclulate the output status as the NANDing of the two input pins
	if (!((m_InputPins[0].getStatus() == HIGH) && (m_InputPins[1].getStatus() == HIGH)))
		m_OutputPin->setStatus(HIGH);
	else
		m_OutputPin->setStatus(LOW);
}


// Function Draw
// Draws 2-input NAND gate
void NAND2::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawNAND2(*m_pGfxInfo, selected);
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
