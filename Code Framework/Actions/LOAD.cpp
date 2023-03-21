#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND2.h"
#include "..\Components\OR2.h"
#include "..\Components\NOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\NAND2.h"
#include "..\Components\INV.h"
#include "..\Components\SWITCH.h"
#include "..\Components\LED.h"
#include "..\Components\CONNECTION.h"
#include "SAVE.h"
#include <chrono>
#include <thread>






Load::Load(ApplicationManager* pApp) :Action(pApp)
{
	Type = LOAD;
} 

Load::~Load(void)
{
	delete LSave; 
}

void Load::Execute()
{
	

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	char key;

	//Print Action Message
	if (pManager->CompCount != 0) {
		pUI->PrintMsg("Click enter to save current circuit then load, esc to abort action, or backspace to load without saving.\n");
		pUI->getpWind()->WaitKeyPress(key);
	}
	else
		key = 8; 

	while (key != 13 && key != 27 && key!=8) {
		pUI->getpWind()->WaitKeyPress(key);
	}

	if (key == 27)
		pUI->PrintMsg("Load aborted."); 
	else 
	{
		LSave = new Save(pManager);
		if (key == 13) {
			LSave->Execute();
			std::this_thread::sleep_for(std::chrono::seconds(0));
		}

		string TempName = "ProgramTXTfiles\\temporaryloadtype1file"; 
		TempName += to_string(pManager->LoadCount); 
		TempName += ".txt"; 
			LSave->ExecutePart(TempName, pUI); 

		pUI->PrintMsg("LOAD: Type in a file's name with directory. Use 2 backslashes. Click enter when done.\n");

		
		name = pUI->GetString();

		bool Success = ExecutePart(name, pUI, 0); 

		if (Success) {
			
			pUI->PrintMsg("Load Completed!.\n");
			pManager->LoadCount++;
			
		}

		
		else
			pUI->PrintMsg("Error opening file.\n");

	} 
}


bool Load::ExecutePart(string name, UI* pUI, int count) {

	ifstream myfile;
	myfile.open(name.c_str());
	if (myfile.is_open())
	{
		pUI->ClearDrawingArea();

		pManager->CompCount = count;
		
		//Calculate the rectangle Corners
		int gateWidth = pUI->getGateWidth();
		int gateHeight = pUI->getGateHeight();

		string line;

		int GateCount;
		myfile >> GateCount; //Read number of gates from first line 
		getline(myfile, line);//discard first line 

		int* ID = new int[GateCount];


		string type, label;
		int Identity, Cx = 0, Cy = 0;

		for (int i = 0; i < GateCount; i++) {


			getline(myfile, line);
			istringstream a(line);
			a >> type;
			a >> Identity;
			a >> label;
			a >> Cx;
			a >> Cy;
			ID[i] = Identity;



			GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to load the gate

			pGInfo->PointsList[0].x = Cx - gateWidth / 2;
			pGInfo->PointsList[0].y = Cy - gateHeight / 2;
			pGInfo->PointsList[1].x = Cx + gateWidth / 2;
			pGInfo->PointsList[1].y = Cy + gateHeight / 2;




			if (type == "AND2") {
				pManager->CompList[count + i] = new AND2(pGInfo, Default_FANOUT);
			}


			if (type == "OR2") {
				pManager->CompList[count + i] = new OR2(pGInfo, Default_FANOUT);
			}


			if (type == "NOR2") {
				pManager->CompList[count + i] = new NOR2(pGInfo, Default_FANOUT);
			}


			if (type == "XOR2") {
				pManager->CompList[count + i] = new XOR2(pGInfo, Default_FANOUT);
			}


			if (type == "XNOR2") {
				pManager->CompList[count + i] = new XNOR2(pGInfo, Default_FANOUT);
			}


			if (type == "NAND2") {
				pManager->CompList[count + i] = new NAND2(pGInfo, Default_FANOUT);
			}


			if (type == "LED") {
				pManager->CompList[count + i] = new LED(pGInfo, Default_FANOUT);
			}


			if (type == "SWITCH") {
				pManager->CompList[count + i] = new Switch(pGInfo, Default_FANOUT);
			}


			if (type == "NOT") {
				pManager->CompList[count + i] = new INV(pGInfo, Default_FANOUT);
			}

			pManager->CompList[count + i]->m_Label = label;
			
			
			pManager->CompList[count + i]->selected = false; 

			pManager->CompCount++;

		}


		int ConnCount;
		myfile >> ConnCount;//Read number of components 
		getline(myfile, line);//Discard number of components 


		int S_Comp, T_Comp, P_n;
		for (int i = 0; i < ConnCount; i++) {

			getline(myfile, line);
			istringstream a(line);
			a >> S_Comp;
			a >> T_Comp;
			a >> P_n;

				GraphicsInfo* r_GfxInfo = new GraphicsInfo(2);
				OutputPin* pSrcPin;
				InputPin* pDstPin;

			int sourceComp;
			int destinationComp;

			for (int j = count; j < GateCount+count; j++) {
				if (ID[j-count] == S_Comp) {

					sourceComp = j;
					break;
				}


			}
			
			for (int j = count; j < GateCount+count; j++) {

				if (ID[j-count] == T_Comp) {

						destinationComp = j;
						break;
				}
			}



			//Gfx info of connections	
			Component* comp = pManager->CompList[sourceComp];
			int x1 = comp->m_pGfxInfo->PointsList[0].x;
			int y1 = comp->m_pGfxInfo->PointsList[0].y;
			int x2 = comp->m_pGfxInfo->PointsList[1].x;
			int y2 = comp->m_pGfxInfo->PointsList[1].y;

			pSrcPin = comp->m_OutputPin;
			comp->m_OutputPin->setStatus(LOW);
			
			

			switch (comp->ComponentType) {
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
			{
				r_GfxInfo->PointsList[0].x = x2;
				r_GfxInfo->PointsList[0].y = y2 - 25;
				break;
			}
			case T_NOT:
			{
				r_GfxInfo->PointsList[0].x = x2 - 1;
				r_GfxInfo->PointsList[0].y = y2 - 24;
				break;
			}

			case T_SWITCH:
			{
				r_GfxInfo->PointsList[0].x = x2;
				r_GfxInfo->PointsList[0].y = y2 - 25;
				break;
			}
			}



			comp = pManager->CompList[destinationComp];
			x1 = comp->m_pGfxInfo->PointsList[0].x;
			y1 = comp->m_pGfxInfo->PointsList[0].y;
			x2 = comp->m_pGfxInfo->PointsList[1].x;
			y2 = comp->m_pGfxInfo->PointsList[1].y;

			pDstPin = &comp->m_InputPins[P_n-1];
			comp->m_InputPins[P_n-1].setStatus(LOW);
			



			switch (comp->ComponentType) {
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
			{

				if (P_n == 1) {
					r_GfxInfo->PointsList[1].x = x1;
					r_GfxInfo->PointsList[1].y = y1 + 13;
				}
				else
				{
					r_GfxInfo->PointsList[1].x = x1;
					r_GfxInfo->PointsList[1].y = y2 - 13;
				}
				break;
			}
			case T_NOT:
			{


				r_GfxInfo->PointsList[1].x = x1;
				r_GfxInfo->PointsList[1].y = y1 + 26;
				break;

			}
			case T_LED:
			{
				r_GfxInfo->PointsList[1].x = x1 + 15;
				r_GfxInfo->PointsList[1].y = y2 - 8;
				break;
			}
			}



			//Create Connection
			pManager->CompList[count + GateCount + i] = new Connection(r_GfxInfo, pSrcPin, pDstPin);
			pManager->CompCount++;

			
		}
		myfile.close(); 
		return 1; 
	}

	else return 0; 

}



