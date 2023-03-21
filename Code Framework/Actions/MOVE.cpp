#include "MOVE.h"
#include "..\ApplicationManager.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
	 Type = MOVE;
}

Move::~Move(void)
{
}

void Move::Execute()
{
	//Print Action Message
	pUI->PrintMsg("You clicked on move.");

	buttonstate state = pWind->GetButtonState(LEFT_BUTTON, Cx, Cy);
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	while (state == BUTTON_UP) {
		state = pWind->GetButtonState(LEFT_BUTTON, Cx, Cy);
	}

	for (int i = 0; i < pManager->CompCount; i++) {
		if (pManager->CompList[i]->ComponentType != T_CONNECTION) {

			if (Cx > pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && Cx < pManager->CompList[i]->m_pGfxInfo->PointsList[1].x &&
				Cy > pManager->CompList[i]->m_pGfxInfo->PointsList[0].y && Cy < pManager->CompList[i]->m_pGfxInfo->PointsList[1].y) {

				
				while (state == BUTTON_DOWN && Cy > pUI->ToolBarHeight + 25 && Cy < (pUI->height - pUI->StatusBarHeight - 25)) {
					pWind->DrawRectangle(pManager->CompList[i]->m_pGfxInfo->PointsList[0].x, pManager->CompList[i]->m_pGfxInfo->PointsList[0].y,
						pManager->CompList[i]->m_pGfxInfo->PointsList[1].x, pManager->CompList[i]->m_pGfxInfo->PointsList[1].y);
					pManager->CompList[i]->m_pGfxInfo->PointsList[0].x = Cx - gateWidth / 2;
					pManager->CompList[i]->m_pGfxInfo->PointsList[0].y = Cy - gateWidth / 2;
					pManager->CompList[i]->m_pGfxInfo->PointsList[1].x = Cx + gateWidth / 2;
					pManager->CompList[i]->m_pGfxInfo->PointsList[1].y = Cy + gateWidth / 2;
					pManager->CompList[i]->Draw(pUI);
					state = pWind->GetButtonState(LEFT_BUTTON, Cx, Cy);
				}
				pUI->ClearDrawingArea();

			}
		}
	}


} 
