
#ifndef _SAVE_
#define _SAVE_

#include "action.h"
#include <fstream>
#include<sstream>
#include <iomanip>
using namespace std;
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

class Save : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	//int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	Save(ApplicationManager* pApp);
	virtual ~Save(void);
	string name;
	//Execute action (code depends on action type)
	virtual void Execute();
	bool ExecutePart(string name, UI* pUI); 

	

};

#endif

