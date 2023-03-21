#include "ModuleB.h"

ModuleB::ModuleB(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 5, r_FanOut)
{
	ComponentType = T_ModuleB;
	m_OutputPin->setStatus(LOW); 
	m_InputPins[0].setStatus(LOW); 
	m_InputPins[1].setStatus(LOW); 
	m_InputPins[2].setStatus(LOW); 
	m_InputPins[3].setStatus(LOW); 
	m_InputPins[4].setStatus(LOW); 

}


// Function Draw
void ModuleB::Draw(UI* pUI)
{
}




void ModuleB::Operate()
{
	int place;
	for (int i = 0; i < pManager->CompCount; i++) {
		if (m_pGfxInfo->PointsList[0].x == pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && m_pGfxInfo->PointsList[1].x == pManager->CompList[i]->m_pGfxInfo->PointsList[1].x)
			place = i;
	}


	m_OutputPin->setStatus(pManager->CompList[place - 20 - 1]->m_OutputPin->getStatus());
	pManager->CompList[place - 36 - 1]->m_InputPins[0].setStatus(pManager->CompList[place - 1]->m_InputPins[0].getStatus());
	pManager->CompList[place - 34 - 1]->m_InputPins[0].setStatus(pManager->CompList[place - 1]->m_InputPins[1].getStatus());
	pManager->CompList[place - 32 - 1]->m_InputPins[0].setStatus(pManager->CompList[place - 1]->m_InputPins[2].getStatus());
	pManager->CompList[place - 30 - 1]->m_InputPins[0].setStatus(pManager->CompList[place - 1]->m_InputPins[3].getStatus());
	pManager->CompList[place - 28 - 1]->m_InputPins[0].setStatus(pManager->CompList[place - 1]->m_InputPins[4].getStatus());

	
}

//returns status of outputpin
int ModuleB::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int ModuleB::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void ModuleB::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}