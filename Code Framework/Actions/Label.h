#ifndef _LABEL
#define _LABEL

#include "action.h"
#include "..\Components\AND2.h"

class Label : public Action
{
protected:
	int Cx, Cy;
	Component* component; 

public:
	Label(ApplicationManager* pApp);
	virtual ~Label(void);
	Component* getComponentLabeled(); 
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
