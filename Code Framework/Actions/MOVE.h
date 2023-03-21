#ifndef _MOVE_
#define _MOVE_

#include "action.h"
#include "..\Components\Component.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"

class Move : public Action
{
private:
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	window* pWind = pUI->getpWind();
	int Cx, Cy;
public:
	Move(ApplicationManager* pApp);
	virtual ~Move(void);
	Component* deleted;
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
