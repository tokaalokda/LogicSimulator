#include "DefMODULE.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"


DefModule::DefModule(ApplicationManager* pApp) :Action(pApp)
{	
	Type = DefMODULE;
};


DefModule::~DefModule(void) {
	delete MLoad; 
};

void DefModule::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	

	pUI->PrintMsg("Click where you will insert the module.");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();

	//Calculate the rectangle Corners
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the AND2 gate

	pGInfo->PointsList[0].x = Cx - 2*gateWidth ;
	pGInfo->PointsList[0].y = Cy - gateHeight;
	pGInfo->PointsList[1].x = Cx + 2*gateWidth;
	pGInfo->PointsList[1].y = Cy + gateHeight;

	if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight || pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight) {
		if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight)
			pUI->PrintMsg("You cannot place a component on the toolbar. Action aborted.");
		if (pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
			pUI->PrintMsg("You cannot place a component on the status bar. Action aborted.");

		pManager->Done_Acts[pManager->executed] = NI;
		pManager->executed--;
	}
	else {

		string TempName = "ProgramTXTfiles\\DefaultModuleA.txt";
		string TempName2 = "ProgramTXTfiles\\DefaultModuleB.txt";

		int OldCount = pManager->CompCount;

		pUI->ClearStatusBar();

		MLoad->ExecutePart(TempName, pUI, OldCount);
		MLoad->ExecutePart(TempName2, pUI, OldCount+36);

		for (int i = OldCount; i < pManager->CompCount; i++) {

				
				pManager->CompList[i]->m_pGfxInfo->PointsList[0].x = Cx;
				pManager->CompList[i]->m_pGfxInfo->PointsList[1].x = Cx;
				pManager->CompList[i]->m_pGfxInfo->PointsList[0].y = Cy;
				pManager->CompList[i]->m_pGfxInfo->PointsList[1].y = Cy;

		}
			   		 	  	  
		Module* pA = new Module(pGInfo, Default_FANOUT);
		pA->pManager = pManager; 
		pManager->AddComponent(pA);

		GraphicsInfo* pGInfo2 = new GraphicsInfo(2);

		pGInfo2->PointsList[0].x = Cx;
		pGInfo2->PointsList[0].y = Cy;
		pGInfo2->PointsList[1].x = Cx;
		pGInfo2->PointsList[1].y = Cy;

		ModuleB* pB = new ModuleB(pGInfo2, Default_FANOUT);
		pB->pManager = pManager;
		pManager->AddComponent(pB);
		
	}
}
