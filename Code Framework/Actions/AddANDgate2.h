#ifndef _ADD_AND_GATE_H
#define _ADD_AND_GATE_H

#include "action.h"
#include "..\Components\AND2.h"

class AddANDgate2 :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	AddANDgate2(ApplicationManager *pApp);
	virtual ~AddANDgate2(void);
	//Execute action (code depends on action type)
	virtual void Execute();


};

#endif