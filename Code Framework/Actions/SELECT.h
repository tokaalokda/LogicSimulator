#ifndef _SELECT
#define _SELECT

#include "action.h"
#include "..\Components\Component.h"

class Select : public Action
{
private:
	int Cx, Cy;

public:
	Select(ApplicationManager* pApp, int x, int y);
	virtual ~Select(void);

	//Execute action (code depends on action type)
	virtual void Execute();



};

#endif
