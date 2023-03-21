#ifndef _Named_MODULE_H
#define _Named_MODULE_H

#include "action.h"
#include "LOAD.h"
#include "Label.h"

class NamedModule : public Action
{
private:
	int Cx, Cy;	//Center point of the module

public:
	NamedModule(ApplicationManager* pApp);
	virtual ~NamedModule(void);

	string* ModuleInfo;

	Load* MLoad = new Load(pManager); 
	Label* MLabel = new Label(pManager); 

	//Execute action (code depends on action type)
	virtual void Execute();
	void ExecutePart(string TempName, UI* pUI);


};

#endif
