#include "CUT.h"
#include "..\ApplicationManager.h"

Cut::Cut(ApplicationManager* pApp) :Action(pApp)
{
	 Type = CUT;
}

Cut::~Cut(void)
{
}

void Cut::Execute()
{
	//Resetting Cut's numbers at the beginning of each new cut
	//pManager->CutConnCount = 0;

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	bool found = 0; 

	for (int i = 0; i < pManager->CompCount; i++)
	{
		if (pManager->CompList[i]->selected)
		{
			found = 1; 
			if (pManager->CompList[i]->ComponentType == T_CONNECTION)
			{
				pUI->PrintMsg("Cannot Cut/Paste a Connection. Please select a Component to Cut/Paste.");
				break;
			}

			Cutitm = pManager->CompList[i];

			pUI->ClearComponent(Cutitm->m_pGfxInfo);

			pUI->LabelComp("            ", Cutitm->m_pGfxInfo->PointsList[0].x, Cutitm->m_pGfxInfo->PointsList[0].y);

			pUI->PrintMsg("You cut the selected component. Click where you'd like to paste.");

			//Finding connections to clear them

			//For the connections of the output pin and the 1st input pin.
			GraphicsInfo* pGInfo1 = new GraphicsInfo(2);

			//For the connections of the output pin and the 2nd and further input pin, if exists.
			GraphicsInfo* pGInfo2 = new GraphicsInfo(2);
			GraphicsInfo* pGInfo3 = new GraphicsInfo(2);
			GraphicsInfo* pGInfo4 = new GraphicsInfo(2);

			//Setting the points
			int x1 = Cutitm->m_pGfxInfo->PointsList[0].x;
			int y1 = Cutitm->m_pGfxInfo->PointsList[0].y;
			int x2 = Cutitm->m_pGfxInfo->PointsList[1].x;
			int y2 = Cutitm->m_pGfxInfo->PointsList[1].y;
			int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;

			//To set the pGInfos

			switch (Cutitm->ComponentType)
			{
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
				//For all components with 2 pins we'll use the two pGInfos:

				pGInfo1->PointsList[0].x = x2;
				pGInfo1->PointsList[0].y = y2 - 25;
				pGInfo1->PointsList[1].x = x1;
				pGInfo1->PointsList[1].y = y2 - 13;

				pGInfo2->PointsList[0].x = x2;
				pGInfo2->PointsList[0].y = y2 - 25;
				pGInfo2->PointsList[1].x = x1;
				pGInfo2->PointsList[1].y = y1 + 13;

				break;

			case T_NOT:

				pGInfo1->PointsList[0].x = x2 - 1;
				pGInfo1->PointsList[0].y = y2 - 24;
				pGInfo1->PointsList[1].x = x1;
				pGInfo1->PointsList[1].y = y1 + 26;

				break;

			case T_SWITCH:

				pGInfo1->PointsList[0].x = x2;
				pGInfo1->PointsList[0].y = y2 - 25;

				break;

			case T_LED:

				pGInfo1->PointsList[1].x = x1 + 15;
				pGInfo1->PointsList[1].y = y2 - 8;
				break;

			case T_Module:
				pGInfo1->PointsList[0].x = x1;
				pGInfo1->PointsList[0].y = y1 + 13;
				pGInfo1->PointsList[1].x = x1;
				pGInfo1->PointsList[1].y = y1 + 33;

				pGInfo2->PointsList[0].x = x1;
				pGInfo2->PointsList[0].y = y1 + 55;
				pGInfo2->PointsList[1].x = x1;
				pGInfo2->PointsList[1].y = y1 + 71;

				pGInfo3->PointsList[0].x = x1;
				pGInfo3->PointsList[0].y = y2 - 10;
				pGInfo3->PointsList[1].x = x2;
				pGInfo3->PointsList[1].y = y1 + 25;

				pGInfo4->PointsList[0].x = x2;
				pGInfo4->PointsList[0].y = y2 - 34;

				break;
			}

			//Finding the connections associated with the cut component and removing them

			int c = 0;
			for (int n = 0; n < pManager->CompCount; n++)
			{
				if (pManager->CompList[n]->ComponentType == T_CONNECTION)
				{
					if ((Cutitm->ComponentType != T_LED) && (Cutitm->ComponentType != T_SWITCH))
					{
						if (((pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo1->PointsList[0].x)
							&& (pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo1->PointsList[0].y))
							|| ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[1].x)
								&& (pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[1].y))
							|| ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo2->PointsList[1].x)
								&& (pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo2->PointsList[1].y)))
						{
							int oldX = pManager->CompList[n]->m_pGfxInfo->PointsList[1].x;
							int oldY = pManager->CompList[n]->m_pGfxInfo->PointsList[1].y;

							OutputPin* Src = pManager->CompList[n]->getSourcePin();
							InputPin* Dst = pManager->CompList[n]->getDestPin();

							int num = Src->m_Conn;
							Src->m_Conn--;

							for (int j = 0; j < num; j++)
							{
								if (Src->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
									&& Src->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
								{
									//Delete connection from source pin's array
									for (int m = j; m < num; m++)
										Src->m_Connections[m] = Src->m_Connections[m + 1];
									break;
								}
							}

							if (num - 1 == 0) //Source pin is only freed from last connection
							{
								Src->setStatus(NCON);
							}

							Dst->setStatus(NCON); //Freeing the associated destination pin to the connection

							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							//pManager->CutConn[pManager->CutConnCount++] = pManager->CompList[n];
							pManager->CompList[n] = NULL;
							c = c + 1;
						}
					}
					else if (Cutitm->ComponentType == T_Module)
					{
						if ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[0].x &&
							pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[0].y)
							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[1].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[1].y)

							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo2->PointsList[0].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo2->PointsList[0].y)

							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo2->PointsList[1].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo2->PointsList[1].y)

							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo3->PointsList[0].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo3->PointsList[0].y)
							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo3->PointsList[1].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo3->PointsList[1].y)

							|| (pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo4->PointsList[0].x &&
								pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo4->PointsList[0].y))
						{
							int oldX = pManager->CompList[n]->m_pGfxInfo->PointsList[1].x;
							int oldY = pManager->CompList[n]->m_pGfxInfo->PointsList[1].y;

							OutputPin* Src = pManager->CompList[n]->getSourcePin();
							InputPin* Dst = pManager->CompList[n]->getDestPin();

							int num = Src->m_Conn;
							Src->m_Conn--;

							for (int j = 0; j < num; j++)
							{
								if (Src->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
									&& Src->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
								{
									//Delete connection from source pin's array
									for (int m = j; m < num; m++)
										Src->m_Connections[m] = Src->m_Connections[m + 1];
									break;
								}
							}

							if (num - 1 == 0) //Source pin is only freed from last connection
							{
								Src->setStatus(NCON);
							}

							Dst->setStatus(NCON); //Freeing the associated destination pin to the connection

							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							//pManager->DelConn[pManager->DelConnCount++] = pManager->CompList[n];
							pManager->CompList[n] = NULL;
							c = c + 1;
						}
					}

					else if (Cutitm->ComponentType != T_LED)
					{
						if (((pManager->CompList[n]->m_pGfxInfo->PointsList[0].x == pGInfo1->PointsList[0].x)
							&& (pManager->CompList[n]->m_pGfxInfo->PointsList[0].y == pGInfo1->PointsList[0].y)))
						{
							int oldX = pManager->CompList[n]->m_pGfxInfo->PointsList[1].x;
							int oldY = pManager->CompList[n]->m_pGfxInfo->PointsList[1].y;

							OutputPin* Src = pManager->CompList[n]->getSourcePin();
							InputPin* Dst = pManager->CompList[n]->getDestPin();

							int num = Src->m_Conn;
							Src->m_Conn--;

							for (int j = 0; j < num; j++)
							{
								if (Src->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
									&& Src->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
								{
									//Delete connection from source pin's array
									for (int m = j; m < num; m++)
										Src->m_Connections[m] = Src->m_Connections[m + 1];
									break;
								}
							}

							if (num - 1 == 0) //Source pin is only freed from last connection
							{
								Src->setStatus(NCON);
							}

							Dst->setStatus(NCON); //Freeing the associated destination pin to the connection

							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							//pManager->CutConn[pManager->CutConnCount++] = pManager->CompList[n];
							pManager->CompList[n] = NULL;
							c = c + 1;
						}
					}
					else if (Cutitm->ComponentType != T_SWITCH)
					{
						if ((pManager->CompList[n]->m_pGfxInfo->PointsList[1].x == pGInfo1->PointsList[1].x) &&
							(pManager->CompList[n]->m_pGfxInfo->PointsList[1].y == pGInfo1->PointsList[1].y))
						{
							int oldX = pManager->CompList[n]->m_pGfxInfo->PointsList[1].x;
							int oldY = pManager->CompList[n]->m_pGfxInfo->PointsList[1].y;

							OutputPin* Src = pManager->CompList[n]->getSourcePin();
							InputPin* Dst = pManager->CompList[n]->getDestPin();

							int num = Src->m_Conn;
							Src->m_Conn--;

							for (int j = 0; j < num; j++)
							{
								if (Src->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
									&& Src->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
								{
									//Delete connection from source pin's array
									for (int m = j; m < num; m++)
										Src->m_Connections[m] = Src->m_Connections[m + 1];
									break;
								}
							}

							if (num - 1 == 0) //Source pin is only freed from last connection
							{
								Src->setStatus(NCON);
							}

							Dst->setStatus(NCON); //Freeing the associated destination pin to the connection

							pUI->ClearConnection(pManager->CompList[n]->m_pGfxInfo);
							//pManager->CutConn[pManager->CutConnCount++] = pManager->CompList[n];
							pManager->CompList[n] = NULL;
							c = c + 1;
						}
					}
				}
			}

			//pManager->CutpGInf = pManager->CompList[i]->m_pGfxInfo;

			if (pManager->CompList[i]->ComponentType != T_Module) {
				pManager->CompList[i] = NULL;

				int k = 0;
				for (int j = 0; j < pManager->CompCount; j++)
				{
					if (pManager->CompList[j] != NULL)
					{
						pManager->CompList[k] = pManager->CompList[j];
						k = k + 1;
					}
				}

				pManager->CompCount = pManager->CompCount - c ;


				//Setting new position to paste a component

				int x, y;

				pUI->GetPointClicked(x, y); //Coordinates for copy's center

				int gateWidth = pUI->getGateWidth();
				int gateHeight = pUI->getGateHeight();

				//Graphics info to construct the copy
				GraphicsInfo* pGInfo = new GraphicsInfo(2);

				pGInfo->PointsList[0].x = x - gateWidth / 2;
				pGInfo->PointsList[0].y = y - gateHeight / 2;
				pGInfo->PointsList[1].x = x + gateWidth / 2;
				pGInfo->PointsList[1].y = y + gateHeight / 2;

				//Cases of pasting on the tool bar or status bar

				if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight || pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
				{
					if (pGInfo->PointsList[0].y - 25 < pUI->ToolBarHeight)
						pUI->PrintMsg("You cannot paste the component on the toolbar. Action aborted.");

					if (pGInfo->PointsList[1].y > pUI->height - pUI->StatusBarHeight)
						pUI->PrintMsg("You cannot paste the component on the status bar. Action aborted.");

					pManager->Done_Acts[pManager->executed] = NI;
					pManager->executed--;
					break;
				}

				else
				{
					//pManager->CutItem = Cutitm; //Setting pointer CutItem to the old cut item with its old position

					Cutitm->m_pGfxInfo = pGInfo;
					pManager->CompList[pManager->CompCount - 1] = Cutitm;
					if ((pManager->CompList[pManager->CompCount - 1]->ComponentType == T_LED) ||
						(pManager->CompList[pManager->CompCount - 1]->ComponentType == T_SWITCH))
					{
						Label temp(pManager);
						temp.Execute();
					}
					pManager->UnselectAll();
					//pManager->Done_Acts[pManager->executed-1] = CUT;
					pUI->PrintMsg("Cut component pasted successfully.");
					break;
				}
			}
			else if (pManager->CompList[i]->ComponentType == T_Module)
			{

				for (int m = i - 72; m < i + 2; m++)
					pManager->CompList[m] = NULL;

				int k = 0;
				for (int j = 0; j < pManager->CompCount; j++)
				{
					if (pManager->CompList[j] != NULL)
					{
						pManager->CompList[k] = pManager->CompList[j];
						k = k + 1;
					}
				}

				pManager->CompCount = pManager->CompCount - c ;

				CUTDef->Execute(); 

				k = 0; 
				for (int j = 0; j < pManager->CompCount; j++)
				{
					if (pManager->CompList[j] != NULL)
					{
						pManager->CompList[k] = pManager->CompList[j];
						k = k + 1;
					}
				}

				pManager->CompCount = pManager->CompCount - 74; 

				
					for (int i = pManager->CompCount - 74; i < pManager->CompCount - 2; i++)
					{
						pManager->CompList[i]->inModule = 1;
						if (pManager->CompList[i]->ComponentType != T_CONNECTION) {
							pManager->CompList[i]->m_OutputPin->setStatus(LOW);
							if (pManager->CompList[i]->ComponentType == T_NOT)
								pManager->CompList[i]->m_InputPins[0].setStatus(LOW);
						}

					}

				
				pUI->PrintMsg("Cut component pasted successfully.");

			}

		}

		
	}
	//In case no component is selected for cutting
	if (!found )
	{
		pUI->PrintMsg("Nothing is selected. Please select a component to cut.");
	}
}

