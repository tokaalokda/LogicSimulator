#include "TruthTable.h"

TruthTable::TruthTable(ApplicationManager* pApp) : Action(pApp) {

}

TruthTable::~TruthTable(void){

}

bool isAllStable(STATUS* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == NCON) return 0;
	}
	return 1;
}


bool isAllHigh(STATUS* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] != HIGH) return 0;
	}
	return 1;
}

bool AddOne(STATUS* arr, int size) {
	if (isAllHigh(arr, size) == 1) return 0;
	arr[size - 1] = (STATUS)(arr[size - 1] + 1);
	while (!isAllStable(arr, size)) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == NCON) {
				arr[i] = LOW;
				arr[i - 1] = (STATUS)(arr[i - 1] + 1);
			}
		}
	}
	return 1;
}



void TruthTable::Execute() {
	int s_num = 0, l_num = 0;
	for (int i = 0; i < pManager->CompCount; i++) {
		if (pManager->CompList[i]->ComponentType == T_SWITCH) {
			AllSwitches[s_num] = pManager->CompList[i];
			s_num++;
		}
		else if (pManager->CompList[i]->ComponentType == T_LED) {
			AllLEDs[l_num] = pManager->CompList[i];
			l_num++;
		}
	}
	
	STATUS* currentStat = new STATUS[s_num];
	for (int i = 0; i < s_num; i++) {
		currentStat[i] = AllSwitches[i]->isON;
	}

	STATUS* inputs = new STATUS[s_num];
	STATUS** AllInputs;
	AllInputs = new STATUS * [pow(2,s_num)];
	for (int i = 0; i < s_num; i++) {
		inputs[i] = LOW;
	}

	STATUS** outputs; 
	outputs = new STATUS * [pow(2, s_num)];
	for (int i = 0; i < pow(2, s_num); i++) {
		outputs[i] = new STATUS[l_num];
		AllInputs[i] = new STATUS[s_num];
	}

	pUI->pWind->SetFont(12, BOLD, BY_NAME, "Arial");
	pUI->pWind->SetPen(BLUE);
	int cellWidth = pUI->width / 10;
	int cellHeight = (pUI->height - pUI->ToolBarHeight - pUI->StatusBarHeight) / 32;

	//Trying different combinations of inputs on switches and getting outputs on LEDs
	int c = 0;
	do {
		for (int i = 0; i < s_num; i++) {
			AllSwitches[i]->isON = inputs[i];
			AllInputs[c][i] = inputs[i];
		}

		for (int j = 0; j < 50; j++)
			for (int i = 0; i < pManager->CompCount; i++)
				pManager->CompList[i]->Operate();

		for (int k = 0; k < l_num; k++) {
			outputs[c][k] = AllLEDs[k]->isON;
		}
		c++;
	} while (AddOne(inputs, s_num));


	if (s_num <= 5 && l_num <= 5) {
		pUI->ClearDrawingArea();
		pUI->PrintMsg("Press Escape to return.");

		//Drawing the table

		pUI->pWind->SetPen(RED, 1);
		for (int i = 1; i < 32; i++) {
			pUI->pWind->DrawLine(0, pUI->ToolBarHeight + i * cellHeight, pUI->width, pUI->ToolBarHeight + i * cellHeight);
		}

		for (int i = 1; i < 10; i++) {
			pUI->pWind->DrawLine(i * cellWidth, pUI->ToolBarHeight, i * cellWidth, pUI->height - pUI->StatusBarHeight);
		}
		pUI->pWind->SetPen(RED, 3);
		pUI->pWind->DrawLine(5 * cellWidth, pUI->ToolBarHeight, 5 * cellWidth, pUI->height - pUI->StatusBarHeight);
		pUI->pWind->DrawLine(0, pUI->ToolBarHeight + cellHeight, pUI->width, pUI->ToolBarHeight + cellHeight);

		//Writing labels

		pUI->pWind->SetFont(12, BOLD, BY_NAME, "Arial");
		pUI->pWind->SetPen(BLACK);

		for (int i = 0; i < s_num; i++) {
			pUI->pWind->DrawString((6-s_num+i) * cellWidth - cellWidth / 2 - 2, pUI->ToolBarHeight + cellHeight / 4 - 2, AllSwitches[i]->m_Label);
		}

		for (int i = 0; i < l_num; i++) {
			pUI->pWind->DrawString((5+i) * cellWidth + cellWidth / 2 - 2, pUI->ToolBarHeight + cellHeight / 4 - 2, AllLEDs[i]->m_Label);
		}

		//Printing input and output values to UI

		for (int i = 0; i < pow(2, s_num); i++) {
			for (int j = 0; j < s_num; j++) {
				string in;
				if (AllInputs[i][j] == LOW) in = "0";
				else in = "1";
				pUI->pWind->DrawString((6 - s_num + j) * cellWidth - cellWidth / 2 - 2, pUI->ToolBarHeight + cellHeight / 4 - 2 + (i+1) * cellHeight, in);
			}

			for (int j = 0; j < l_num; j++) {
				string out;
				if (outputs[i][j] == LOW) out = "0";
				else out = "1";
				pUI->pWind->DrawString((5 + j) * cellWidth + cellWidth / 2 - 2, pUI->ToolBarHeight + cellHeight / 4 - 2 + (i + 1) * cellHeight, out);
			}
		}

		char key;
		pUI->getpWind()->WaitKeyPress(key);
		while(key != 27) pUI->getpWind()->WaitKeyPress(key);
		pUI->ClearDrawingArea();


	}
	else {
		pUI->PrintMsg("You have more than 5 switches or LEDs. Truth table must be saved to a file.\n");
		ofstream outFile;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		pUI->PrintMsg("Type in a file's name with directory. Use 2 backslashes. Click enter when done.\n");
		string name = pUI->GetString();
		outFile.open(name.c_str());
		if (outFile.is_open()) {
			//Drawing table header upper part
			for (int i = 0; i < s_num; i++) {
				outFile << fixed << setw(17) << "----------|";
			}
			outFile << "|";
			for (int j = 0; j < l_num; j++) {
				outFile << fixed << setw(17) << "----------|";
			}
			outFile << endl;

			//Printing labels
			for (int i = 0; i < s_num; i++) {
				outFile << fixed << setw(15) << AllSwitches[i]->m_Label << " |";
			}
			outFile << "|";
			for (int j = 0; j < l_num; j++) {
				outFile << fixed << setw(15) << AllLEDs[j]->m_Label << " |";
			}
			outFile << endl;

			//Drawing table header lower part
			for (int i = 0; i < s_num; i++) {
				outFile << fixed << setw(17) << "----------|";
			}
			outFile << "|";
			for (int j = 0; j < l_num; j++) {
				outFile << fixed << setw(17) << "----------|";
			}
			outFile << endl;

			//Printing inputs and corresponding outputs
			for (int i = 0; i < pow(2, s_num); i++) {
				for (int j = 0; j < s_num; j++) {
					outFile << fixed << setw(10) << "    " << AllInputs[i][j] << "     |";
				}
				outFile << "|";
				for (int j = 0; j < l_num; j++) {
					outFile << fixed << setw(10) << "    " << outputs[i][j] << "     |";
				}
				outFile << endl;
			}
			outFile.close();
			pUI->PrintMsg("Truth table saved successfully in the file!");
		}
		else
			pUI->PrintMsg("Error Opening File!");
	}
	for (int i = 0; i < s_num; i++) {
		AllSwitches[i]->isON = currentStat[i];
	}
}
