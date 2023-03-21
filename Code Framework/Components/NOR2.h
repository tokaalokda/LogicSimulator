#ifndef _NOR2_H
#define _NOR2_H

/*
  Class NOR2
  -----------
  represent the 2-input NOR gate
*/

#include "Gate.h"

class NOR2 :public Gate
{
public:
	NOR2(GraphicsInfo* r_pGfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the OR gate
	virtual void Draw(UI*);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

#endif
