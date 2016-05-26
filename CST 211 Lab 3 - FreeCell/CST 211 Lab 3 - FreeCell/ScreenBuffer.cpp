/*************************************************************
* Author:			Daniel Stotts
* Filename:			ScreenBuffer.cpp
* Date Created:		4/6/2016
* Modifications:	4/24/2016 - Modified for use with Unicode
**************************************************************/

#include "ScreenBuffer.h"
#include "Exception.h"

ScreenBuffer * ScreenBuffer::_instance = nullptr;

/**********************************************************************
* Purpose: Returns a reference to the single ScreenBuffer instance.
*
* Precondition:
*     None
*
* Postcondition:
*     Reference to instance returned.
*
************************************************************************/
ScreenBuffer * ScreenBuffer::GetInstance()
{
	if (_instance == nullptr)
		_instance = new ScreenBuffer();
	return _instance;
}

/**********************************************************************
* Purpose: Deletes the single ScreenBuffer instance.
*
* Precondition:
*     None
*
* Postcondition:
*	  Instance deleted.
*
************************************************************************/
void ScreenBuffer::DeleteInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

/**********************************************************************
* Purpose: Constructs the instance of the ScreenBuffer object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance of ScreenBuffer created.
*
************************************************************************/
ScreenBuffer::ScreenBuffer() :
	_hStdout(GetStdHandle(STD_OUTPUT_HANDLE)),
	_chbuf_size{ SB_WIDTH, SB_HEIGHT },
	_chbuf_coord{ 0, 0 },
	_write_area{ 0, 0, SB_WIDTH - 1, SB_HEIGHT - 1 },
	_origin_r(0), _offset_r(0),
	_origin_c(0), _offset_c(0)
{
	for (int i = 0; i < SB_WIDTH * SB_HEIGHT; ++i)
	{
		_chbuf[i].Char.UnicodeChar = wchar_t(0);
		_chbuf[i].Attributes = F_GRAY;
	}
}

/**********************************************************************
* Purpose: Destroys the instance of the ScreenBuffer object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance of ScreenBuffer destroyed.
*
************************************************************************/
ScreenBuffer::~ScreenBuffer()
{
	
}

/**********************************************************************
* Purpose: Sets the "origin" all coordinates will originate from.
*
* Precondition:
*     None
*
* Postcondition:
*     Origin "coordinate" set.
*
************************************************************************/
void ScreenBuffer::SetOrigin(int r, int c)
{
	if (r < 0 || c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (r > SB_HEIGHT - 1 || c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	_origin_r = r;
	_origin_c = c;
}

/**********************************************************************
* Purpose: Sets the "offset" all coordinates will originate from.
			Also considers origin.
*
* Precondition:
*     None
*
* Postcondition:
*     Offset "coordinate" set.
*
************************************************************************/
void ScreenBuffer::SetOffset(int r, int c)
{
	if (_origin_r + r < 0 || _origin_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + r > SB_HEIGHT - 1 || _origin_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	_offset_r = r;
	_offset_c = c;
}

/**********************************************************************
* Purpose: Returns current offset, within a coordinate struct.
*
* Precondition:
*     None
*
* Postcondition:
*     Offset coordinate returned.
*
************************************************************************/
ScreenBuffer::PointRC ScreenBuffer::GetOffset() const
{
	return PointRC{ static_cast<short>(_offset_r),static_cast<short>(_offset_c) };
}

/**********************************************************************
* Purpose: Draws all characters in character buffer to the console window.
*
* Precondition:
*     None
*
* Postcondition:
*     _chbuf drawn.
*
************************************************************************/
void ScreenBuffer::Draw()
{
	WriteConsoleOutputW(_hStdout, _chbuf, _chbuf_size, _chbuf_coord, &_write_area);
}

/**********************************************************************
* Purpose: Resets all cells in character buffer to default values.
*
* Precondition:
*     None
*
* Postcondition:
*     _chbuf reset to default.
*
************************************************************************/
void ScreenBuffer::Clear()
{
	_origin_r = 0; 	_offset_r = 0;
	_origin_c = 0; 	_offset_c = 0;

	for (int i = 0; i < SB_WIDTH * SB_HEIGHT; ++i)
	{
		_chbuf[i].Char.UnicodeChar = wchar_t(0);
		_chbuf[i].Attributes = F_GRAY;
	}
}

/**********************************************************************
* Purpose: Sets a length of characters equal to a string, beginning
			at a specified coordinate.
*
* Precondition:
*     None
*
* Postcondition:
*     cString set at location.
*
************************************************************************/
void ScreenBuffer::SetcString(int r, int c, wchar_t * a, WORD p)
{
	if (_origin_r + _offset_r + r < 0 || _origin_c + _offset_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + _offset_r + r > SB_HEIGHT - 1 || _origin_c + _offset_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	if (_origin_c + _offset_c + c + wcslen(a) > SB_WIDTH - 1)
		throw Exception("cString size must not exceed horizontal boundary!");

	for (int i = 0; i < wcslen(a); ++i)
		SetChar(r, c + i, a[i], p);
}

/**********************************************************************
* Purpose: Sets a character at a specified coordinate to a specified
			character.
*
* Precondition:
*     None
*
* Postcondition:
*     Character set at location.
*
************************************************************************/
void ScreenBuffer::SetChar(int r, int c, wchar_t a, WORD p)
{
	if (_origin_r + _offset_r + r < 0 || _origin_c + _offset_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + _offset_r + r > SB_HEIGHT - 1 || _origin_c + _offset_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	_chbuf[((r + _origin_r + _offset_r) * SB_WIDTH) + (c + _origin_c + _offset_c)].Char.UnicodeChar = a;
	SetCharAttribute(r, c, p);
}

/**********************************************************************
* Purpose: Returns Unicode character data from a specified coordinate.
*
* Precondition:
*     None
*
* Postcondition:
*     Unicode character at location returned.
*
************************************************************************/
wchar_t ScreenBuffer::GetChar(int r, int c) const
{
	if (_origin_r + _offset_r + r < 0 || _origin_c + _offset_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + _offset_r + r > SB_HEIGHT - 1 || _origin_c + _offset_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	return _chbuf[((r + _origin_r + _offset_r) * SB_WIDTH) + (c + _origin_c + _offset_c)].Char.UnicodeChar;
}

/**********************************************************************
* Purpose: Sets attribute data at a specified coordinate.
*
* Precondition:
*     None
*
* Postcondition:
*     Attributes of selected block set.
*
************************************************************************/
void ScreenBuffer::SetCharAttribute(int r, int c, WORD a)
{
	if (_origin_r + _offset_r + r < 0 || _origin_c + _offset_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + _offset_r + r > SB_HEIGHT - 1 || _origin_c + _offset_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	_chbuf[((r + _origin_r + _offset_r) * SB_WIDTH) + (c + _origin_c + _offset_c)].Attributes = a;
}

/**********************************************************************
* Purpose: Returns attribute data from a specified coordinate.
*
* Precondition:
*     None
*
* Postcondition:
*     Character attributes at location returned.
*
************************************************************************/
WORD ScreenBuffer::GetCharAttribute(int r, int c) const
{
	if (_origin_r + _offset_r + r < 0 || _origin_c + _offset_c + c < 0)
		throw Exception("Coordinate must not lie outside of boundary!");
	if (_origin_r + _offset_r + r > SB_HEIGHT - 1 || _origin_c + _offset_c + c > SB_WIDTH - 1)
		throw Exception("Coordinate must not lie outside of boundary!");

	return _chbuf[((r + _origin_r + _offset_r) * SB_WIDTH) + (c + _origin_c + _offset_c)].Attributes;
}

/**********************************************************************
* Purpose: Sets all characters between two specifed coordinates to a
			specified character.
*
* Precondition:
*     None
*
* Postcondition:
*     Block set at location.
*
************************************************************************/
void ScreenBuffer::SetBlock(int r1, int c1, int r2, int c2, wchar_t a, WORD p)
{
	if (_origin_r + _offset_r + r1 < 0 || _origin_c + _offset_c + c1 < 0 || _origin_r + _offset_r + r2 < 0 || _origin_c + _offset_c + c2 < 0)
		throw Exception("Coordinates must not lie outside of boundary!");
	if (_origin_r + _offset_r + r1 > SB_HEIGHT - 1 || _origin_c + _offset_c + c1 > SB_WIDTH - 1 || _origin_r + _offset_r + r2 > SB_HEIGHT - 1 || _origin_c + _offset_c + c2 > SB_WIDTH - 1)
		throw Exception("Coordinates must not lie outside of boundary!");

	if (c1 > c2)
	{
		c1 ^= c2; c2 ^= c1; c1 ^= c2; // XOR swap
	}

	if (r1 > r2)
	{
		r1 ^= r2; r2 ^= r1; r1 ^= r2; // XOR swap
	}

	for (int x = 0; x <= r2 - r1; ++x)
		for (int y = 0; y <= c2 - c1; ++y)
			SetChar(x + r1, y + c1, a);

	SetBlockAttribute(r1, c1, r2, c2, p);
}

/**********************************************************************
* Purpose: Sets attribute data at all coordinates between two
			specified coordinates.
*
* Precondition:
*     None
*
* Postcondition:
*     Character attributes at location set.
*
************************************************************************/
void ScreenBuffer::SetBlockAttribute(int r1, int c1, int r2, int c2, WORD a)
{
	if (_origin_r + _offset_r + r1 < 0 || _origin_c + _offset_c + c1 < 0 || _origin_r + _offset_r + r2 < 0 || _origin_c + _offset_c + c2 < 0)
		throw Exception("Coordinates must not lie outside of boundary!");
	if (_origin_r + _offset_r + r1 > SB_HEIGHT - 1 || _origin_c + _offset_c + c1 > SB_WIDTH - 1 || _origin_r + _offset_r + r2 > SB_HEIGHT - 1 || _origin_c + _offset_c + c2 > SB_WIDTH - 1)
		throw Exception("Coordinates must not lie outside of boundary!");

	if (c1 > c2)
	{
		c1 ^= c2; c2 ^= c1; c1 ^= c2; // XOR swap
	}

	if (r1 > r2)
	{
		r1 ^= r2; r2 ^= r1; r1 ^= r2; // XOR swap
	}

	for (int x = 0; x <= r2 - r1; ++x)
		for (int y = 0; y <= c2 - c1; ++y)
			SetCharAttribute(x + r1, y + c1, a);
}

int ScreenBuffer::GetRows() const
{
	return (SB_HEIGHT - _origin_r - _offset_r);
}

int ScreenBuffer::GetColumns() const
{
	return (SB_WIDTH - _origin_c - _offset_c);
}