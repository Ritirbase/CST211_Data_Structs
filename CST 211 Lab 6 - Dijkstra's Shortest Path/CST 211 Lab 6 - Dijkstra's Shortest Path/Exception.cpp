/*************************************************************
* Author:			Daniel Stotts
* Filename:			Exception.cpp
* Date Created:		3/28/2016
* Modifications:	None
**************************************************************/

#include "Exception.h"

/**********************************************************************
* Purpose: Constructs an instance of an exception object.
*
* Precondition:
*     None
*
* Postcondition:
*     None
*
************************************************************************/
Exception::Exception() : 
	m_msg(nullptr)
{ }

/**********************************************************************
* Purpose: Constructs an instance of an exception object, using
		   a cString as a means to set the internal "message".
*
* Precondition:
*     None
*
* Postcondition:
*     Instance has its internal "message" set.
*
************************************************************************/
Exception::Exception(char * msg)
{
	if (msg == nullptr)
		m_msg = nullptr;
	else
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

/**********************************************************************
* Purpose: Constructs an instance of an exception object, using
		   another exception instance as a means to set the internal
		   "message".
*
* Precondition:
*     None
*
* Postcondition:
*     Instance has its internal "message" set.
*
************************************************************************/
Exception::Exception(const Exception & copy) : 
	m_msg(new char[strlen(copy.m_msg) + 1])
{
	strcpy(m_msg, copy.m_msg);
}

/**********************************************************************
* Purpose: Destroys the instance of an exception object.
*
* Precondition:
*     None
*
* Postcondition:
*     All data members are set to their default values.
*
************************************************************************/
Exception::~Exception()
{
	if (m_msg != nullptr)
	{
		delete[] m_msg;
		m_msg = nullptr;
	}
}

/**********************************************************************
* Purpose: Sets an instance of an exception to equal another instance.
*
* Precondition:
*     Source instance must not equal destination instance.
*
* Postcondition:
*     All data members are set to their copied values.
*
************************************************************************/
const Exception & Exception::operator = (const Exception & rhs)
{
	if (this != &rhs)
	{
		if (m_msg != nullptr)
			delete[] m_msg;

		if (rhs.m_msg == nullptr)
			m_msg == nullptr;
		else
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Returns the internal "message" data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Messaged returned.
*
************************************************************************/
const char * Exception::getMessage() const
{
	return m_msg;
}

/**********************************************************************
* Purpose: Sets the internal "message" data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Message updated.
*
************************************************************************/
void Exception::setMessage(char * msg)
{
	if (msg == nullptr)
	{
		if (m_msg != nullptr)
		{
			delete[] m_msg;
			m_msg = nullptr;
		}
	}
	else
	{
		if (m_msg != nullptr)
			delete[] m_msg;

		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

/**********************************************************************
* Purpose: Outputs relevant data to ostream object.
*
* Precondition:
*     None
*
* Postcondition:
*     Data member(s) output via ostream.
*
************************************************************************/
ostream & operator << (ostream & stream, const Exception & exception)
{
	if (exception.m_msg != nullptr)
		stream << exception.m_msg;

	return stream;
}