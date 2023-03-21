#ifndef _EDIT_CONN
#define _EDIT_CONN

#include "action.h"
#include "..\Components\Connection.h"
#include "AddConnection.h"

class EditConn : public Action
{
private:

	int srcX, srcY, destX, destY;	//Points Clicked
	InputPin* inp;
	OutputPin* outp;
	
	

public:
	EditConn(ApplicationManager* pApp);
	virtual ~EditConn(void);

	AddConnection* EditAdd = new AddConnection(pManager); 

	//int checkPin(int x, int y);
	//void connectPin(int x, int y, int r);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
