#ifndef _Save_MODULE_H
#define _Save_MODULE_H

#include "action.h"
#include "SAVE.h"

class SaveModule : public Action
{

public:

	string name; 
	string description; 
	string* ModuleNames; 

	SaveModule(ApplicationManager* pApp);
	virtual ~SaveModule(void);

	Save* MSave = new Save(pManager);

	//Execute action (code depends on action type)
	virtual void Execute();


};

#endif
