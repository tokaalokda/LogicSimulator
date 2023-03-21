#include "SELECT.h"
#include "..\ApplicationManager.h"


Select::Select(ApplicationManager* pApp, int x, int y) :Action(pApp)
{
	Cx = x; 
	Cy = y; 
}

Select::~Select(void)
{
}

void Select::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	
	bool found = false;
	int i = 0;
	
	while (found == false && i < pManager->CompCount) {
		
		if (pManager->CompList[i]->ComponentType != T_CONNECTION) {
			
			if (Cx > pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && Cx < pManager->CompList[i]->m_pGfxInfo->PointsList[1].x && Cy > pManager->CompList[i]->m_pGfxInfo->PointsList[0].y && Cy < pManager->CompList[i]->m_pGfxInfo->PointsList[1].y) {
				found = true;
			
				if (pUI->AppMode == SIMULATION && pManager->CompList[i]->ComponentType == T_SWITCH)
				{
					
					if (pManager->CompList[i]->isON == LOW)
						pManager->CompList[i]->isON = HIGH;

					else
						pManager->CompList[i]->isON = LOW;

				}
				
				else
				{
					if (pManager->CompList[i]->selected == false)
						pManager->CompList[i]->selected = true;

					else
						pManager->CompList[i]->selected = false;
				}
			}
		}

		
	

		if (pManager->CompList[i]->ComponentType == T_CONNECTION) {
			
			int x1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].x;
			int y1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].y;
			int x2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x;
			int y2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;

			


			if (Cx >= x1 && Cx <= x1 + (x2 - x1) / 3 && Cy >=y1-10 && Cy <=y1+10|| Cy >= y1 && Cy <= y2 && Cx >= x1 + ((x2 - x1)/3) - 20 && Cx <= x1 + ((x2 - x1) / 3) + 20 || Cx >= x1 + (x2 - x1) / 3 && Cx <= x2 && Cy >= y2 - 10 && Cy <= y2 + 10) {
				found = true;
				
				if (pManager->CompList[i]->selected == false) 
					pManager->CompList[i]->selected = true;
			
				else
					pManager->CompList[i]->selected = false;

			}
		}

		i++; 
	}

	if (found == false)
		pManager->UnselectAll(); 

}


