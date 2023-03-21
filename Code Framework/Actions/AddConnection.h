#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
#include "..\ApplicationManager.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"

class AddConnection : public Action {
private:
	int srcX, srcY, destX, destY;
	int pin;
	InputPin* inp;
	OutputPin* outp;
	
public:
	Component* component;
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);
	GraphicsInfo* pGInfo = new GraphicsInfo(2); 
	
	int checkPin(int x, int y); 
	void connectPin(int x, int y, int r);

	//Execute action (code depends on action type)
	virtual void Execute();
};