#ifndef __UI_H_
#define __UI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
using namespace std;

struct Point
{
	int x,y;
};


//A structure to contain drawing parameters for each component
//Each component stores its drawing points in this struct 
//For example, a Gate can store points of the rectangluar area it occupies
//				The Connection 
//this structure can be extended if desired
struct GraphicsInfo
{
	int PointsCount;
	Point* PointsList;
	GraphicsInfo(int PtsCnt)
	{
		PointsCount = PtsCnt;
		PointsList = new Point[PointsCount];	//allocate required points
	}

};


class UI
{

	enum DsgnMenuItem //The items of the design menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in menu
		//If you want to change the menu items order, change the order here
		ITM_INV,
		ITM_AND2,		//AND gate item in menu
		ITM_OR2,		//OR gate item in menu
		ITM_NAND2,
		ITM_NOR2,
		ITM_XOR2,
		ITM_XNOR2,
		ITM_SWITCH,
		ITM_LED,
		ITM_CONNECTION,
		ITM_LABEL,
		ITM_UNDO,
		ITM_REDO,
		ITM_DEL,
		ITM_MOVE,
		ITM_EDITCONN,
		ITM_COPY,
		ITM_CUT,
		ITM_PASTE,
		ITM_SAVE,
		ITM_LOAD,
		ITM_DefMODULE,     //Insert the default module
		ITM_NamedMODULE, //Insert a module named by the user
		ITM_SaveMODULE, //Save circuit as module
		ITM_SIM,	//Simulate menu item
		ITM_EXIT,		//Exit item
		ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	};


	enum SimMenuItem //The items of the simulation menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in menu
		
		ITM_DSN,	//Simulate menu items
		ITM_TRUTH,	//Truth table menu item
	    ITM_EXIT_SIM,
		//TODO:Add more items names here
	
		ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
	};



	

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	GATE_Width = 50,		//Gate Image default width
		                GATE_Height = 50;		//Gate Image default height
	                    

	
public:
	window* pWind;
	
	static const int	width = 1200, height = 650,	//Window width and height
		wx = 15, wy = 15,			//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		ToolBarHeight = 45,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth = 45;		//Width of each item in toolbar menu
	MODE AppMode;		//Application Mode (design or simulation)
	int PCx, PCy;     // Last point clicked
	UI();
	int getGateWidth() const;
	int getGateHeight() const;	
	window* getpWind(); 
	// Input Functions  ---------------------------
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetString();		//Returns a string entered by the user

	ActionType GetUserAction(); //Reads the user click and maps it to an action

	
	// Output Functions  ---------------------------

	void ChangeTitle(string Title) const;

	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

		
	// Draws 2-input AND gate
	void DrawAND2(const GraphicsInfo &r_GfxInfo, bool selected = false) const;
	void DrawOR2(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawINV(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawNAND2(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawNOR2(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawXOR2(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	void DrawModule(const GraphicsInfo& r_GfxInfo, bool selected) const;
	void DrawSWITCH(const GraphicsInfo& r_GfxInfo, bool selected = false, STATUS isOn = NCON) const;
	void DrawLED(const GraphicsInfo& r_GfxInfo, bool selected = false, STATUS isOn = NCON) const;

	// Draws Connection
	void DrawConnection(const GraphicsInfo &r_GfxInfo, bool selected = false) const;
	// Clear Connection
	void UI::ClearConnection(GraphicsInfo *r_GfxInfo) const;
	void UI::ClearComponent(GraphicsInfo* r_GfxInfo) const;
	
	void PrintMsg(string msg) const;	//Print a message on Status bar
	void LabelComp(string l, int x, int y);
	void PrintOnWind(string l, int line); 

	~UI();
};

#endif