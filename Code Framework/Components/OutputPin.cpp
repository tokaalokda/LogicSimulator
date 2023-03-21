#include "OutputPin.h"
#include "Connection.h"


OutputPin::OutputPin()
{
	m_Conn = 0;
	m_FanOut = Default_FANOUT;
}

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > Default_FANOUT ? Default_FANOUT : r_FanOut;	//set the fan out of the pin.
}

//Functionn ConnectTo:
//Connects the ouput pin to the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Component *r_Conn)
{
	if(m_Conn < m_FanOut && r_Conn->ComponentType ==T_CONNECTION)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}