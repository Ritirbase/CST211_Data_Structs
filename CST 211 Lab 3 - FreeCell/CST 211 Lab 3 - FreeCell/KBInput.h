/*************************************************************
* Author:			Daniel Stotts
* Filename:			KBInput.h
* Date Created:		4/9/2016
* Modifications:	4/26/2016 - Added number definitions &
					"removed" 2D array support
					4/28/2016 - added copy ctor, op =
**************************************************************/

#ifndef KBINPUT_H
#define KBINPUT_H

//#include "Array2D.h"

#ifndef KB_KEYS
#ifndef KB_ONE
#define KB_ONE char(0x31)
#endif
#ifndef KB_TWO
#define KB_TWO char(0x32)
#endif
#ifndef KB_THREE
#define KB_THREE char(0x33)
#endif
#ifndef KB_FOUR
#define KB_FOUR char(0x34)
#endif
#ifndef KB_FIVE
#define KB_FIVE char(0x35)
#endif
#ifndef KB_SIX
#define KB_SIX char(0x36)
#endif
#ifndef KB_SEVEN
#define KB_SEVEN char(0x37)
#endif
#ifndef KB_EIGHT
#define KB_EIGHT char(0x38)
#endif
#ifndef KB_NINE
#define KB_NINE char(0x39)
#endif
#ifndef KB_ZERO
#define KB_ZERO char(0x30)
#endif
#ifndef KB_UP
#define KB_UP char(87)
#endif
#ifndef KB_DOWN
#define KB_DOWN char(83)
#endif
#ifndef KB_LEFT
#define KB_LEFT char(65)
#endif
#ifndef KB_RIGHT
#define KB_RIGHT char(68)
#endif
#ifndef KB_Q
#define KB_Q char(81)
#endif
#ifndef KB_E
#define KB_E char(69)
#endif
#ifndef KB_R
#define KB_R char(82)
#endif
#ifndef KB_T
#define KB_T char(84)
#endif
#ifndef KB_F
#define KB_F char(70)
#endif
#ifndef KB_SPACE
#define KB_SPACE char(32)
#endif
#ifndef KB_BACKQUOTE
#define KB_BACKQUOTE char(96)
#endif
#endif

/************************************************************************
* Class: KBInput
*
* Purpose: This class manages keyboard input, as well as internal "boundaries"
			for ease of use with array selection.
*
* Manager functions:
* 	KBInput();
*	KBInput(int, int);
*	~KBInput();
*
* Methods:
*	WaitKey();
*	GetKey() const;
*	GetR() const;
*	GetC() const;
*	GetRMax() const;
*	SetRMax(int);
*	GetCMax() const;
*	SetCMax(int);
*************************************************************************/
class KBInput
{
public:
	KBInput();
	KBInput(int, int);
	KBInput(const KBInput &);
	~KBInput();

	const KBInput & operator = (const KBInput &);

	void WaitKey();
	char GetKey() const;

	//const int GetR() const;
	//const int GetC() const;

	//const int GetRMax() const;
	//void SetRMax(int);

	//const int GetCMax() const;
	//void SetCMax(int);

private:
	char m_key;

	//int _sel_R; int _sel_R_max;
	//int _sel_C; int _sel_C_max;

};

#endif