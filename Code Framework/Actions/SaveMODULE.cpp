#include "SaveMODULE.h"
#include "..\ApplicationManager.h"
#include <istream>


SaveModule::SaveModule(ApplicationManager* pApp) :Action(pApp) {};

SaveModule::~SaveModule(void) {
	delete MSave;
	delete[] ModuleNames; 
};

void SaveModule::Execute()
{
	
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	if (pManager->CompCount != 0)
	{

		int ModuleCount;
		 
		

		string file = "ProgramTXTfiles\\ModuleCount.txt";

		ifstream infile(file.c_str());
		infile >> ModuleCount;
		infile.close();

		ModuleNames = new string[ModuleCount];

		string trash; 

		string file2 = "ProgramTXTfiles\\ModuleInfo.txt";

		ifstream infile2(file2.c_str()); 
		getline(infile2, trash);

		for (int i = 0; i < ModuleCount; i++) 
		{
			getline(infile2, ModuleNames[i]);
			getline(infile2, trash ); 
			
		}
		infile2.close(); 
				 
				
		//Get module name Message
		pUI->PrintMsg("SAVE as Module: Type in your module's name. Click enter when done.\n");
		name = pUI->GetString();
		

		bool unique = 1;

		
		for (int i = 0; i < ModuleCount; i++) {
			if (name == ModuleNames[i])
				unique = 0;
		}

					   	

		while (!unique || name.length() > 10 || name == "" || name == " " || name == "  " || name == "   " || name == "    " || name == "     " || name == "      " || name == "       " || name == "        " || name == "         " || name == "          ")
		{ 
			
			while (name.length() > 10)
			{
				pUI->PrintMsg("Please enter a string less than ELEVEN characters.");
				name = pUI->GetString();
			}
			
						
			do {
				unique = 1;
				for (int k = 0; k < ModuleCount; k++) {
					if (name == ModuleNames[k])
						unique = 0;
				}

				if (!unique)
				{
					pUI->PrintMsg("This name was used by another module. Please enter a unique name.");
					name = pUI->GetString();
				}

			} while (!unique);


			while (name == "" || name == " " || name == "  " || name == "   " || name == "    " || name == "     " || name == "      " || name == "       " || name == "        " || name == "         " || name == "          ")
			{
			  pUI->PrintMsg("Please enter a nonempty string.");
			  name = pUI->GetString();
			} 

		
		
		
		}

		do {
			unique = 1;
			for (int k = 0; k < ModuleCount; k++) {
				if (name == ModuleNames[k])
					unique = 0;
			}

			if (!unique)
			{
				pUI->PrintMsg("This name was used by another module. Please enter a unique name.");
				name = pUI->GetString();
			}

		} while (!unique);

		//Get module description
		pUI->PrintMsg("SAVE as Module: Type in your module's description. Max size: 100 Characters. Click enter when done.\n");
		description = pUI->GetString();
		while (description.length() > 100)
		{
			pUI->PrintMsg("Please enter a string less than 101 characters!");
			name = pUI->GetString();
		}

		ofstream outfile2; 
		outfile2.open(file2.c_str(), ios::app); 
		outfile2 <<  name << endl  << description << endl; 
		outfile2.close(); 

		
		string TempName = "ProgramTXTfiles\\Modulefile";
		TempName += to_string(ModuleCount);
		TempName += ".txt";
		MSave->ExecutePart(TempName, pUI);

		pUI->PrintMsg("Module saved!");
		
		ModuleCount++;

		ofstream outfile(file.c_str());
		outfile << ModuleCount;
		outfile.close();

	}
	else pUI->PrintMsg("Please draw a circuit before you try to save a module.\n");


}