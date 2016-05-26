/*************************************************************
* Author:			Daniel Stotts
* Filename:			Exception.h
* Date Created:		3/28/2016
* Modifications:	None
**************************************************************/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <fstream>
using std::ostream;

/************************************************************************
* Class: Exception
*
* Purpose: This class manages an exception cString to be thrown.
*
* Manager functions:
* 	Exception()
*	Exception(char * msg)
*	Exception (const Exception & copy)
*	~Exception()
*	operator = (const Exception & copy)
*
* Methods:
*	getMessage()
*	setMessage(char *)
*	operator << (ostream & stream, const Exception & exception)
*************************************************************************/
class Exception
{
public:
	Exception();
	Exception(char *);
	Exception(const Exception &);
	~Exception();

	const Exception & operator = (const Exception &);
	
	const char * getMessage() const;
	void setMessage(char *);

	friend ostream & operator << (ostream &, const Exception &);

private:
	char * m_msg;

};

#endif