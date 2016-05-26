#include "GameBoard.h"

/**********************************************************************
* Purpose: Constructs an instance of a GameBoard object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
GameBoard::GameBoard(Deck & deck) :
	_cards(deck),
	_sb(ScreenBuffer::GetInstance()),
	_rowcur(-1),
	_colcur(-1)
{
	_sb->SetOrigin(2, 2);
	DealCards();
}

/**********************************************************************
* Purpose: Constructs an instance of a GameBoard object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
GameBoard::GameBoard(const GameBoard & copy) :
	_cards(copy._cards),
	_sb(copy._sb),
	_rowcur(copy._rowcur),
	_colcur(copy._colcur),
	_selected(copy._selected),
	_free_db(copy._free_db),
	_home_db(copy._home_db),
	_board_db(copy._board_db),
	_selected_db(copy._selected_db),
	_controls_db(copy._controls_db)
{
	for (int i = 0; i < 4; ++i)
		_free[i] = copy._free[i];
	for (int i = 0; i < 4; ++i)
		_home[i] = copy._home[i];
	for (int i = 0; i < 8; ++i)
		_play[i] = copy._play[i];

	for (int i = 0; i < 8; ++i)
		_play_db[i] = copy._play_db[i];
}

/**********************************************************************
* Purpose: Destroys the instance of a GameBoard object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
GameBoard::~GameBoard()
{

}

/**********************************************************************
* Purpose: Sets instance equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
const GameBoard & GameBoard::operator = (const GameBoard & rhs)
{
	if (this != &rhs)
	{
		_cards = rhs._cards;
		_sb = rhs._sb;

		_rowcur = rhs._rowcur;
		_colcur = rhs._colcur;

		for (int i = 0; i < 4; ++i)
			_free[i] = rhs._free[i];
		for (int i = 0; i < 4; ++i)
			_home[i] = rhs._home[i];
		for (int i = 0; i < 8; ++i)
			_play[i] = rhs._play[i];

		_selected = rhs._selected;

		_free_db = rhs._free_db;
		_home_db = rhs._home_db;
		_board_db = rhs._board_db;
		for (int i = 0; i < 8; ++i)
			_play_db[i] = rhs._play_db[i];
		_selected_db = rhs._selected_db;
		_controls_db = rhs._controls_db;
	}
	return *this;
}

/**********************************************************************
* Purpose: Deals a deck of cards to play area.
*
* Precondition:
*     None
*
* Postcondition:
*     Cards dealt.
*
************************************************************************/
void GameBoard::DealCards()
{
	_cards.Shuffle();
	for (int i = 0; i < 52; ++i)
		_play[i % 8].Push(_cards.Deal());
}

/**********************************************************************
* Purpose: Draws basic board geometry.
*
* Precondition:
*     None
*
* Postcondition:
*     Board drawn.
*
************************************************************************/
void GameBoard::DrawBoard()
{
	if (FORCE_REFRESH || _board_db)
	{
		_sb->SetOffset(0, 0);
		_sb->SetBlock(0, 0, _sb->GetRows() - 1, _sb->GetColumns() - 30, TCHAR(0x0000), B_L_GREEN);
		_sb->SetBlock(1, 1, _sb->GetRows() - 2, _sb->GetColumns() - 31, TCHAR(0x0000), B_GREEN);
		_sb->SetBlock(0, _sb->GetColumns() - 29, _sb->GetRows() - 29, _sb->GetColumns() - 1, TCHAR(0x0000));
		_sb->SetBlock(1, _sb->GetColumns() - 28, _sb->GetRows() - 30, _sb->GetColumns() - 2, TCHAR(0x0000));
		_sb->SetcString(_sb->GetRows() - 2, (_sb->GetColumns() / 2) - 30, L"FreeCell v0.7 by Daniel Stotts", B_GREEN | F_L_GREEN);
		_sb->Draw();
		_board_db = false;
	}
}

/**********************************************************************
* Purpose: Draws free cells.
*
* Precondition:
*     None
*
* Postcondition:
*     Free cells drawn.
*
************************************************************************/
void GameBoard::DrawFree()
{
	if (FORCE_REFRESH || _free_db)
	{
		_sb->SetOffset(0, 0);
		_sb->SetcString(2, 13, L"Free Cells: ");
		for (int i = 0; i < 4; ++i)
			DrawCard(_free[i], 4, i * 7 + 5, true, false, -1);
		_sb->Draw();
		_free_db = false;
	}
}

/**********************************************************************
* Purpose: Draws home cells.
*
* Precondition:
*     None
*
* Postcondition:
*     Home cells drawn.
*
************************************************************************/
void GameBoard::DrawHome()
{
	if (FORCE_REFRESH || _home_db)
	{
		_sb->SetOffset(0, 0);
		_sb->SetcString(2, 47, L"Home Cells: ");
		Card blank;
		for (int i = 0; i < 4; ++i)
			if (_home[i].isEmpty())
				DrawCard(blank, 4, i * 7 + 39, true, false, -1);
			else
				DrawCard(_home[i].Peek(), 4, i * 7 + 39, true, false, -1);
		_sb->SetOffset(6, 42);
		if (_home[0].isEmpty()) _sb->SetChar(0, 0, TCHAR(0x2660), F_D_GRAY); // SPADE
		if (_home[1].isEmpty()) _sb->SetChar(0, 7, TCHAR(0x2663), F_D_GRAY); // CLUB
		if (_home[2].isEmpty()) _sb->SetChar(0, 14, TCHAR(0x2665), F_L_RED); // HEART
		if (_home[3].isEmpty()) _sb->SetChar(0, 21, TCHAR(0x2666), F_L_RED); // DIAMOND
		_sb->Draw();
		_home_db = false;
	}
}

/**********************************************************************
* Purpose: Draws play area.
*
* Precondition:
*     None
*
* Postcondition:
*     Play area drawn.
*
************************************************************************/
void GameBoard::DrawPlay()
{
	LinkedStack<Card> temp1, temp2;
	for (int s = 0; s < 8; ++s)
	{
		if (FORCE_REFRESH || _play_db[s])
		{
			_sb->SetOffset(0, 0);
			if (_play[s].isEmpty())
				DrawCard(Card(Card::NOR, Card::NOS), 10, s * 7 + 8, true,
					(_colcur == s ? true : false), _selected.Size());
			else
			{
				temp1 = _play[s];
				for (int i = 0; i < temp1.Size() + i; ++i)
					temp2.Push(temp1.Pop());
				for (int i = 0; i < temp2.Size() + i; ++i)
				{
					temp1.Push(temp2.Pop());
					DrawCard(temp1.Peek(), (i * 2) + 10, s * 7 + 8,
						(temp2.Size() == 0 ? true : false),
						(_colcur == s ? true : false), _selected.Size());
				}
			}
			_sb->Draw();
			_play_db[s] = false;
		}
	}
}

/**********************************************************************
* Purpose: Draws selected cards.
*
* Precondition:
*     None
*
* Postcondition:
*     Selected cards drawn.
*
************************************************************************/
void GameBoard::DrawSelected()
{
	if (FORCE_REFRESH || _selected_db)
	{
		_sb->SetOffset(0, 0);
		_sb->SetBlock(4, 73, _sb->GetRows() - 2, 79, TCHAR(0x0000), B_GREEN);
		_sb->SetcString(2, 71, L"Selected: ");
		if (_selected.isEmpty())
			DrawCard(Card(Card::NOR, Card::NOS), 4, 73, true, false, -1);
		else
		{
			LinkedStack<Card> temp;
			for (int i = 0; i < _selected.Size() + i; ++i)
			{
				temp.Push(_selected.Pop());
				DrawCard(temp.Peek(), 4 + (2 * i), 73, true, false, -1);
			}
			for (int i = 0; i < temp.Size() + i; ++i)
				_selected.Push(temp.Pop());
		}
		_selected_db = false;
	}
}

/**********************************************************************
* Purpose: Draws controls.
*
* Precondition:
*     None
*
* Postcondition:
*     Controls drawn.
*
************************************************************************/
void GameBoard::DrawControls()
{
	if (FORCE_REFRESH || _controls_db)
	{
		_sb->SetOffset(2, 88);
		_sb->SetcString(0, 4, L"Controls: ", F_L_PURPLE);
		_sb->SetcString(2, 0, L"W: UP ", F_L_CYAN);
		_sb->SetcString(3, 0, L"A: LEFT ", F_L_CYAN);
		_sb->SetcString(4, 0, L"S: DOWN ", F_L_CYAN);
		_sb->SetcString(5, 0, L"D: RIGHT ", F_L_CYAN);
		_sb->SetcString(7, 0, L"1 - 4: MOVE TO FREE CELL ", F_L_GREEN);
		_sb->SetcString(8, 0, L"5 - 8: FREE TO HOME CELL ", F_L_GREEN);
		//_sb->SetcString(8, 0, L"5 - 8: HOME CELL ", F_L_GREEN);
		_sb->SetcString(9, 0, L"R: MOVE TO HOME CELL ", F_L_GREEN);
		_sb->SetcString(11, 0, L"E: SELECT ", F_L_CYAN);
		_sb->SetcString(12, 0, L"SPACE: SELECT ", F_L_CYAN);
		_sb->SetcString(14, 0, L"Q Q: QUIT GAME ", F_L_PURPLE);
		_sb->Draw();
	}
}

/**********************************************************************
* Purpose: Sets selected card.
*
* Precondition:
*     None
*
* Postcondition:
*     Selected card set.
*
************************************************************************/
void GameBoard::SetSelected(int r, int c)
{
	if (c > 7)
		_colcur = 7;
	else
		_colcur = c;

	if (_play[_colcur].isEmpty())
		_rowcur = 0;
	else if (r > _play[_colcur].Size() - 1)
		_rowcur = _play[_colcur].Size() - 1;
	else
		_rowcur = r;

	SetPlayDB(_colcur);
}

/**********************************************************************
* Purpose: Sets selected card.
*
* Precondition:
*     None
*
* Postcondition:
*     Selected card set.
*
************************************************************************/
void GameBoard::SetSelectedRef(int & r, int & c, int stabilize, bool smaller)
{
	if (c > 7)
		_colcur = 7;
	else
		_colcur = c;

	//if (r > _play[_colcur].Size() - 1)
	//	_rowcur = _play[_colcur].Size() - 1;
	//else
	_rowcur = r + (stabilize + r < 0 ? 0 : stabilize);
	if (smaller)
		_rowcur = 0;

	r = _rowcur;
	c = _colcur;

	SetPlayDB(_colcur);
}

/**********************************************************************
* Purpose: Gets selected card.
*
* Precondition:
*     None
*
* Postcondition:
*     Selected card returned.
*
************************************************************************/
Card GameBoard::GetSelected()
{
	Card returndata(Card(Card::NOR, Card::NOS));
	if (_rowcur != -1 && _colcur != -1)
	{
		LinkedStack<Card> temp(_play[_colcur]);

		for (int i = 0; i < _rowcur; ++i)
			temp.Pop();

		if (!temp.isEmpty())
			returndata = temp.Peek();
	}
	return returndata;
}

/**********************************************************************
* Purpose: Gets row cursor position.
*
* Precondition:
*     None
*
* Postcondition:
*     Row cursor position returned.
*
************************************************************************/
int GameBoard::GetRowCur() const
{
	return _rowcur;
}

/**********************************************************************
* Purpose: Gets column cursor position.
*
* Precondition:
*     None
*
* Postcondition:
*     Column cursor position returned.
*
************************************************************************/
int GameBoard::GetColCur() const
{
	return _colcur;
}

/**********************************************************************
* Purpose: Sends a card to free cell area.
*
* Precondition:
*     None
*
* Postcondition:
*     Card relocated.
*
************************************************************************/
void GameBoard::PlaceFree(int f)
{
	if (!_play[_colcur].isEmpty())
	{
		_free[f] = _play[_colcur].Pop();
		SetFreeDB();
		//for (int i = 0; i < 4; ++i)
		//	SetPlayDB(i);
	}
}

/**********************************************************************
* Purpose: Reintroduces card to play area from free cells.
*
* Precondition:
*     None
*
* Postcondition:
*     Card reintroduced.
*
************************************************************************/
void GameBoard::ReintroFree(int f)
{
	if (_free[f] != Card(Card::NOR, Card::NOS))
	{
		_play[_colcur].Push(_free[f]);
		_free[f].SetRank(Card::NOR);
		_free[f].SetSuit(Card::NOS);
		SetFreeDB();
		//for (int i = 0; i < 4; ++i)
		//	SetPlayDB(i);
	}
}

/**********************************************************************
* Purpose: Determines if a card can be reintroduced from free cell.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool GameBoard::CanReintroFree(int f)
{
	bool indeed = true;

	if (_free[f].GetRank() == Card::NOR || _free[f].GetSuit() == Card::NOS)
		indeed = false;
	else
	{
		if (!_play[_colcur].isEmpty())
		{
			// SAME TWO COLORS?
			if ((_free[f].GetSuit() == Card::Spade || _free[f].GetSuit() == Card::Club) &&
				(_play[_colcur].Peek().GetSuit() == Card::Spade || _play[_colcur].Peek().GetSuit() == Card::Club))
				indeed = false;
			if ((_free[f].GetSuit() == Card::Heart || _free[f].GetSuit() == Card::Diamond) &&
				(_play[_colcur].Peek().GetSuit() == Card::Heart || _play[_colcur].Peek().GetSuit() == Card::Diamond))
				indeed = false;
			// INVALID RANK CHAIN?
			if (_free[f].GetRank() != _play[_colcur].Peek().GetRank() - 1)
				indeed = false;
		}
	}
	return indeed;
}

/**********************************************************************
* Purpose: Sends a card to home cell area.
*
* Precondition:
*     None
*
* Postcondition:
*     Card relocated.
*
************************************************************************/
void GameBoard::PlaceHome(int h)
{
	_home[h].Push(_play[_colcur].Pop());
	SetHomeDB();
}

/**********************************************************************
* Purpose: Determines if a card can be sent home.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool GameBoard::CanPlaceHome(int h)
{
	bool indeed = true;

	switch (h)
	{
	case 0: // SPADE
		if (GetSelected().GetSuit() == Card::Spade)
		{
			if (_home[0].isEmpty())
			{
				if (GetSelected().GetRank() != Card::Ace)
					indeed = false;
			}
			else
				if (_home[0].Peek().GetRank() + 1 != GetSelected().GetRank())
					indeed = false;
		}
		else
			indeed = false;
		break;
	case 1: // CLUB
		if (GetSelected().GetSuit() == Card::Club)
		{
			if (_home[1].isEmpty())
			{
				if (GetSelected().GetRank() != Card::Ace)
					indeed = false;
			}
			else
				if (_home[1].Peek().GetRank() + 1 != GetSelected().GetRank())
					indeed = false;
		}
		else
			indeed = false;
		break;
	case 2: // HEART
		if (GetSelected().GetSuit() == Card::Heart)
		{
			if (_home[2].isEmpty())
			{
				if (GetSelected().GetRank() != Card::Ace)
					indeed = false;
			}
			else
				if (_home[2].Peek().GetRank() + 1 != GetSelected().GetRank())
					indeed = false;
		}
		else
			indeed = false;
		break;
	case 3: // DIAMOND
		if (GetSelected().GetSuit() == Card::Diamond)
		{
			if (_home[3].isEmpty())
			{
				if (GetSelected().GetRank() != Card::Ace)
					indeed = false;
			}
			else
				if (_home[3].Peek().GetRank() + 1 != GetSelected().GetRank())
					indeed = false;
		}
		else
			indeed = false;
		break;
	}
	return indeed;
}

/**********************************************************************
* Purpose: Moves card from free cell to home area.
*
* Precondition:
*     None
*
* Postcondition:
*     Card relocated.
*
************************************************************************/
bool GameBoard::MoveToHome(int f)
{
	bool indeed = true;

	if (_free[f].GetRank() != Card::NOR && _free[f].GetSuit() != Card::NOS)
		switch (static_cast<int>(_free[f].GetSuit()))
		{
		case 0: // SPADE
			if (_free[f].GetSuit() == Card::Spade)
			{
				if (_home[0].isEmpty())
				{
					if (_free[f].GetRank() != Card::Ace)
						indeed = false;
				}
				else
					if (_home[0].Peek().GetRank() + 1 != _free[f].GetRank())
						indeed = false;
			}
			else
				indeed = false;

			if (indeed)
			{
				_home[0].Push(Card(_free[f].GetRank(), _free[f].GetSuit()));
				_free[f].SetRank(Card::NOR);
				_free[f].SetSuit(Card::NOS);
			}
			break;
		case 1: // CLUB
			if (_free[f].GetSuit() == Card::Club)
			{
				if (_home[1].isEmpty())
				{
					if (_free[f].GetRank() != Card::Ace)
						indeed = false;
				}
				else
					if (_home[1].Peek().GetRank() + 1 != _free[f].GetRank())
						indeed = false;
			}
			else
				indeed = false;

			if (indeed)
			{
				_home[1].Push(Card(_free[f].GetRank(), _free[f].GetSuit()));
				_free[f].SetRank(Card::NOR);
				_free[f].SetSuit(Card::NOS);
			}
			break;
		case 2: // HEART
			if (_free[f].GetSuit() == Card::Heart)
			{
				if (_home[2].isEmpty())
				{
					if (_free[f].GetRank() != Card::Ace)
						indeed = false;
				}
				else
					if (_home[2].Peek().GetRank() + 1 != _free[f].GetRank())
						indeed = false;
			}
			else
				indeed = false;

			if (indeed)
			{
				_home[2].Push(Card(_free[f].GetRank(), _free[f].GetSuit()));
				_free[f].SetRank(Card::NOR);
				_free[f].SetSuit(Card::NOS);
			}
			break;
		case 3: // DIAMOND
			if (_free[f].GetSuit() == Card::Diamond)
			{
				if (_home[3].isEmpty())
				{
					if (_free[f].GetRank() != Card::Ace)
						indeed = false;
				}
				else
					if (_home[3].Peek().GetRank() + 1 != _free[f].GetRank())
						indeed = false;
			}
			else
				indeed = false;

			if (indeed)
			{
				_home[3].Push(Card(_free[f].GetRank(), _free[f].GetSuit()));
				_free[f].SetRank(Card::NOR);
				_free[f].SetSuit(Card::NOS);
			}
			break;
		}
	return indeed;
}

//void GameBoard::ReintroHome(int h)
//{
//
//}

/**********************************************************************
* Purpose: Returns column size.
*
* Precondition:
*     None
*
* Postcondition:
*     Value returned.
*
************************************************************************/
int GameBoard::GetColumnSize(int c)
{
	if (c < 0 || c > 7)
		throw Exception("Invalid column!");

	return _play[c].Size();
}

/**********************************************************************
* Purpose: Splits play area stack into selected stack.
*
* Precondition:
*     None
*
* Postcondition:
*     Cards relocated.
*
************************************************************************/
void GameBoard::SplitStack()
{
	if (!_play[_colcur].isEmpty())
	{
		for (int i = 0; i < (_rowcur < 13 ? _rowcur + 1 : 13); ++i)
			_selected.Push(_play[_colcur].Pop());
		_play_db[_colcur] = true;
		_rowcur = 0;
		SetPlayDB(_colcur);
	}
}

/**********************************************************************
* Purpose: Determines of play stack can be split at cursor position.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool GameBoard::CanSplit()
{
	bool indeed = true;
	LinkedStack<Card> temp;

	int allowmove = 1; // limit/ cap

	if (_play[_colcur].isEmpty())
		indeed = false;
	else
	{
		// OPEN FREE CELLS
		for (int i = 0; i < 4; ++i)
			if (_free[i].GetRank() == Card::NOR && _free[i].GetSuit() == Card::NOS)
				++allowmove;
		// OPEN PLAY STACKS
		for (int i = 0; i < 8; ++i)
			if (_play[i].isEmpty())
				allowmove *= 2;
		// CARDS UNDER/ EQUAL TO THRESHOLD?
		if (_rowcur >= allowmove)
			indeed = false;

		for (int i = 0; i < _rowcur; ++i)
		{
			temp.Push(_play[_colcur].Pop());
			// SAME TWO COLORS?
			if ((temp.Peek().GetSuit() == Card::Spade || temp.Peek().GetSuit() == Card::Club) &&
				(_play[_colcur].Peek().GetSuit() == Card::Spade || _play[_colcur].Peek().GetSuit() == Card::Club))
				indeed = false;
			if ((temp.Peek().GetSuit() == Card::Heart || temp.Peek().GetSuit() == Card::Diamond) &&
				(_play[_colcur].Peek().GetSuit() == Card::Heart || _play[_colcur].Peek().GetSuit() == Card::Diamond))
				indeed = false;
			// INVALID RANK CHAIN?
			if (temp.Peek().GetRank() != _play[_colcur].Peek().GetRank() - 1)
				indeed = false;
		}
		for (int i = 0; i < temp.Size() + i; ++i)
			_play[_colcur].Push(temp.Pop());
	}
	return indeed;
}

/**********************************************************************
* Purpose: Places selected cards.
*
* Precondition:
*     None
*
* Postcondition:
*     Cards relocated.
*
************************************************************************/
void GameBoard::PlaceSelected()
{
	if (!_selected.isEmpty())
	{
		for (int i = 0; i < _selected.Size() + i; ++i)
			_play[_colcur].Push(_selected.Pop());
		SetPlayDB(_colcur);
	}
}

/**********************************************************************
* Purpose: Determines if selected cards can be placed.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool GameBoard::CanPlace()
{
	bool indeed = true;
	LinkedStack<Card> temp;

	int allowmove = 1; // limit/ cap

	if (_selected.isEmpty())
		indeed = false;
	else
	{
		// OPEN FREE CELLS
		for (int i = 0; i < 4; ++i)
			if (_free[i].GetRank() == Card::NOR && _free[i].GetSuit() == Card::NOS)
				++allowmove;
		// OPEN PLAY STACKS
		for (int i = 0; i < 8; ++i)
			if (_play[i].isEmpty())
				allowmove *= 2;
		// MOVING INTO EMPTY STACK?
		if (_play[_colcur].isEmpty())
			allowmove /= 2;
		// CARDS UNDER/ EQUAL TO THRESHOLD?
		if (_selected.Size() > allowmove)
			indeed = false;
		if (!_play[_colcur].isEmpty())
		{
			// SAME TWO COLORS?
			if ((_selected.Peek().GetSuit() == Card::Spade || _selected.Peek().GetSuit() == Card::Club) &&
				(_play[_colcur].Peek().GetSuit() == Card::Spade || _play[_colcur].Peek().GetSuit() == Card::Club))
				indeed = false;
			if ((_selected.Peek().GetSuit() == Card::Heart || _selected.Peek().GetSuit() == Card::Diamond) &&
				(_play[_colcur].Peek().GetSuit() == Card::Heart || _play[_colcur].Peek().GetSuit() == Card::Diamond))
				indeed = false;
			// INVALID RANK CHAIN?
			if (_selected.Peek().GetRank() != _play[_colcur].Peek().GetRank() - 1)
				indeed = false;
		}
	}
	return indeed;
}

/**********************************************************************
* Purpose: Determines if game has been won.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool GameBoard::IsVictorious()
{
	bool victory = true;

	for (int i = 0; i < 4; ++i)
		if (_home[i].isEmpty())
			victory = false;
		else if (_home[i].Peek().GetRank() != Card::King)
			victory = false;

	return victory;
}

/**********************************************************************
* Purpose: Sets free cell dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetFreeDB()
{
	_free_db = true;
}

/**********************************************************************
* Purpose: Sets home cell dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetHomeDB()
{
	_home_db = true;
}

/**********************************************************************
* Purpose: Sets game board dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetBoardDB()
{
	_board_db = true;
}

/**********************************************************************
* Purpose: Sets play cell dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetPlayDB(int c)
{
	if (c < 0 || c > 7)
		throw Exception("Invalid column!");

	_play_db[c] = true;
}

/**********************************************************************
* Purpose: Sets selected cards dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetSelectedDB()
{
	_selected_db = true;
}

/**********************************************************************
* Purpose: Sets controls dirty bit.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean set.
*
************************************************************************/
void GameBoard::SetControlsDB()
{
	_controls_db = true;
}

/**********************************************************************
* Purpose: Draws a card.
*
* Precondition:
*     None
*
* Postcondition:
*     Card drawn.
*
************************************************************************/
void GameBoard::DrawCard(Card card, int r, int c, bool full, bool allowsel, int washsize)
{
	wchar_t out;
	WORD color = F_GRAY;
	Card selected(Card(Card::Ace, Card::NOS));
	// SELECTION ALLOWED
	if (allowsel)
		selected = GetSelected();
	// SET CARD OFFSET
	_sb->SetOffset(r, c);
	if (full) // DRAW FULL CARD
	{
		// WASH SCREEN
		if (washsize != -1)
			if (washsize < 14)
				_sb->SetBlock(0, 0, ((washsize <= 0 ? -1 : washsize) - 1) * 2 + 6 +
					(_selected.isEmpty() ? 4 : 0), 6, TCHAR(0x0000), B_GREEN);
			else
				_sb->SetBlock(0, 0, _sb->GetRows() - 2, 6, TCHAR(0x0000), B_GREEN);
		// CLEAR SPACE
		_sb->SetBlock(0, 0, 4, 6, TCHAR(0x0000));
		// TOP
		_sb->SetChar(0, 0, selected == card ? TCHAR(0x2554) :
			TCHAR(0x250C), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetBlock(0, 1, 0, 5, selected == card ? TCHAR(0x2550) :
			TCHAR(0x2500), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetChar(0, 6, selected == card ? TCHAR(0x2557) :
			TCHAR(0x2510), selected == card ? F_L_YELLOW : F_GRAY);
		// SIDES
		_sb->SetBlock(1, 0, 3, 0, selected == card ? TCHAR(0x2551) :
			TCHAR(0x2502), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetBlock(1, 6, 3, 6, selected == card ? TCHAR(0x2551) :
			TCHAR(0x2502), selected == card ? F_L_YELLOW : F_GRAY);
		// BOTTOM
		_sb->SetChar(4, 0, selected == card ? TCHAR(0x255A) :
			TCHAR(0x2514), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetBlock(4, 1, 4, 5, selected == card ? TCHAR(0x2550) :
			TCHAR(0x2500), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetChar(4, 6, selected == card ? TCHAR(0x255D) :
			TCHAR(0x2518), selected == card ? F_L_YELLOW : F_GRAY);
		// RANK
		switch (card.GetRank())
		{
		case Card::NOR:		out = TCHAR(0x0000); break; // RANK NONE
		case Card::Ace:		out = TCHAR(0x0041); break;
		case Card::Jack:	out = TCHAR(0x004A); break;
		case Card::Queen:	out = TCHAR(0x0051); break;
		case Card::King:	out = TCHAR(0x004B); break;
		default:			out = TCHAR(card.GetRank() + 0x0031); break;
		}
		_sb->SetChar(1, 5, out);
		_sb->SetChar(3, 1, out);
		if (card.GetRank() == Card::Ten) // Extra character for rank 10
		{
			_sb->SetcString(1, 4, L"10");
			_sb->SetcString(3, 1, L"10");
		}
		// SUIT
		out = 0;
		switch (card.GetSuit())
		{
		case Card::NOS:		out = TCHAR(0x0000); color = F_GRAY; break; // SUIT NONE
		case Card::Spade:	out = TCHAR(0x2660); color = F_GRAY; break;
		case Card::Club:	out = TCHAR(0x2663); color = F_GRAY; break;
		case Card::Heart:	out = TCHAR(0x2665); color = F_L_RED; break;
		case Card::Diamond:	out = TCHAR(0x2666); color = F_L_RED; break;
		}
		_sb->SetChar(1, 1, out, color);
		_sb->SetChar(2, 3, out, color);
		_sb->SetChar(3, 5, out, color);
	}
	else // DRAW TOP TWO ROWS OF CARD
	{
		// CLEAR SPACE
		_sb->SetBlock(0, 0, 1, 6, TCHAR(0x0000));
		// TOP
		_sb->SetChar(0, 0, selected == card ? TCHAR(0x2554) :
			TCHAR(0x250C), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetBlock(0, 1, 0, 5, selected == card ? TCHAR(0x2550) :
			TCHAR(0x2500), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetChar(0, 6, selected == card ? TCHAR(0x2557) :
			TCHAR(0x2510), selected == card ? F_L_YELLOW : F_GRAY);
		// SIDES
		_sb->SetChar(1, 0, selected == card ? TCHAR(0x2551) :
			TCHAR(0x2502), selected == card ? F_L_YELLOW : F_GRAY);
		_sb->SetChar(1, 6, selected == card ? TCHAR(0x2551) :
			TCHAR(0x2502), selected == card ? F_L_YELLOW : F_GRAY);
		// RANK
		switch (card.GetRank())
		{
		case Card::NOR:		out = TCHAR(0x0000); break; // RANK NONE
		case Card::Ace:		out = TCHAR(0x0041); break;
		case Card::Jack:	out = TCHAR(0x004A); break;
		case Card::Queen:	out = TCHAR(0x0051); break;
		case Card::King:	out = TCHAR(0x004B); break;
		default:			out = TCHAR(card.GetRank() + 0x0031); break;
		}
		_sb->SetChar(1, 5, out);
		if (card.GetRank() == Card::Ten) // Extra character for rank 10
			_sb->SetcString(1, 4, L"10");
		// SUIT
		out = 0;
		switch (card.GetSuit())
		{
		case Card::NOS:		out = TCHAR(0x0000); color = F_GRAY; break; // SUIT NONE
		case Card::Spade:	out = TCHAR(0x2660); color = F_GRAY; break;
		case Card::Club:	out = TCHAR(0x2663); color = F_GRAY; break;
		case Card::Heart:	out = TCHAR(0x2665); color = F_L_RED; break;
		case Card::Diamond:	out = TCHAR(0x2666); color = F_L_RED; break;
		}
		_sb->SetChar(1, 1, out, color);
	}
	// DRAW CARD
	_sb->Draw();
}