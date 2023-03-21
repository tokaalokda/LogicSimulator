#ifndef _LED_H
#define _LED_H


#include "Gate.h"

class LED :public Gate
{

public:
    LED(GraphicsInfo* r_pGfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the Switch gate
	virtual void Draw(UI*);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	int getStatus();
};

#endif

