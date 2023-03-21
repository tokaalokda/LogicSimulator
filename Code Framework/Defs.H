#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions

enum ActionType
{
	
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add/ Edit Label to a Component, a Connection
	EDIT_Conn,			//Edit source/destination pin(s) of connection 

	SELECT,		//Select a Component, a Connection
	DEL, //Delete a Component, a Connection
	COPY,       //Copies a Component
	CUT,        //Cuts a Component
	MOVE,		//Move a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	DefMODULE,     //Insert the default module 
	NamedMODULE, //Insert a module named by the user
	SaveMODULE, //Save designed circuit as a module 

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode
	TRUTH,

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

	
	//Types used inside action classes to serve undo and redo operations
	NI,      //Default type for when the action type is inconsequential 
	ADD_COMP, //For all add gate, switch, or LED actions 

}; 


//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH,
	NCON	//not connected
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum Type
{ 
	T_CONNECTION,
	T_SWITCH, 
	T_LED,
	T_NOT,
	T_AND2, 
	T_OR2,
	T_NAND2, 
	T_NOR2, 
	T_XOR2,
	T_XNOR2,
	T_Module, 
	T_ModuleB
};

//Maximum number of input pins that can be connected to any output pin

//assume fan out is 5 for now it can be read from the user or can be predefined as const

enum FANOUT
{
	Default_FANOUT = 5	//Default fan out of 2-input AND gate
};


#ifndef NULL
#define NULL 0
#endif

#endif