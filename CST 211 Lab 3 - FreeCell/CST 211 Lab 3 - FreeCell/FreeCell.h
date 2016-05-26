/*************************************************************
* Author:			Daniel Stotts
* Filename:			FreeCell.h
* Date Created:		4/25/2016
* Modifications:	None
**************************************************************/

#ifndef FREECELL_H
#define FREECELL_H

#include "Deck.h"
#include "GameBoard.h"
#include "KBInput.h"

/************************************************************************
* Class: FreeCell
*
* Purpose: Implements a game of FreeCell.
*
* Manager functions:
*	FreeCell();
*	FreeCell(const FreeCell &);
*	~FreeCell();
*	operator = (const FreeCell &);
*
* Methods:
*	Play();
*************************************************************************/
class FreeCell
{
public:
	FreeCell();
	FreeCell(const FreeCell &);
	~FreeCell();

	const FreeCell & operator = (const FreeCell &);

	void Play();
private:
	Deck _deck;
	GameBoard _gb;
	KBInput _kbi;

	bool _exit;

	int _offset;
	bool _smaller;
	bool _stacksplit;
	bool _placedfree[4];
	bool _win;

	int _tv, _th;

	int _vertical, _horizontal;
};

#endif