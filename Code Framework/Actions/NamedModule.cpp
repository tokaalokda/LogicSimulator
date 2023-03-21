#include "NamedMODULE.h"
#include "..\ApplicationManager.h"
#include <istream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;
 

NamedModule:: NamedModule(ApplicationManager* pApp) :Action(pApp) 
{
	Type = NamedMODULE; 
};


NamedModule::~NamedModule(void) {
	delete MLoad;
	delete[] ModuleInfo;
	delete MLabel; 
};


void NamedModule::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Insert a Named Module: Press enter to view the list of modules or escape to abort the action.");
	
	char key ;
	pUI->getpWind()->WaitKeyPress(key);
	
	
	while (key != 13 && key != 27 ) {
		pUI->getpWind()->WaitKeyPress(key);
	}

	if (key == 27)
		pUI->PrintMsg("Insert module aborted.");

	else {
		
		pUI->ClearDrawingArea();

		int ModuleCount;

		string file = "ProgramTXTfiles\\ModuleCount.txt";

		ifstream infile(file.c_str());
		infile >> ModuleCount;
		infile.close();

		if (ModuleCount > 0) {


			ModuleInfo = new string[2 * ModuleCount];

			string temp;
			string file2 = "ProgramTXTfiles\\ModuleInfo.txt";

			ifstream infile2(file2.c_str());
			getline(infile2, temp);

			for (int i = 0; i < ModuleCount * 2; i = i + 2)
			{
				getline(infile2, ModuleInfo[i]);
				getline(infile2, ModuleInfo[i + 1]);

			}
			infile2.close();


			for (int i = 0; i < ModuleCount * 2; i = i + 2)
			{
				temp = to_string(i / 2) + "- " + ModuleInfo[i] + "   " + ModuleInfo[i + 1];
				pUI->PrintOnWind(temp, i / 2);
			}

			pUI->PrintMsg("Enter the number of the module you will load.");

			temp = pUI->GetString();
			stringstream a(temp);
			int ModuleNumber;
			a >> ModuleNumber;

			while (ModuleNumber >= ModuleCount)
			{
				pUI->PrintMsg("Please enter a valid module number.");
				temp = pUI->GetString();
				stringstream a(temp);
				int ModuleNumber;
				a >> ModuleNumber;
			}

			pUI->ClearDrawingArea();
			pManager->UpdateInterface();



			string TempName = "ProgramTXTfiles\\Modulefile";
			TempName += to_string(ModuleNumber);
			TempName += ".txt";

			ExecutePart(TempName, pUI);
		}

		else pUI->PrintMsg("There are no saved modules to display. Action is aborted.");

	}

}

void NamedModule::ExecutePart(string TempName, UI* pUI) {

	int OldCount = pManager->CompCount;

	pUI->ClearStatusBar();

	pUI->PrintMsg("Click where you will insert the module.");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	pUI->ClearStatusBar();

	MLoad->ExecutePart(TempName, pUI, pManager->CompCount);

	int maxX = 0, maxY = 0, minX = pUI->width, minY = pUI->height;

	for (int i = OldCount; i < pManager->CompCount; i++) {

		if (pManager->CompList[i]->ComponentType != T_CONNECTION)
		{

			if (pManager->CompList[i]->m_pGfxInfo->PointsList[0].x < minX)
				minX = pManager->CompList[i]->m_pGfxInfo->PointsList[0].x;

			if (pManager->CompList[i]->m_pGfxInfo->PointsList[0].y < minY)
				minY = pManager->CompList[i]->m_pGfxInfo->PointsList[0].y;

			if (pManager->CompList[i]->m_pGfxInfo->PointsList[1].x > maxX)
				maxX = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x;

			if (pManager->CompList[i]->m_pGfxInfo->PointsList[1].y > maxY)
				maxY = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;

		}

	}

	int centerX, centerY;

	centerX = (minX + maxX) / 2;
	centerY = (minY + maxY) / 2;

	if (Cy + minY - centerY -25 < pUI->ToolBarHeight || Cy + maxY - centerY > pUI->height - pUI->StatusBarHeight)
	{
		if (Cy + minY - centerY -25 < pUI->ToolBarHeight)
			pUI->PrintMsg("This clicked point places a module where it interferes with the  tool bar. Action aborted.");
		if (Cy + maxY - centerY > pUI->height - pUI->StatusBarHeight)
			pUI->PrintMsg("This clicked point places a module where it interferes with the  status bar. Action aborted.");

		pManager->CompCount = OldCount;

		for (int i = OldCount; i < pManager->CompCount; i++)
			pManager->CompList[i] = NULL;

		pManager->Done_Acts[pManager->executed] = NI;
		pManager->executed--; 


	}

	else
	{

		for (int i = OldCount; i < pManager->CompCount; i++) {

			pManager->CompList[i]->m_pGfxInfo->PointsList[0].x = Cx + (pManager->CompList[i]->m_pGfxInfo->PointsList[0].x - centerX);
			pManager->CompList[i]->m_pGfxInfo->PointsList[1].x = Cx + (pManager->CompList[i]->m_pGfxInfo->PointsList[1].x - centerX);
			pManager->CompList[i]->m_pGfxInfo->PointsList[0].y = Cy + (pManager->CompList[i]->m_pGfxInfo->PointsList[0].y - centerY);
			pManager->CompList[i]->m_pGfxInfo->PointsList[1].y = Cy + (pManager->CompList[i]->m_pGfxInfo->PointsList[1].y - centerY);

		}


		bool unique;

		do {
			unique = 1;

			for (int i = OldCount; i < pManager->CompCount; i++) {

				if (pManager->CompList[i]->ComponentType == T_SWITCH || pManager->CompList[i]->ComponentType == T_LED)
				{

					for (int j = 0; j < OldCount; j++) {

						if ((pManager->CompList[i]->ComponentType == T_SWITCH || pManager->CompList[i]->ComponentType == T_LED) && pManager->CompList[i]->m_Label == pManager->CompList[j]->m_Label)
						{
							unique = 0;
							pManager->CompList[i]->selected = 1;
							pManager->UpdateInterface();
							pUI->PrintMsg("The selected LED/Switch has the same label as a LED/Switch already inserted and will need to be relabeled.");
							std::this_thread::sleep_for(std::chrono::seconds(2));
							MLabel->Execute();
							pManager->UpdateInterface();
						}

					}

				}

			}
		} while (!unique);

		pManager->ModuleCompCount[pManager->ModuleCount] = (pManager->CompCount) - OldCount;
		pManager->ModuleCount++;

		
	}



}