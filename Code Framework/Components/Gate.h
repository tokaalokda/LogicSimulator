#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate:public Component
{
protected:
   
public:
	Gate(GraphicsInfo* pGfxInfo, int r_Inputs, int r_FanOut);
	

};

#endif
