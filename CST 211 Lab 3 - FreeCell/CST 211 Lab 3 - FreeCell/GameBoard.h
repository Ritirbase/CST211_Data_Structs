/*************************************************************
* Author:			Daniel Stotts
* Filename:			GameBoard.h
* Date Created:		4/23/2016
* Modifications:	None
**************************************************************/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Deck.h"
#include "ScreenBuffer.h"
#include "ArrayStack.h"
#include "LinkedStack.h"

#define FORCE_REFRESH false

/************************************************************************
* Class: GameBoard
*
* Purpose: Manages main game functionality.
*
* Manager functions:
* 	GameBoard(Deck &);
*	GameBoard(const GameBoard &);
*	~GameBoard();
*	operator = (const GameBoard &);
*
* Methods:
*	DealCards();
*	DrawBoard();
*	DrawFree();
*	DrawHome();
*	DrawPlay();
*	DrawSelected();
*	DrawControls();
*	SetSelected(int, int);
*	SetSelectedRef(int &, int &, int = 0, bool = false);
*	GetSelected();
*	GetRowCur() const;
*	GetColCur() const;
*	PlaceFree(int);
*	ReintroFree(int);
*	CanReintroFree(int);
*	PlaceHome(int);
*	CanPlaceHome(int);
*	MoveToHome(int);
*	GetColumnSize(int);
*	SplitStack();
*	CanSplit();.
*	PlaceSelected();
*	CanPlace();
*	IsVictorious();
*	SetFreeDB();
*	SetHomeDB();
*	SetBoardDB();
*	SetPlayDB(int);
*	SetSelectedDB();
*	SetControlsDB();
*************************************************************************/
class GameBoard
{
public:
	GameBoard(Deck &);
	GameBoard(const GameBoard &);
	~GameBoard();

	const GameBoard & operator = (const GameBoard &);

	void DealCards();

	void DrawBoard(); // Draw board frame
	void DrawFree(); // Draw free cells
	void DrawHome(); // Draw home cells
	void DrawPlay(); // Draw play area
	void DrawSelected(); // Draw selected cards
	void DrawControls(); // Draw control information

	void SetSelected(int, int);
	void SetSelectedRef(int &, int &, int = 0, bool = false);
	Card GetSelected();

	int GetRowCur() const;
	int GetColCur() const;

	void PlaceFree(int); // Attempt a placement in specified "free" cell.
	void ReintroFree(int); // Attempt a re-introduction of specified "free" cell to the play area.
	bool CanReintroFree(int); // Determines whether specified card can be reintroduced to play area.
	void PlaceHome(int); // Attempt a placement in specified "home" cell.
	bool CanPlaceHome(int); // Determines whether specified card can be sent home.
	//void ReintroHome(int); // Attempt a re-introduction of specified "home" cell to the play area.
	bool MoveToHome(int); // Attempt a move from a free cell to a home cell.

	int GetColumnSize(int);

	void SplitStack(); // Split stack at selection, place (reversed) in _selected.
	bool CanSplit(); // Determines whether stack can be split at location.

	void PlaceSelected(); // Place _selected at location.
	bool CanPlace(); // Determines whether _selected can be placed at location.

	bool IsVictorious(); // Determines whether or not the player has won the game.

	void SetFreeDB();
	void SetHomeDB();
	void SetBoardDB();
	void SetPlayDB(int);
	void SetSelectedDB();
	void SetControlsDB();

private:
	void DrawCard(Card, int = 0, int = 0, bool = true, bool = false, int = 0);

	Deck & _cards;
	ScreenBuffer * _sb;

	int _rowcur;
	int _colcur;

	Card _free[4];
	ArrayStack<Card> _home[4]{ 13, 13, 13, 13 };
	LinkedStack<Card> _play[8];
	LinkedStack<Card> _selected;

	bool _free_db; // Dirty bit for free cell update
	bool _home_db; // Dirty bit for home cell update
	bool _board_db; // Dirty bit for board frame update
	bool _play_db[8]; // Dirty bits for ScreenBuffer update
	bool _selected_db; // Dirty bit for Selected update
	bool _controls_db; // Dirty bit for drawing controls
};

#endif