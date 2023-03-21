#ifndef _SWITCH_H
#define _SWITCH_H


#include "Gate.h"

class Switch :public Gate
{
private:
	
public:
	Switch(GraphicsInfo* r_pGfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the Switch gate
	virtual void Draw(UI*);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	int getStatus();
};

#endif
