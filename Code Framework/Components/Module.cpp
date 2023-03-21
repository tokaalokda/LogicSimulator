#include "Module.h"

Module::Module(GraphicsInfo* r_pGfxInfo, int r_FanOut) :Gate(r_pGfxInfo, 5, r_FanOut)
{
	ComponentType = T_Module;
	
}

int Module::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int Module::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

 void Module::Operate()
{
	 int place; 
	 for (int i=0; i < pManager ->CompCount; i++){
	 	 if (m_pGfxInfo->PointsList[0].x== pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && m_pGfxInfo->PointsList[1].x == pManager->CompList[i]->m_pGfxInfo->PointsList[1].x)
			 place = i;
	 } 


	 m_OutputPin->setStatus(pManager->CompList[place - 36 - 30]->m_OutputPin->getStatus());
	 pManager->CompList[place - 36 - 29]->m_InputPins[0].setStatus(m_InputPins[0].getStatus());
	 pManager->CompList[place - 36 - 27]->m_InputPins[0].setStatus(m_InputPins[1].getStatus());
	 pManager->CompList[place - 36 - 25]->m_InputPins[0].setStatus(m_InputPins[2].getStatus());
	 pManager->CompList[place - 36 - 23]->m_InputPins[0].setStatus(m_InputPins[3].getStatus());
	 pManager->CompList[place - 36 - 21]->m_InputPins[0].setStatus(m_InputPins[4].getStatus());

	 	
}


// Function Draw
void Module::Draw(UI* pUI)
{
	//Call output class and pass gate drawing info to it.
	pUI->DrawModule(*m_pGfxInfo, selected); 
}



//Set status of an input pin ot HIGH or LOW
void Module::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}