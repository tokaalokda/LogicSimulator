#pragma once

#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddINV.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddLED.h"
#include "Actions\AddCONNECTION.h"
#include "Actions\SELECT.h"
#include "Actions\SAVE.h"
#include "Actions\LOAD.h"
#include "Actions\Label.h"
#include "Actions\EditCONN.h"
#include "Actions\UNDO.h"
#include "Actions\REDO.h"
#include "Actions\DELETE.h"
#include "Actions\COPY.h"
#include "Actions\CUT.h"
#include "Actions\MOVE.h"
#include "Actions\DefMODULE.h"
#include "Actions\NamedMODULE.h"
#include "Actions\SaveMODULE.h"
#include "Actions\TruthTable.h"
#include <cstdio>
#include <iostream>
using namespace std; 


ApplicationManager::ApplicationManager()
{
	
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	for (int i = 0; i < MaxCompCount; i++)
		Undone_Comps[i] = NULL;

	for (int i = 0; i < 100000; i++)
		Done_Acts[i] = NI;

	for (int i = 0; i < 100000; i++)
		Undone_Acts[i] = NI;

	for (int i = 0; i < 100000; i++)
		DoneEditConn[i] = NULL;

	for (int i = 0; i < 100000; i++)
		UndoneEditConn[i] = NULL;

	
	
		

	//Creates the UI Object & Initialize the UI	
	pUI = new UI;

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UnselectAll()
{
	    for (int i = 0; i < CompCount; i++)
			CompList[i]->selected = false;
		UpdateInterface();

}
////////////////////////////////////////////////////////////////////

int ApplicationManager::ReturnSelected() const {
	
	int SelectedCount = 0; 
	int Location; 
	
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected ==true) {
			SelectedCount++;
			Location = i;
		}
		if (SelectedCount == 2)
		{
			pUI->PrintMsg("You cannot perform this action for more than 1 component. Please select only 1 then try again.");
			return -1; 
		}
	}

	if (SelectedCount==0)
	{
		pUI->PrintMsg("Please select a component before you try to perform this action.");
		return -1;
	}

	if (SelectedCount == 1)
	{
		return Location;
	}
	
}
////////////////////////////////////////////////////////////////////
bool ApplicationManager::isAllConnected() const {
	for (int i = 0; i < CompCount; i++) {
		switch (CompList[i]->ComponentType) {
		case T_AND2:
		case T_OR2:
		case T_NAND2:
		case T_NOR2:
		case T_XOR2:
		case T_XNOR2:
		{
			if (CompList[i]->GetOutPinStatus() == NCON || CompList[i]->GetInputPinStatus(1) == NCON
				|| CompList[i]->GetInputPinStatus(2) == NCON)
			{
				return 0;
				cout << i << endl;
			}
			break;

		}
		case T_NOT:
		{
			if (CompList[i]->GetOutPinStatus() == NCON || CompList[i]->GetInputPinStatus(1) == NCON)
			{
				return 0;
				cout << i; 
			}
			break;
		}
		case T_SWITCH:
		{
			if (CompList[i]->GetOutPinStatus() == NCON)
			{
				cout << i << endl; 
				return 0;
			}
			break;
		}
		case T_LED:
		{
			if (CompList[i]->GetInputPinStatus(1) == NCON) 
			{
				cout << i << endl;
				return 0;
			}
		}
		case T_Module: 
		case T_ModuleB: 
		{
			if (CompList[i]->GetInputPinStatus(1) == NCON || CompList[i]->GetInputPinStatus(2) == NCON ||
				CompList[i]->GetInputPinStatus(3) == NCON || CompList[i]->GetInputPinStatus(4) == NCON ||
				CompList[i]->GetInputPinStatus(5) == NCON || CompList[i]->GetOutPinStatus() == NCON )
			{
				
				cout << i << endl; 
				return 0;
			}


			break; 
		}
		case T_CONNECTION: continue;
		}
	}
	return 1;
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::TurnOffAll() {
	for (int i = 0; i < CompCount; i++) {
		switch (CompList[i]->ComponentType) {
		case T_CONNECTION: {
			CompList[i]->setInputPinStatus(0,LOW);
			CompList[i]->Operate();
			break;}
		case T_LED:
		case T_SWITCH: {
			CompList[i]->isON = LOW;
			break;
		}
		}
	}
}
void ApplicationManager::ExecuteAction(ActionType ActType)
{

	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_INV:
		//Unselect any selected before next action 
		UnselectAll();
		pAct = new AddINV(this);
	    break;

	case ADD_AND_GATE_2:
		UnselectAll();
		pAct = new AddANDgate2(this);
		break;

	case ADD_OR_GATE_2:
		UnselectAll();
		pAct = new AddORgate2(this);
		break;

	case ADD_NAND_GATE_2:
		UnselectAll();
		pAct = new AddNANDgate2(this);
		break;

	case ADD_NOR_GATE_2:
		UnselectAll();
		pAct = new AddNORgate2(this);
		break;

	case ADD_XOR_GATE_2:
		UnselectAll();
		pAct = new AddXORgate2(this);
		break;

	case ADD_XNOR_GATE_2:
		UnselectAll();
		pAct = new AddXNORgate2(this);
		break;

	case ADD_Switch:
		UnselectAll();
		pAct = new AddSWITCH(this);
		break;

	case ADD_LED:
		UnselectAll();
		pAct = new AddLED(this);
		break;

	case ADD_CONNECTION:
		UnselectAll();
		pAct = new AddConnection(this);
		break;

	case ADD_Label: //For adding and editing labels
		pAct = new Label(this);
		break;

	case EDIT_Conn:
		pAct = new EditConn(this); 
		break; 
	
	case SELECT:
		pAct = new Select(this, pUI->PCx, pUI->PCy);
		break;

	
	case SAVE:
		UnselectAll();
		pAct = new Save(this);
		break;

	case LOAD:
		UnselectAll();
		pAct = new Load(this);
		break;

	case UNDO:
		UnselectAll();
		pAct = new Undo(this);
		break;

	case REDO:
		UnselectAll();
		pAct = new Redo(this);
		break;

	case DEL:
		pAct = new Delete(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case CUT:
		pAct = new Cut(this);
		break;

	
	case MOVE:
		pAct = new Move(this);
		break;


	case DefMODULE:
		UnselectAll();
		pAct = new DefModule(this); 
		break; 
	
	case NamedMODULE: 
		UnselectAll();
		pAct = new NamedModule(this);
		break; 

	case SaveMODULE: 
		UnselectAll();
		pAct = new SaveModule(this);
		break; 

	case DSN_MODE:
		UnselectAll();
		TurnOffAll();
		pUI->CreateDesignToolBar();
		break;

	case SIM_MODE:
		UnselectAll();
		if (isAllConnected())
			pUI->CreateSimulationToolBar();
		else
			pUI->PrintMsg("One or more components are not connected!");
		break;
	case TRUTH:
		pAct = new TruthTable(this);
		break;
	case EXIT:

		
		string Temp; 

		for (int i = 0; i < UndoneLoadCount+LoadCount; i++) {
			Temp = "ProgramTXTfiles\\temporaryloadtype1file";
			Temp += to_string(i);
			Temp += ".txt";
			remove(Temp.c_str()); 
		}

		for (int i = 0; i < UndoneLoadCount+LoadCount; i++) {
			Temp = "ProgramTXTfiles\\temporaryloadtype2file";
			Temp += to_string(i);
			Temp += ".txt";
			remove(Temp.c_str());
		}
		
		break;


	}
	if(pAct)
	{
		if (pAct->Type != NI)
			Done_Acts[executed++] = pAct->Type;

		pAct->Execute();

		if (pAct->Type == DefMODULE)
		{
			for (int i = CompCount - 74; i < CompCount - 2; i++)
			{
				CompList[i]->inModule = 1;
				if (CompList[i]->ComponentType != T_CONNECTION) {
					CompList[i]->m_OutputPin->setStatus(LOW);
					if (CompList[i]->ComponentType == T_NOT)
						CompList[i]->m_InputPins[0].setStatus(LOW);
				}

			}
			
		}


		
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	
	
	
	for (int i = 0; i < CompCount; i++)
		pUI->LabelComp(CompList[i]->m_Label, CompList[i]->m_pGfxInfo->PointsList[0].x, CompList[i]->m_pGfxInfo->PointsList[0].y);

	if (pUI->AppMode == SIMULATION)
    for(int j = 0; j < 300; j++)
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Operate();

	for (int i = 0; i < CompCount; i++)
		if (CompList[i]->inModule != 1)
			  CompList[i]->Draw(pUI);



}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete pUI;
	
}

