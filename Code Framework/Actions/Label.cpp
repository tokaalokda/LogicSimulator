#include "Label.h"
#include "..\ApplicationManager.h"

Label::Label(ApplicationManager * pApp) :Action(pApp)
{
	Type = NI;
}

Label::~Label(void)
{
}

Component* Label::getComponentLabeled() {
	return component;
}

void Label::Execute()
{

	int i = pManager->ReturnSelected(); // The location of the selected array in CompList

	if (i != -1) {

		//Get a Pointer to the user Interfaces
		UI* pUI = pManager->GetUI();

		component = pManager->CompList[i];

		string Label;

		if (component->ComponentType != T_SWITCH && component->ComponentType != T_LED)
			//Print Action Message
			pUI->PrintMsg("Type in a label other than '-' then click ENTER.");


		if (component->ComponentType == T_LED)
			pUI->PrintMsg("All LEDs must have labels at all times. Please type in a nonempty label other than '-' then click ENTER.");
		if (component->ComponentType == T_SWITCH)
			pUI->PrintMsg("All switches must have labels at all times. Please type in a nonempty label other than '-' then click ENTER.");



		Label = pUI->GetString();


		while (Label == "-" || Label.length() > 10)
		{
			while (Label.length() > 10)
			{
				pUI->PrintMsg("Please enter a string less than ELEVEN characters!");
				Label = pUI->GetString();
			}

			while (Label == "-")
			{
				pUI->PrintMsg("This string is reserved by the program. Please enter a different label.");
				Label = pUI->GetString();
			}
		}






		if (pManager->CompList[i]->ComponentType == T_SWITCH || pManager->CompList[i]->ComponentType == T_LED) {

			bool unique = 1;
			for (int k = 0; k < pManager->CompCount; k++) {
				if ((pManager->CompList[k]->ComponentType == T_SWITCH || pManager->CompList[k]->ComponentType == T_LED) && Label == pManager->CompList[k]->m_Label)
					unique = 0;
			}

			while (!unique || Label.length() > 10 || Label == "-" || Label == "" || Label == " " || Label == "  " || Label == "   " || Label == "    " || Label == "     " || Label == "      " || Label == "       " || Label == "        " || Label == "         " || Label == "          ")
			{

				while (Label.length() > 10)
				{
					pUI->PrintMsg("Please enter a string less than ELEVEN characters!");
					Label = pUI->GetString();
				}

				while (Label == "" || Label == " " || Label == "  " || Label == "   " || Label == "    " || Label == "     " || Label == "      " || Label == "       " || Label == "        " || Label == "         " || Label == "          ")
				{
					pUI->PrintMsg("Switches and LEDs must have valid labels at all times. Please enter a nonempty label other than '-'.");
					Label = pUI->GetString();
				}

				while (Label == "-")
				{
					pUI->PrintMsg("This string is reserved by the program. Please enter a different label.");
					Label = pUI->GetString();
				}

				do {
					unique = 1;
					for (int k = 0; k < pManager->CompCount; k++) {
						if ((pManager->CompList[k]->ComponentType == T_SWITCH || pManager->CompList[k]->ComponentType == T_LED) && Label == pManager->CompList[k]->m_Label)
							unique = 0;
					}

					if (!unique)
					{
						pUI->PrintMsg("Switches and LEDs must have unique labels. Please pick a label not used by another switch or LED.");
						Label = pUI->GetString();
					}

				} while (!unique);
			}


		}



		if (Label == "" || Label == " " || Label == "  " || Label == "   " || Label == "    " || Label == "     " || Label == "      " || Label == "       " || Label == "        " || Label == "         " || Label == "          ")
		{		
		 pManager->CompList[i]->m_Label = "-";
		 pUI->LabelComp("          ",
			pManager->CompList[i]->m_pGfxInfo->PointsList[0].x,
			pManager->CompList[i]->m_pGfxInfo->PointsList[0].y);
	    }
		else 
		    pManager->CompList[i]->m_Label = Label;

		pManager->CompList[i]->selected = 0; 


		//Clear Status Bar
		pUI->ClearStatusBar();
	}
}
