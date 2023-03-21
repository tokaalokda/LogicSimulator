#ifndef _CUT_
#define _CUT_

#include "action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"
#include "Label.h"
#include "..\Actions\DefMODULE.h"

class Cut : public Action
{
private:

public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);
	Component* Cutitm; //To be used in "Cut" execution

	DefModule* CUTDef = new DefModule(pManager); 

	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
