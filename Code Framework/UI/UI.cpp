#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = BLUE;
	MsgColor = BLUE;
	BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Logic Simulator Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}


int UI::getGateWidth() const
{
	return GATE_Width;
}

int UI::getGateHeight() const
{
	return GATE_Height;
}

window* UI::getpWind() {
	return pWind;
}
//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string UI::GetString()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() 
{	
	int x, y; 
	GetPointClicked(x, y);	//Get the coordinates of the user click
	PCx = x; 
	PCy = y; 

	if(AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_INV: return ADD_INV;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_SWITCH: return ADD_Switch;
			case ITM_LED: return ADD_LED;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_SAVE: return SAVE; 
			case ITM_LOAD: return LOAD; 
			case ITM_DefMODULE: return DefMODULE; 
			case ITM_NamedMODULE: return NamedMODULE;
			case ITM_SaveMODULE: return SaveMODULE; 
			case ITM_LABEL: return ADD_Label;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;
            case ITM_COPY: return COPY;
            case ITM_CUT: return CUT;
            case ITM_SIM: return SIM_MODE; 
			case ITM_EDITCONN: return EDIT_Conn;
			case ITM_EXIT: return EXIT;	
			

			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
	  if (y >= 0 && y < ToolBarHeight)
	  {
		
		int ClickedItemOrder = (x / ToolItemWidth);
		

		switch (ClickedItemOrder)
		{
		
		case ITM_DSN: return DSN_MODE;
		case ITM_TRUTH: return TRUTH;
		case ITM_EXIT_SIM: return EXIT;

		default: return DSN_TOOL;	//A click on empty place in desgin toolbar
		}
	  }

	   //[2] User clicks on the drawing area
	   if (y >= ToolBarHeight && y < height - StatusBarHeight)
	   {
		return SELECT;	//user want to select/unselect a statement in the flowchart
	   }

	//[3] User clicks on the status bar
	    return STATUS_BAR;
	
	}
	

}

//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight + 1, width, height - StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar() 
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_INV] = "images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_CONNECTION.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_UNDO.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_REDO.jpg";
	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_Label.jpg";
	MenuItemImages[ITM_DEL] = "images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_Move.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\Menu_Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\Menu_Cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\Menu_Paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_Load.jpg";
	MenuItemImages[ITM_DefMODULE] = "images\\Menu\\Menu_DefModule.jpg";
	MenuItemImages[ITM_NamedMODULE] = "images\\Menu\\Menu_NamedModule.jpg";
	MenuItemImages[ITM_SaveMODULE] = "images\\Menu\\Menu_SaveModule.jpg";
	MenuItemImages[ITM_SIM] = "images\\Menu\\Menu_Simulate.jpg";
	MenuItemImages[ITM_EDITCONN] = "images\\Menu\\Menu_EditConnect.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*ToolItemWidth,0,ToolItemWidth, ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, ToolBarHeight + 1, width, ToolBarHeight + 1);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode

	string MenuItemImages[ITM_SIM_CNT];
	pWind->SetPen(WHITE, 3);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight);
	MenuItemImages[ITM_DSN] = "images\\Menu\\Menu_Design.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_Truth.jpg";
	MenuItemImages[ITM_EXIT_SIM] = "images\\Menu\\Menu_Exit.jpg";

	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawAND2(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg";
	else  
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawOR2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawINV(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawNAND2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawNOR2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawXOR2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawXNOR2(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;
	
    if (selected )	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawModule(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GateImage;

	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Module_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_Module.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, 4*GATE_Width, 2*GATE_Height);
}

void UI::DrawSWITCH(const GraphicsInfo& r_GfxInfo, bool selected, STATUS isOn) const
{
	string GateImage;

	if (isOn == HIGH)	//use image in the on case
		GateImage = "Images\\Gates\\Switch_ON.jpg";
	else if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Switch_OFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Switch_OFF.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}

void UI::DrawLED(const GraphicsInfo& r_GfxInfo, bool selected, STATUS isOn) const
{
	string GateImage;

	if (isOn == HIGH)
		GateImage = "Images\\Gates\\LED_ON.jpg";
	else if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\LED_OFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\LED_OFF.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, GATE_Width, GATE_Height);
}


void UI::DrawConnection(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	int x1 = r_GfxInfo.PointsList[0].x;
	int y1 = r_GfxInfo.PointsList[0].y;
	int x2 = r_GfxInfo.PointsList[1].x;
	int y2 = r_GfxInfo.PointsList[1].y;
	if (selected) 	pWind->SetPen(RED, 3);
	else pWind->SetPen(ConnColor, 3);
	pWind->DrawLine(x1, y1, x1 + (x2-x1)/3, y1);
	pWind->DrawLine(x1 + (x2 - x1) / 3, y1, x1 + (x2 - x1) / 3, y2);
	pWind->DrawLine(x1 + (x2 - x1) / 3, y2, x2, y2);
}


void UI::ClearConnection(GraphicsInfo *r_GfxInfo) const
{
	int x1 = r_GfxInfo->PointsList[0].x;
	int y1 = r_GfxInfo->PointsList[0].y;
	int x2 = r_GfxInfo->PointsList[1].x;
	int y2 = r_GfxInfo->PointsList[1].y;

	pWind->SetPen(BkGrndColor, 3);
	pWind->DrawLine(x1, y1, x1 + (x2 - x1) / 3, y1);
	pWind->DrawLine(x1 + (x2 - x1) / 3, y1, x1 + (x2 - x1) / 3, y2);
	pWind->DrawLine(x1 + (x2 - x1) / 3, y2, x2, y2);

}

void UI::ClearComponent(GraphicsInfo* r_GfxInfo) const
{
	int x1 = r_GfxInfo->PointsList[0].x;
	int y1 = r_GfxInfo->PointsList[0].y;
	int x2 = r_GfxInfo->PointsList[1].x;
	int y2 = r_GfxInfo->PointsList[1].y;

	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(x1, y1, x2, y2);
}


void UI::LabelComp(string l, int x, int y) {

	if (l != "-") {

		int MsgX = x + 10;

		int MsgY = y - 20;

		//Clear Old label
		pWind->SetPen(BkGrndColor);
		pWind->SetBrush(BkGrndColor);
		pWind->DrawRectangle(MsgX, MsgY, MsgX + 95, MsgY + 15);

		// Print the Message
		pWind->SetFont(15, BOLD, BY_NAME, "Arial");
		pWind->SetPen(BLACK);
		pWind->DrawString(MsgX, MsgY, l);

	}
}

void UI::PrintOnWind(string l, int line) {
	int x = 10; 
	int y = 60 + line*20;  
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	pWind->SetPen(RED);
	pWind->DrawString(x, y, l);
}

UI::~UI()
{
	delete pWind;
}