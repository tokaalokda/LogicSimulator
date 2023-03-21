#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

private:
	enum { MaxCompCount = 10000 };	//Max no of Components

	UI* pUI; //pointer to the UI

public:	

	////Delete's things

	//int delcount = 0;
	//Component* Deltd[1000]; //Array of deleted elements for undo purposes
	//int DelConnCount = 0; //For undo purposes
	//Component* DelConn[1000]; //To save the removed connections for undo purposes

	////Cut's things

	//int CutConnCount = 0; //For undo purposes
	//Component* CutItem;
	//Component* CutConn[1000]; //To save the removed connections for undo purposes
	//GraphicsInfo* CutpGInf = new GraphicsInfo(2); //To save the old position for undo purposes

	string HeldString;
	ApplicationManager(); //constructor

	ActionType* Done_Acts = new ActionType[100000]; //Array of Done actions
	ActionType* Undone_Acts = new ActionType[100000]; //Array of undone actions
	int executed = 0; //Number of done actions
	int Undone_count = 0; //Number of undone actions

	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	int CompCount = 0;		//Actual number of Components

	Component* Undone_Comps[MaxCompCount]; //Array of undone components	
	int undone_Compcount = 0; //Number of undone components
	int LoadCount = 0;
	int UndoneLoadCount = 0; 

	int* ModuleCompCount = new int[100000]; 
	int* UndoneModuleCompCount = new int[100000];
	int ModuleCount = 0; 
	int UndoneModuleCount = 0; 

	Component* DoneEditConn[100000];
	Component* UndoneEditConn[100000];
	int EditConnCount = 0;
	int UndoneEditConnCount = 0;
	int* EditConnPlaces = new int[100000];
		

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Unselects selected components before new action is excuted (not used with all action types)
	void UnselectAll(); 

	//Checks that only one component is selected and returns its location
	int ReturnSelected() const; 

	//Checks if all components are connected before running the simulation
	bool isAllConnected() const;

	//Turns off all LEDs and Switches before going back to design mode
	void TurnOffAll();



	//destructor
	~ApplicationManager();
};

#endif