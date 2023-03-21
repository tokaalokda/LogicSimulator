#ifndef _LOAD_
#define _LOAD_

#include "action.h"
#include "Save.h"
#include <fstream>
#include<sstream>
#include <iomanip>
using namespace std;
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

class Load : public Action
{
public:
	Load(ApplicationManager* pApp);
	virtual ~Load(void);
	string name;
	Save* LSave; 
	//Execute action (code depends on action type)
	virtual void Execute();
	bool ExecutePart(string name, UI* pUI, int count);

	

};

#endif

