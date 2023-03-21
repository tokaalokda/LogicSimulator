#ifndef _COPY_
#define _COPY_

#include "action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include "..\components\NAND2.h"
#include "..\components\AND2.h"
#include "..\components\LED.h"
#include "..\components\Switch.h"
#include "..\Components\INV.h"
#include "..\Components\NOR2.h"
#include "..\Components\OR2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\XOR2.h"
#include "Label.h"

class Copy : public Action
{
private:


public:
	Component* copied;
	Copy(ApplicationManager* pApp);
	virtual ~Copy(void);
	//Execute action (code depends on action type)
	virtual void Execute();



};

#endif