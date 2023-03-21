#ifndef _TRUTHTABLE
#define _TRUTHTABLE

#include "action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include <cmath>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

class TruthTable : public Action
{
private:
	UI* pUI = pManager->GetUI();
	Component* AllSwitches[200];
	Component* AllLEDs[200];
public:
	TruthTable(ApplicationManager* pApp);
	virtual ~TruthTable(void);

	//Execute action (code depends on action type)
	virtual void Execute();
};

#endif