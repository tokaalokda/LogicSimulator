#ifndef _ADD_INV
#define _ADD_INV

#include "action.h"
#include "..\Components\INV.h"

class AddINV : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	//int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddINV(ApplicationManager* pApp);
	virtual ~AddINV(void);
	//Execute action (code depends on action type)
	virtual void Execute();
};

#endif
