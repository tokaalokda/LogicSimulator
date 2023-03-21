#pragma once
#include "Action.h"
#include "SAVE.h"
#include "LOAD.h"
#include "../ApplicationManager.h"

class Redo :public Action
{

public:

	Redo(ApplicationManager* pApp);
	~Redo(void);
	Save* RSave = new Save(pManager);
	Load* RLoad = new Load(pManager); 

	//Execute action (code depends on action type)
	virtual void Execute();

};