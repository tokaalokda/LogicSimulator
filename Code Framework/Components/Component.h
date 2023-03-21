//#ifndef _COMPONENT_H
//#define _COMPONENT_H
#pragma once

#include "..\Defs.h"
#include "..\UI\UI.h"
#include "..\\Components\InputPin.h"
#include "..//ApplicationManager.h"


class OutputPin;

//Base class for classes Gate, Switch, and LED.

class Component
{
private:

protected:
	

public:

	ApplicationManager* pManager = NULL;
	bool selected = 0;
	bool inModule = 0; 
	Type ComponentType;
	string m_Label= "-";
	GraphicsInfo* m_pGfxInfo;  //The parameters required to draw a component


	//For gates
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin* m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.

	//For switches
	STATUS isON = NCON;

	//For AddConnection and EditCONN
	virtual void setSourcePin(OutputPin* pSrcPin);
	virtual void setDestPin(InputPin* pDstPin);
	virtual OutputPin* getSourcePin();
	virtual InputPin* getDestPin();

	virtual void setPins(ApplicationManager* pManager);





	Component(GraphicsInfo* r_GfxInfo);

	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(UI*) = 0;	//for each component to Draw itself


	virtual int GetOutPinStatus() = 0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s) = 0;	//set status of Inputpin # n, to be used by connection class.


	Component();

	//Destructor must be virtual
	virtual ~Component();



}; 
