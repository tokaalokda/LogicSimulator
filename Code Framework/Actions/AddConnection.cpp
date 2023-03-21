#include "AddConnection.h"



AddConnection::AddConnection(ApplicationManager * pApp) :Action(pApp)
{
  Type = ADD_CONNECTION;
}

AddConnection::~AddConnection(void)
{
}

//The next commented part is supposed to be a function that returns whether the user clicks in empty space, input pin or output pin
//The problem is that pins are not defined for all components so one possible solution is to add the pins to the Component Class
//Another problem is to differentiate between input and output pins and to make sure no 2 inputs or outputs are connected to eachother cuz thats gay

int AddConnection::checkPin(int x, int y) {
	for (int i = 0; i < pManager->CompCount; i++) {


		int x1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].x;
		int y1 = pManager->CompList[i]->m_pGfxInfo->PointsList[0].y;
		int x2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].x;
		int y2 = pManager->CompList[i]->m_pGfxInfo->PointsList[1].y;
		if (x > x1 && x < x2 && y > y1 && y < y2)
		{
			component = pManager->CompList[i];

			int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2; 
			int xdiff = x2 - x1, ydiff = y2 - y1;
			switch (component->ComponentType) {
			case T_AND2:
			case T_OR2:
			case T_NAND2:
			case T_NOR2:
			case T_XOR2:
			case T_XNOR2:
			{
				if (x > xhalf) {

					return 1;
				}
				else if (y > yhalf) {

					return 2;
				}
				else
				{
					return 3;
				}
			}
			case T_NOT: {
				if (x > xhalf) {

					return 1;
				}
				else
				{
					return 2;
				}
			}
			case T_SWITCH:
			{
				return 1;
			}
			case T_LED:
			{
				return 2;
			}
			case T_Module:
			{
				if (x < xhalf && y < (y1 + 0.2* ydiff)) {

					return 10;
				}
				else if (x < xhalf && y < (y1 + 0.4 * ydiff)) {

					return 11;
				}
				else if (x < xhalf && y < (y1 + 0.6 * ydiff)) {

					return 12;
				}
				else if (x < xhalf && y <( y1 + 0.8 * ydiff)) {

					return 13;
				}
				else if (x < xhalf && y < (y1 +  ydiff)) {

					return 14;
				}
				else if (x > xhalf && y < yhalf) {

					return 15;
				}
				else  if (x > xhalf && y > yhalf)
				{
					return 16;
				}
				break; 
			}

			}
		}
	}
	return 0;
}


void AddConnection::connectPin(int x, int y, int r) {

	int x1 = component->m_pGfxInfo->PointsList[0].x;
	int y1 = component->m_pGfxInfo->PointsList[0].y;
	int x2 = component->m_pGfxInfo->PointsList[1].x;
	int y2 = component->m_pGfxInfo->PointsList[1].y;
	int xhalf = (x2 + x1) / 2, yhalf = (y2 + y1) / 2; 
	int xdiff = x2 - x1, ydiff = y2 - y1;

	switch (component->ComponentType) {
	case T_AND2:
	case T_OR2:
	case T_NAND2:
	case T_NOR2:
	case T_XOR2:
	case T_XNOR2:
	{
		if (r == 1) {
			pGInfo->PointsList[0].x = x2;
			pGInfo->PointsList[0].y = y2 - 25;
		}
		else if (r == 2) {
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y2 - 13;
		}
		else
		{
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 13;
		}
		break;
	}
	case T_NOT: {
		if (r == 1) {
			pGInfo->PointsList[0].x = x2 - 1;
			pGInfo->PointsList[0].y = y2 - 24;
		}
		else
		{
			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 26;
		}
		break;
	}
	case T_SWITCH:
	{
		pGInfo->PointsList[0].x = x2;
		pGInfo->PointsList[0].y = y2 - 25;
		break;
	}
	case T_LED:
	{
		pGInfo->PointsList[1].x = x1 + 15;
		pGInfo->PointsList[1].y = y2 - 8;
		break;
	}
	case T_Module:
	{
		if (r ==10 ){

			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 13;
			
		}
		else if (r ==11) {

		    pGInfo->PointsList[1].x = x1;
		    pGInfo->PointsList[1].y = y1 + 33;
		}
		else if (r ==12) {
		
			pGInfo->PointsList[1].x = x1;
		    pGInfo->PointsList[1].y = y1 + 55;
		}
		else if (r ==13) {

			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y1 + 71;
		}
		else if (r == 14) {

			pGInfo->PointsList[1].x = x1;
			pGInfo->PointsList[1].y = y2 - 10; 
		}
		else if (r == 15) {

			pGInfo->PointsList[0].x = x2;
			pGInfo->PointsList[0].y = y1 + 25;
		}
		else if (r == 16)
		{
			pGInfo->PointsList[0].x = x2;
			pGInfo->PointsList[0].y = y2 - 34;
		}
		break;
	}
	}

}



void AddConnection::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Connection: Click on the source pin");

	//Get Center point of the Gate
	pUI->GetPointClicked(srcX, srcY);
	pin = checkPin(srcX, srcY);

	while (pin != 1 && pin != 15 && pin != 16) {
		pUI->PrintMsg("Please click on a valid source pin");
		pUI->GetPointClicked(srcX, srcY);
		pin = checkPin(srcX, srcY);
	}

	connectPin(srcX, srcY, pin);
	Component* outComp = component;
	if (component->ComponentType != T_Module || (component->ComponentType == T_Module && pin == 15)) {
		outp = component->m_OutputPin;
	}
	else if (component->ComponentType == T_Module && pin == 16)
	{
		int place;
		for (int i = 0; i < pManager->CompCount; i++) {
			if (component ->m_pGfxInfo->PointsList[0].x == pManager->CompList[i]->m_pGfxInfo->PointsList[0].x && component ->m_pGfxInfo->PointsList[1].x == pManager->CompList[i]->m_pGfxInfo->PointsList[1].x)
				place = i;
		}

		outp = pManager->CompList[place + 1]->m_OutputPin;

	}
	

	pUI->PrintMsg("Connection: Click on the destination pin");
	pUI->GetPointClicked(destX, destY);
	pin = checkPin(destX, destY);

	while (pin != 2 && pin != 3 && pin != 10 && pin != 11 && pin != 12 && pin != 13 && pin != 14) {
		pUI->PrintMsg("Please click on a valid destination pin");
		pUI->GetPointClicked(destX, destY);
		pin = checkPin(destX, destY);
	}

	connectPin(srcX, srcY, pin);

	Component* inComp = component;

	if (pin == 2)
	{		
		inp = &component->m_InputPins[0];
	}
	if (pin == 3)
	{
		inp = &component->m_InputPins[1];
	}
	if (pin == 10)
	{
		inp = &component->m_InputPins[0];
		component->m_InputPins[0].setStatus(LOW);
	}
	if (pin == 11)
	{
		inp = &component->m_InputPins[1];
		component->m_InputPins[1].setStatus(LOW);
	}
	if (pin == 12)
	{
		inp = &component->m_InputPins[2];
		component->m_InputPins[2].setStatus(LOW);
	}
	if (pin == 13)
	{
		inp = &component->m_InputPins[3];
		component->m_InputPins[3].setStatus(LOW);
	}
	if (pin == 14)
	{
		inp = &component->m_InputPins[4];
		component->m_InputPins[4].setStatus(LOW);
	}
	

	pUI->ClearStatusBar();

	destX = pGInfo->PointsList[1].x;
	destY = pGInfo->PointsList[1].y;


	//Check that no other connections are connected to destination pin
	bool isDestAvailable = 1;
	for (int j = 0; j < pManager->CompCount; j++)
	{
		if (destX == pManager->CompList[j]->m_pGfxInfo->PointsList[1].x
			&& destY == pManager->CompList[j]->m_pGfxInfo->PointsList[1].y)
		{
			isDestAvailable = 0;
			break;
		}
	}



	if (isDestAvailable)
	{
		Connection* pC = new Connection(pGInfo, outp, inp);
		if (!outp->ConnectTo(pC)) {
			pUI->PrintMsg("Connection failed: Source gate has reached the maximum number of outputs.");
		}
		else
			pManager->AddComponent(pC);

			outComp->m_OutputPin->setStatus(LOW);
			if (inComp->ComponentType!= T_Module)
			inComp->m_InputPins[pin - 2].setStatus(LOW);
	}
	else pUI->PrintMsg("Connection failed: Destination gate already has an input.");
}