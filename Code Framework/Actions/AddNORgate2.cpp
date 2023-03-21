#include "AddNORgate2.h"
#include "..\ApplicationManager.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp) :Action(pApp)
{
	Type = ADD_COMP;
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input NOR Gate: Click to add the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the gate

	pGInfo->PointsList[0].x = Cx - gateWidth / 2;
	pGInfo->PointsList[0].y = Cy - gateHeight / 2;
	pGInfo->PointsList[1].x = Cx + gateWidth / 2;
	pGInfo->PointsList[1].y = Cy + gateHeight / 2;

	if (pGInfo->PointsList[0].y -25 < pUI->ToolBarHeight || pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight) {
		if (pGInfo->PointsList[0].y -25 < pUI->ToolBarHeight)
			pUI->PrintMsg("You cannot place a component on the toolbar. Action aborted.");
		if (pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
			pUI->PrintMsg("You cannot place a component on the status bar. Action aborted.");

		pManager->Done_Acts[pManager->executed] = NI;
		pManager->executed--;
	}
	else {
		NOR2* pA = new NOR2(pGInfo, Default_FANOUT);
		pManager->AddComponent(pA);
	}
}

