/*************************************************************
* Author:			Daniel Stotts
* Filename:			KBInput.cpp
* Date Created:		4/9/2016
* Modifications:	4/26/2016 - "removed" 2D array support
					4/28/2016 - added copy ctor, op =
**************************************************************/

//#include <iostream>
//using std::cin;

#include <conio.h>
#include <ctype.h>

#include "KBInput.h"

/**********************************************************************
* Purpose: Constructs an instance of a KBInput object.
*
* Precondition:
*     None
*
* Postcondition:
*     KBInput instance created.
*
************************************************************************/
KBInput::KBInput() :
	m_key(char(0))/*,
	_sel_R(0), _sel_R_max(0),
	_sel_C(0), _sel_C_max(0)*/
{ }

/**********************************************************************
* Purpose: Constructs an instance of a KBInput object.
*
* Precondition:
*     None
*
* Postcondition:
*     KBInput instance created.
*
************************************************************************/
KBInput::KBInput(int r, int c) :
	m_key(char(0))/*,
	_sel_R(0), _sel_R_max(r - 1),
	_sel_C(0), _sel_C_max(c - 1)*/
{ }

/**********************************************************************
* Purpose: Constructs an instance of a KBInput object.
*
* Precondition:
*     None
*
* Postcondition:
*     KBInput instance created.
*
************************************************************************/
KBInput::KBInput(const KBInput & copy) :
	m_key(copy.m_key)
{ }

/**********************************************************************
* Purpose: Destroys the instance of an KBInput object.
*
* Precondition:
*     None
*
* Postcondition:
*     KBInput instance destroyed.
*e
************************************************************************/
KBInput::~KBInput()
{
	m_key = '\0';

	//_sel_R = 0; _sel_R_max = 0;
	//_sel_C = 0; _sel_C_max = 0;
}

/**********************************************************************
* Purpose: Sets this instance equal to another instance of a KBInput
			object.
*
* Precondition:
*     None
*
* Postcondition:
*     KBInput instance copied.
*
************************************************************************/
const KBInput & KBInput::operator = (const KBInput & rhs)
{
	if(this != &rhs)
	{
		m_key = rhs.m_key;
	}
	return *this;
}

/**********************************************************************
* Purpose: Waits for and returns a keypress. Also handles internal
			"array" coordinates, allowing for easy use with arrays.
*
* Precondition:
*     None
*
* Postcondition:
*     Key has been read and recorded.
*
************************************************************************/
void KBInput::WaitKey()
{
	//cin.ignore(cin.rdbuf()->in_avail());
	m_key = toupper(getch());

	//switch (m_key)
	//{
	//case KB_UP: if (_sel_R > 0) --_sel_R; break;
	//case KB_DOWN: if (_sel_R < _sel_R_max) ++_sel_R; break;
	//case(KB_LEFT) : if (_sel_C > 0) --_sel_C; break;
	//case(KB_RIGHT) : if (_sel_C < _sel_C_max) ++_sel_C; break;
	//default: break;
	//}
}

/**********************************************************************
* Purpose: Returns key data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Key data member returned.
*
************************************************************************/
char KBInput::GetKey() const
{
	return m_key;
}

///**********************************************************************
//* Purpose: Returns selected row data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Row data member returned.
//*
//************************************************************************/
//const int KBInput::GetR() const
//{
//	return _sel_R;
//}
//
///**********************************************************************
//* Purpose: Returns selected column data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Column data member returned.
//*
//************************************************************************/
//const int KBInput::GetC() const
//{
//	return _sel_C;
//}
//
///**********************************************************************
//* Purpose: Returns maximum row boundary data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Max row data member returned.
//*
//************************************************************************/
//const int KBInput::GetRMax() const
//{
//	return _sel_R_max;
//}
//
///**********************************************************************
//* Purpose: Sets maximum row boundary data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Max row data member set.
//*
//************************************************************************/
//void KBInput::SetRMax(int r)
//{
//	_sel_R = 0;
//	_sel_C = 0;
//
//	_sel_R_max = r - 1;
//}
//
///**********************************************************************
//* Purpose: Returns maximum column boundary data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Max column data member returned.
//*
//************************************************************************/
//const int KBInput::GetCMax() const
//{
//	return _sel_C_max;
//}
//
///**********************************************************************
//* Purpose: Sets maximum column boundary data member.
//*
//* Precondition:
//*     None
//*
//* Postcondition:
//*     Max column data member set.
//*
//************************************************************************/
//void KBInput::SetCMax(int c)
//{
//	_sel_R = 0;
//	_sel_C = 0;
//
//	_sel_C_max = c - 1;
//}