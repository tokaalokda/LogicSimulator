#include "SAVE.h"
#include "..\ApplicationManager.h"
#include <chrono>
#include <thread>



Save::Save(ApplicationManager* pApp) :Action(pApp)
{
}

Save::~Save(void)
{
}

void Save::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	bool success = 1; 

	if (pManager->CompCount != 0)
	{
		for (int i = 0; i < pManager->CompCount; i++) {
			if (pManager->CompList[i]->ComponentType == T_Module)
			{
				pUI->PrintMsg("Circuits with default Modules cannot be saved. Please delete the module component before attempting to save");
				success = 0; 
			}
		} 
			if (success)
			{
				//Print Action Message
				pUI->PrintMsg("SAVE: Type in a file's name with directory. Use 2 backslashes. Click enter when done.\n");
				name = pUI->GetString();

				bool Success = ExecutePart(name, pUI);

				if (Success)
				{
					pUI->PrintMsg("Circuit saved!");
					std::this_thread::sleep_for(std::chrono::seconds(2));
					pUI->ClearStatusBar();
				}
				else  pUI->PrintMsg("Error opening file.\n");
			} 

	}
	else pUI->PrintMsg("Please draw a circuit before you try to save.\n");
}


bool Save::ExecutePart(string name, UI* pUI) {

	for (int i = 0; i < pManager->CompCount; i++)
		if (pManager->CompList[i]->ComponentType == T_Module)
		{
			pUI->PrintMsg("Circuits with default Modules cannot be saved. Please delete the module component before attempting to save");
			return 0;
		} 
		
			ofstream myfile;
			myfile.open(name.c_str());
			if (myfile.is_open())
			{
				int ConnCount = 0;

				for (int i = 0; i < pManager->CompCount; i++) {
					if (pManager->CompList[i]->ComponentType == T_CONNECTION)
						ConnCount++;
				}

				myfile << pManager->CompCount - ConnCount << endl;

				for (int i = 0; i < pManager->CompCount; i++) {
					if (pManager->CompList[i]->ComponentType != T_CONNECTION) {
						string type;
						switch (pManager->CompList[i]->ComponentType) {
						case T_SWITCH:  type = "SWITCH"; break;
						case T_LED: type = "LED"; break;
						case T_NOT: type = "NOT"; break;
						case T_AND2: type = "AND2"; break;
						case T_OR2: type = "OR2"; break;
						case T_NAND2: type = "NAND2"; break;
						case T_NOR2: type = "NOR2"; break;
						case T_XOR2: type = "XOR2"; break;
						case T_XNOR2: type = "XNOR2"; break;
						};
						Cx = (pManager->CompList[i]->m_pGfxInfo->PointsList[0].x + pManager->CompList[i]->m_pGfxInfo->PointsList[1].x) / 2;
						Cy = (pManager->CompList[i]->m_pGfxInfo->PointsList[0].y + pManager->CompList[i]->m_pGfxInfo->PointsList[1].y) / 2;
						myfile << left << setw(10) << type << left << setw(10) << i << left << setw(10) << pManager->CompList[i]->m_Label << left << setw(12) << Cx << left << setw(6) << Cy << endl;


					}
				}

				myfile << ConnCount << endl;
				bool sourceFound = 0, targetFound = 0;

				int S_Comp, T_Comp, DstPin;
				for (int i = 0; i < pManager->CompCount; i++) {

					if (pManager->CompList[i]->ComponentType == T_CONNECTION) {

						int SrcX = pManager->CompList[i]->m_pGfxInfo->PointsList[0].x;
						int SrcY = pManager->CompList[i]->m_pGfxInfo->PointsList[0].y;
						int DestX = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x;
						int DestY = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;

						for (int j = 0; j < pManager->CompCount; j++)
						{
							if (pManager->CompList[j]->ComponentType != T_CONNECTION)
							{

								int x1 = pManager->CompList[j]->m_pGfxInfo->PointsList[0].x;
								int y1 = pManager->CompList[j]->m_pGfxInfo->PointsList[0].y;
								int x2 = pManager->CompList[j]->m_pGfxInfo->PointsList[1].x;
								int y2 = pManager->CompList[j]->m_pGfxInfo->PointsList[1].y;


								switch (pManager->CompList[j]->ComponentType) {
								case T_AND2:
								case T_OR2:
								case T_NAND2:
								case T_NOR2:
								case T_XOR2:
								case T_XNOR2:
								{
									if (SrcX == x2 && SrcY == y2 - 25) {

										S_Comp = j;
										sourceFound = 1;

									}
									else if (DestX == x1 && DestY == y1 + 13) {

										T_Comp = j;
										DstPin = 1;
										targetFound = 1;
									}
									else if (DestX == x1 && DestY == y2 - 13)
									{
										T_Comp = j;
										DstPin = 2;
										targetFound = 1;
									}
									break;
								}
								case T_NOT: {
									if (SrcX == x2 - 1 && SrcY == y2 - 24) {

										S_Comp = j;
										sourceFound = 1;
									}
									else if (DestX == x1 && DestY == y1 + 26)
									{

										T_Comp = j;
										DstPin = 1;
										targetFound = 1;
									}
									break;
								}
								case T_SWITCH:
								{
									if (SrcX == x2 && SrcY == y2 - 25)
									{
										S_Comp = j;
										sourceFound = 1;
									}
									break;
								}
								case T_LED:
								{
									if (DestX == x1 + 15 && DestY == y2 - 8)
									{
										T_Comp = j;
										DstPin = 1;
										targetFound = 1;

									}
									break;
								}

								if (sourceFound == 1 && targetFound == 1)
									break;
								}
							}
						}




						myfile << left << setw(10) << S_Comp << left << setw(10) << T_Comp << left << setw(10) << DstPin << endl;


					}

				}

				myfile.close();
				return 1;

			}

			else return 0;
		
}




