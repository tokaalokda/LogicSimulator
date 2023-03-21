#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin

Gate::Gate(GraphicsInfo* pGfxInfo, int r_Inputs, int r_FanOut):Component(pGfxInfo)
{
	//Allocate number of input pins (equals r_Inputs)

	m_OutputPin = new OutputPin(r_FanOut);
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}