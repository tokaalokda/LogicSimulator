#include "EditConn.h"
#include "..\ApplicationManager.h"
#include "AddConnection.h"

EditConn::EditConn(ApplicationManager* pApp) :Action(pApp)
{
	Type = EDIT_Conn; 
}

EditConn::~EditConn(void)
{
	delete EditAdd; 
}



void EditConn::Execute()
{

	int i = pManager->ReturnSelected(); // The location of the selected array in CompList

	if (i != -1)
	{
		
		//Get a Pointer to the user Interfaces
		UI* pUI = pManager->GetUI();

		if (pManager->CompList[i]->ComponentType == T_CONNECTION)
        {
			pManager->DoneEditConn[pManager->EditConnCount] = new Connection(pManager->CompList[i]->m_pGfxInfo, pManager->CompList[i]->getSourcePin(), pManager->CompList[i]->getDestPin());
			pManager->DoneEditConn[pManager->EditConnCount]->m_Label = pManager->CompList[i]->m_Label; 
			pManager->EditConnPlaces[pManager->EditConnCount++] = i; 

			//Erase connection from UI to clear space for edited one
			pUI->ClearConnection(pManager->CompList[i]->m_pGfxInfo); 
			pUI->LabelComp("               ",
				pManager->CompList[i]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[i]->m_pGfxInfo->PointsList[0].y);

			//Unconnect the destination pin of the removed connection
			
			pManager->CompList[i]->getDestPin()->setStatus(NCON);

			//Destination points of old connection (note: no two connections share a dest. point)
			int oldX = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x; 
			int oldY = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;

			//int to hold the source pin's number of connections
			int Num_Conn = pManager->CompList[i]->getSourcePin()->m_Conn; 

			 //Find the connection in its original source pin's array of connections by comparing dest. points
			for (int j = 0; j < Num_Conn; j++) 
			{
				if (pManager->CompList[i]->getSourcePin()->m_Connections[j]->m_pGfxInfo->PointsList[1].x == oldX
					&& pManager->CompList[i]->getSourcePin()->m_Connections[j]->m_pGfxInfo->PointsList[1].y == oldY)
				{ 
					//Delete connection from source pin's array
					for (int m = j; m < Num_Conn; m++)
						pManager->CompList[i]->getSourcePin()->m_Connections[m] = pManager->CompList[i]->getSourcePin()->m_Connections[m+1];
					break; 
				}
			} 

			//Subtract 1 from number of connections connected to original source pin
			pManager->CompList[i]->getSourcePin()->m_Conn--; 
			if (Num_Conn -1 ==0)
				pManager->CompList[i]->getSourcePin()->setStatus(NCON);
			
			
			
			int pin;
			bool isAvailable;
			
		    //Select new source pin
			do 
			{
				//Print Action Message
				pUI->PrintMsg("Click on the new source pin");

				//Get Center point of the Gate
				pUI->GetPointClicked(srcX, srcY);
				pin = EditAdd->checkPin(srcX, srcY);

				while (pin != 1 && pin != 15 && pin != 16) {
					pUI->PrintMsg("Please click on a valid source pin");
					pUI->GetPointClicked(srcX, srcY);
					pin = EditAdd->checkPin(srcX, srcY);
				}
				
				
				Component* outComp = EditAdd->component;
				if (EditAdd->component->ComponentType != T_Module || (EditAdd->component->ComponentType == T_Module && pin == 15)) {
					outp =EditAdd->component->m_OutputPin;
				}
				else if (EditAdd->component->ComponentType == T_Module && pin == 16)
				{
					int place;
					for (int i = 0; i < pManager->CompCount; i++) {
						if (EditAdd->component->m_pGfxInfo->PointsList[0].x == pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && EditAdd->component->m_pGfxInfo->PointsList[1].x == pManager->CompList[i]->m_pGfxInfo->PointsList[1].x)
							place = i;
					}

					outp = pManager->CompList[place + 1]->m_OutputPin;

				}
				
				EditAdd->connectPin(srcX, srcY, pin); 
				
				EditAdd->component->m_OutputPin->setStatus(LOW);
				pManager->CompList[i]->setSourcePin(outp);
				

			    isAvailable = outp->ConnectTo(pManager->CompList[i]); 

				if (! isAvailable) 
					pUI->PrintMsg("This gate has reached the maximum number of outputs. Select another gate.");
				
			} while (! isAvailable); 
			
			
			
			//Select new destination pin
			isAvailable = 1; 
			do
			{
				pUI->PrintMsg("Connection: Click on the destination pin");
				pUI->GetPointClicked(destX, destY);
				pin = EditAdd->checkPin(destX, destY);

				while (pin != 2 && pin != 3 && pin != 10 && pin != 11 && pin != 12 && pin != 13 && pin != 14) {
					pUI->PrintMsg("Please click on a valid destination pin");
					pUI->GetPointClicked(destX, destY);
					pin = EditAdd->checkPin(destX, destY);
				}

				//Ensures that no other connections are connected to this input pin. 

				destX = EditAdd->pGInfo->PointsList[1].x;
				destY = EditAdd->pGInfo->PointsList[1].y; 

				for (int j = 0; j < i; j++)
				{
					if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
						&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
					{
						isAvailable = 0;
						break;
					}
						
				}
				if (isAvailable == 1) {
					for (int j = i + 1; j < pManager->CompCount; j++)
					{
						if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
							&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
						{
							isAvailable = 0;
							break;
						}
					}
				}

				if(!isAvailable)
					pUI->PrintMsg("This input is already connected. Select another input.");
			} while (!isAvailable);


			EditAdd->connectPin(srcX, srcY, pin);

			if (pin == 2)
			{
				inp = &EditAdd->component->m_InputPins[0];
			}
			if (pin == 3)
			{
				inp = &EditAdd->component->m_InputPins[1];
			}
			if (pin == 10)
			{
				inp = &EditAdd->component->m_InputPins[0];
				EditAdd->component->m_InputPins[0].setStatus(LOW);
			}
			if (pin == 11)
			{
				inp = &EditAdd->component->m_InputPins[1];
				EditAdd->component->m_InputPins[1].setStatus(LOW);
			}
			if (pin == 12)
			{
				inp = &EditAdd-> component->m_InputPins[2];
				EditAdd->component->m_InputPins[2].setStatus(LOW);
			}
			if (pin == 13)
			{
				inp = &EditAdd->component->m_InputPins[3];
				EditAdd->component->m_InputPins[3].setStatus(LOW);
			}
			if (pin == 14)
			{
				inp = &EditAdd-> component->m_InputPins[4];
				EditAdd->component->m_InputPins[4].setStatus(LOW);
			}



				pManager->CompList[i]->setDestPin(inp);
				EditAdd->component->m_InputPins[pin - 2].setStatus(LOW);

				pUI->ClearStatusBar();

				//Change graphics info
				pManager->CompList[i]->m_pGfxInfo = EditAdd->pGInfo;

				
				
				
			
			
		}
		else pUI->PrintMsg("A connection needs to be selected before this action could be performed. \n");
	}

}

void EditConn::Undo()
{}

void EditConn::Redo()
{}

