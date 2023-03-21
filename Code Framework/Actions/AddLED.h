#ifndef _ADD_LED
#define _ADD_LED

#include "action.h"
#include "..\Components\LED.h"

class AddLED : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	//int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddLED(ApplicationManager* pApp);
	virtual ~AddLED(void);
	//Execute action (code depends on action type)
	virtual void Execute();



};

#endif
