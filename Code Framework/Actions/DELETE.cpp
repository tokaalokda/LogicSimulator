#include "DELETE.h"
#include "..\ApplicationManager.h"
#include "SELECT.h"

Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
	Type = DEL;
}

Delete::~Delete(void)
{

}

void Delete::Execute()
{
	//pManager->delcount = 0;
	//pManager->DelConnCount = 0;

	//Resetting delete's numbers at the beginning of each delete

	UI* pUI = pManager->GetUI();

	bool found = 0; 

	for (int i = 0; i < pManager->CompCount; i++)
	{
		if (pManager->CompList[i]->selected)
		{
			found = 1;
			if (pManager->CompList[i]->ComponentType != T_CONNECTION)
			{
				 
				pUI->ClearComponent(pManager->CompList[i]->m_pGfxInfo);
				deleted = pManager->CompList[i];
				//pManager->Deltd[pManager->delcount++] = deleted;
				pUI->LabelComp("            ", deleted->m_pGfxInfo->PointsList[0].x, deleted->m_pGfxInfo->PointsList[0].y);
				//Finding connections to clear them

                //For the connections of the output pin and the 1st input pin.
				GraphicsInfo* pGInfo1 = new GraphicsInfo(2);

				//For the connections of the output pin and the 2nd and further input pin, if exists.
				GraphicsInfo* pGInfo2 = new GraphicsInfo(2);
				GraphicsInfo* pGInfo3 = new GraphicsInfo(2);
				GraphicsInfo* pGInfo4 = new GraphicsInfo(2);
				

				//Setting the points
				int x1 = deleted->m_pGfxInfo->PointsList[0].x;
				int y1 = deleted->m_pGfxInfo->PointsList[0].y;
				int x2 = deleted->m_pGfxInfo->PointsList[1].x;
				int y2 = deleted->m_pGfxInfo->PointsList[1].y;
				int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2;

				//To set the pGInfos

				switch (deleted->ComponentType)
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
					pGInfo1->PointsList[0].y = y1 +13;
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

				//Finding the connections associated with the deleted component and removing them

				int c = 0;

				for (int n = 0; n < pManager->CompCount; n++)
				{
					if (pManager->CompList[n]->ComponentType == T_CONNECTION)
					{
						if ((deleted->ComponentType != T_LED) && (deleted->ComponentType != T_SWITCH) && deleted->ComponentType != T_Module)
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
								//pManager->DelConn[pManager->DelConnCount++] = pManager->CompList[n];
								pManager->CompList[n] = NULL;
								c = c + 1;
							}
						}
						else if (deleted->ComponentType == T_Module)
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
						else if (deleted->ComponentType != T_LED)
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
								//pManager->DelConn[pManager->DelConnCount++] = pManager->CompList[n];
								pManager->CompList[n] = NULL;
								c = c + 1;
							}
						}
						else if (deleted->ComponentType != T_SWITCH)
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
								//pManager->DelConn[pManager->DelConnCount++] = pManager->CompList[n];
								pManager->CompList[n] = NULL;
								c = c + 1;
							}
						}
					}
				}

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

					pManager->CompList[pManager->CompCount - c - 1] = NULL;
					pManager->CompCount = pManager->CompCount - c - 1;
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

					pManager->CompCount = pManager->CompCount - c - 74;

				}

				i = -1; //Resetting the loop because complist was resorted

				//Print Action Message

				pUI->PrintMsg("You deleted the selected component.");

				//pManager->delcount = pManager->delcount + 1;
			}

			else if (pManager->CompList[i]->ComponentType == T_CONNECTION)
			{
				pUI->ClearConnection(pManager->CompList[i]->m_pGfxInfo);
				deleted = pManager->CompList[i];
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

				pManager->CompList[pManager->CompCount-1] = NULL;
				pManager->CompCount = pManager->CompCount - 1;

				i = -1; //Resetting the loop because complist was resorted

				//pManager->delcount = pManager->delcount + 1;
				//Print Action Message

				pUI->PrintMsg("You deleted the selected connection.");
			}
			pUI->PrintMsg("You deleted the selected component(s).");
		}
		
	}
	if (!found)
	{
		pUI->PrintMsg("Nothing is selected. Please select a component to delete.");
	}
}

