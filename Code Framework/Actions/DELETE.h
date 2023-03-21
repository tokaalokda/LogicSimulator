#ifndef _DELETE_
#define _DELETE_

#include "action.h"
#include "..\Components\Component.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"

class Delete : public Action
{
private:
	

public:
	Component* deleted; //To be used in "Delete"s execution
	
	Delete(ApplicationManager* pApp);
	virtual ~Delete(void);

	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif
