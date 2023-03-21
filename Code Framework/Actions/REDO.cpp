#include "REDO.h"

Redo::Redo(ApplicationManager* pApp) :Action(pApp) {};

Redo::~Redo(void) {
	delete RSave; 
	delete RLoad; 
};

void Redo::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->Undone_count > 0)
	{
	  //Print Action Message
	  pUI->PrintMsg("You clicked on Redo.");

	    ActionType t1 = pManager->Undone_Acts[pManager->Undone_count - 1];

		pManager->Done_Acts[pManager->executed] = pManager->Undone_Acts[pManager->Undone_count-1];
		pManager->Undone_Acts[pManager->Undone_count-1] = NI;
		pManager->Undone_count--;
		pManager->executed++;

		if (t1 == ADD_COMP || t1 == ADD_CONNECTION) {

			pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[pManager->undone_Compcount - 1];
			pManager->Undone_Comps[pManager->undone_Compcount - 1] = NULL;
			pManager->CompCount++;
			pManager->undone_Compcount--;
		}

		else if (t1 == LOAD) {

			string TempName = "ProgramTXTfiles\\temporaryloadtype1file";
			TempName += to_string(pManager->LoadCount);
			TempName += ".txt";
			RSave->ExecutePart(TempName,pUI);

			pManager->UndoneLoadCount--;
			pManager->LoadCount++;

			string TempName2 = "ProgramTXTfiles\\temporaryloadtype2file";
			int number = pManager->UndoneLoadCount;
			TempName2 += to_string(number);
			TempName2 += ".txt";
			bool y = RLoad->ExecutePart(TempName2, pUI, 0);


		}

		else if (t1 == EDIT_Conn)
		{
			pManager->DoneEditConn[pManager->EditConnCount] = new Connection(pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->m_pGfxInfo, pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->getSourcePin(), pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->getDestPin());

			pUI->ClearConnection(pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount]]->m_pGfxInfo);

			pManager->DoneEditConn[pManager->EditConnCount]->m_Label = pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->m_Label;

			pUI->LabelComp("               ",
				pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->m_pGfxInfo->PointsList[0].x,
				pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount ]]->m_pGfxInfo->PointsList[0].y);

			
			pManager->EditConnCount++;

			pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount-1]] = new Connection(pManager->UndoneEditConn[pManager->UndoneEditConnCount - 1]->m_pGfxInfo, pManager->UndoneEditConn[pManager->UndoneEditConnCount - 1]->getSourcePin(), pManager->UndoneEditConn[pManager->UndoneEditConnCount - 1]->getDestPin());

			pManager->CompList[pManager->EditConnPlaces[pManager->EditConnCount-1]]->m_Label = pManager->UndoneEditConn[pManager->UndoneEditConnCount - 1]->m_Label;

			pManager->UndoneEditConnCount--;
			
		}

		else if (t1 == NamedMODULE) 
		{
			for (int i = 0; i < pManager->UndoneModuleCompCount[pManager->UndoneModuleCount - 1]; i++) {
				pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[pManager->undone_Compcount - 1];
				pManager->Undone_Comps[pManager->undone_Compcount - 1] = NULL;
				pManager->CompCount++;
				pManager->undone_Compcount--;
			}
			pManager->ModuleCount++;
			pManager->UndoneModuleCount--;
			pManager->ModuleCompCount[pManager->ModuleCount - 1] = pManager->UndoneModuleCompCount[pManager->UndoneModuleCount];
			pManager->UndoneModuleCompCount[pManager->UndoneModuleCount] = 0;

		}
		else if (t1 == DefMODULE)
		{
			int OldUndoneCount = pManager->undone_Compcount; 
			for (int i = OldUndoneCount - 74; i < OldUndoneCount; i++)
			{
				pManager->CompList[pManager->CompCount] = pManager->Undone_Comps[i];
				pManager->Undone_Comps[i] = NULL;
				pManager->CompCount++;
				pManager->undone_Compcount--;

			}

		}

		
	}
	else
	{
		pUI->PrintMsg("You cannot redo unless you have undone something!");
	}

}