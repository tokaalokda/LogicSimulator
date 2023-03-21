#ifndef _Def_MODULE_H
#define _Def_MODULE_H
#include "Load.h"
#include "..\Components\MODULE.h" 
#include "..\Components\ModuleB.h" 


class DefModule : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate

public:
	DefModule(ApplicationManager* pApp);
	virtual ~DefModule(void);

	Load* MLoad = new Load(pManager);

	

	//Execute action (code depends on action type)
	virtual void Execute();


};

#endif
