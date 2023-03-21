#ifndef _ACTION_H
#define _ACTION_H
#include "../Defs.H"

class ApplicationManager; //forward class declaration


//Base class for all possible actions (abstract class)
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
public:
	Action(ApplicationManager *pApp) { pManager = pApp; }	//constructor
	ActionType Type = NI;
	//Execute action (code depends on action type)
	virtual void Execute()=0;

};

#endif