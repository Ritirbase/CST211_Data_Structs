#include "FreeCell.h"

/**********************************************************************
* Purpose: Constructs an instance of a FreeCell object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
FreeCell::FreeCell() :
	_gb(_deck),
	_exit(false),
	_offset(0),
	_smaller(false),
	_stacksplit(false),
	_win(false),
	_tv(0),
	_th(0),
	_vertical(0),
	_horizontal(0)
{
	for (int i = 0; i < 4; ++i)
		_placedfree[i] = false;
}

/**********************************************************************
* Purpose: Constructs an instance of a FreeCell object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
FreeCell::FreeCell(const FreeCell & copy) :
	_deck(copy._deck),
	_gb(_deck),
	_kbi(copy._kbi),
	_exit(copy._exit),
	_offset(copy._offset),
	_smaller(copy._smaller),
	_stacksplit(copy._stacksplit),
	_win(copy._win),
	_tv(copy._tv),
	_th(copy._th),
	_vertical(copy._vertical),
	_horizontal(copy._horizontal)
{
	for (int i = 0; i < 4; ++i)
		_placedfree[i] = copy._placedfree[i];
}

/**********************************************************************
* Purpose: Destroys an instance of a FreeCell object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
FreeCell::~FreeCell()
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
const FreeCell & FreeCell::operator = (const FreeCell & rhs)
{
	if (this != &rhs)
	{
		_deck = rhs._deck;
		_gb = rhs._gb;
		_kbi = rhs._kbi;
		_exit = rhs._exit;
		_offset = rhs._offset;
		_smaller = rhs._smaller;
		_stacksplit = rhs._stacksplit;
		_win = rhs._win;
		_tv = rhs._tv;
		_th = rhs._th;
		_vertical = rhs._vertical;
		_horizontal = rhs._horizontal;
		for (int i = 0; i < 4; ++i)
			_placedfree[i] = rhs._placedfree[i];
	}
	return *this;
}

/**********************************************************************
* Purpose: Implements a game of FreeCell.
*
* Precondition:
*     None
*
* Postcondition:
*     Game completed.
*
************************************************************************/
void FreeCell::Play()
{
	_gb.SetSelected(0, 0);
	_gb.DrawBoard();
	_gb.DrawFree();
	_gb.DrawHome();
	_gb.DrawPlay();
	_gb.DrawSelected();
	_gb.DrawControls();

	bool success = false;
	bool force = false;

	while (!_exit && !_win)
	{
		_kbi.WaitKey();
		if (_kbi.GetKey() == KB_Q)
		{
			_kbi.WaitKey();
			if (_kbi.GetKey() == KB_F)
			{
				force = true;
				_kbi.WaitKey();
			}
			if (_kbi.GetKey() == KB_Q)
				_exit = true;
			if (_kbi.GetKey() == KB_R)
				_win = true;
		}
		switch (_kbi.GetKey())
		{
		case KB_SPACE:
		case KB_E:
			if (_stacksplit)
			{
				if (_gb.CanPlace() || force)
				{
					_gb.PlaceSelected();
					_vertical = 0;
					_gb.SetSelected(0, _horizontal);
				}
				else
				{
					_gb.SetPlayDB(_horizontal);
					_gb.SetPlayDB(_th);
					_horizontal = _th;
					_gb.SetSelected(0, _th);
					_gb.PlaceSelected();
					_vertical = 0;
				}
				_stacksplit = false;
			}
			else
			{
				if (_gb.CanSplit() || force)
				{
					//_tv = _gb.GetRowCur();
					_th = _gb.GetColCur();
					_gb.SplitStack();
					_vertical = 0;
					_stacksplit = true;
				}
			}
			_gb.SetSelectedDB();
			break;
		case KB_ONE:
		case KB_TWO:
		case KB_THREE:
		case KB_FOUR:
			if (!_stacksplit)
			{
				if (_placedfree[_kbi.GetKey() - 0x31])
				{
					if (_gb.CanReintroFree(_kbi.GetKey() - 0x31) || force)
					{
						_gb.ReintroFree(_kbi.GetKey() - 0x31);
						_vertical = 0;
						_gb.SetSelected(_vertical, _horizontal);
						_placedfree[_kbi.GetKey() - 0x31] = false;
					}
				}
				else
				{
					if (_vertical == 0)
					{
						_gb.PlaceFree(_kbi.GetKey() - 0x31);
						_gb.SetSelected(0, _horizontal);
						_placedfree[_kbi.GetKey() - 0x31] = true;
					}
				}
			}
			break;
		case KB_R:
			if (!_stacksplit)
			{
				bool placed = false;
				_tv = _vertical;
				_vertical = 0;
				_gb.SetSelected(_vertical, _horizontal);
				for (int i = 0; i < 4 && !placed; ++i)
				{
					if (_gb.CanPlaceHome(i))
					{
						_gb.PlaceHome(i);
						placed = true;
					}
				}
				_vertical = _tv + (placed == true ? -1 : 0);
				if (_vertical < 0) _vertical = 0;
				_gb.SetSelected(_vertical, _horizontal);
				//_gb.SetPlayDB(_horizontal);
			}
			break;
		case KB_FIVE:
		case KB_SIX:
		case KB_SEVEN:
		case KB_EIGHT:
			//if (!_stacksplit)
			//{
			success = _gb.MoveToHome(_kbi.GetKey() - 0x35);
				if (success) _placedfree[_kbi.GetKey() - 0x35] = false;
			_gb.SetFreeDB();
			_gb.SetHomeDB();
			/*if (_gb.CanPlaceHome(_kbi.GetKey() - 0x35))
			{
				if (_vertical == 0)
				{
					_gb.PlaceHome(_kbi.GetKey() - 0x35);
					_gb.SetSelected(0, _horizontal);
				}
			}*/
			//}
			break;
		case KB_UP: if (_vertical < _gb.GetColumnSize(_horizontal) - 1)
		{
			++_vertical;
			_gb.SetSelectedRef(_vertical, _horizontal);
			_gb.SetPlayDB(_horizontal);
		}
					break;
		case KB_DOWN: if (_vertical > 0)
		{
			--_vertical;
			_gb.SetSelectedRef(_vertical, _horizontal);
			_gb.SetPlayDB(_horizontal);
		}
					  break;
		case KB_LEFT: if (_horizontal > 0)
		{
			_offset = _gb.GetColumnSize(_horizontal - 1) - _gb.GetColumnSize(_horizontal);
			_smaller = (_gb.GetColumnSize(_horizontal - 1) <= _gb.GetColumnSize(_horizontal) - _gb.GetRowCur() ? true : false);

			_gb.SetPlayDB(_horizontal);
			_gb.SetPlayDB(_horizontal - 1);

			if (_offset == _gb.GetColumnSize(--_horizontal))
				--_vertical;

			_gb.SetSelectedRef(_vertical, _horizontal, _offset, _smaller);
		}
					  break;
		case KB_RIGHT: if (_horizontal < 7)
		{
			_offset = _gb.GetColumnSize(_horizontal + 1) - _gb.GetColumnSize(_horizontal);
			_smaller = (_gb.GetColumnSize(_horizontal + 1) <= _gb.GetColumnSize(_horizontal) - _gb.GetRowCur() ? true : false);

			_gb.SetPlayDB(_horizontal);
			_gb.SetPlayDB(_horizontal + 1);

			if (_offset == _gb.GetColumnSize(++_horizontal))
				--_vertical;

			_gb.SetSelectedRef(_vertical, _horizontal, _offset, _smaller);
		}
					   break;
		}
		_gb.DrawBoard();
		_gb.DrawFree();
		_gb.DrawHome();
		_gb.DrawPlay();
		_gb.DrawSelected();

		force = false;

		if (_gb.IsVictorious())
			_win = true;
	}
}