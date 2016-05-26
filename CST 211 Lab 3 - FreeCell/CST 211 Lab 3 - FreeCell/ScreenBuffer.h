/*************************************************************
* Author:			Daniel Stotts
* Filename:			ScreenBuffer.h
* Date Created:		4/6/2016
* Modifications:	4/24/2016 - Modified for use with Unicode 
					4/24/2016 - Additional functionality added
**************************************************************/

#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <Windows.h>

#ifndef SB_WIDTH
#define SB_WIDTH 116
#endif

#ifndef SB_HEIGHT
#define SB_HEIGHT 59 // 122
#endif

#ifndef FOREGROUND_COLORS
#define FOREGROUND_COLORS

#define F_GRAY (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define F_L_GRAY (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define F_D_GRAY (FOREGROUND_INTENSITY)

#define F_RED (FOREGROUND_RED)
#define F_L_RED (FOREGROUND_RED | FOREGROUND_INTENSITY)

#define F_GREEN (FOREGROUND_GREEN)
#define F_L_GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#define F_BLUE (FOREGROUND_BLUE)
#define F_L_BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define F_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define F_L_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#define F_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define F_L_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define F_PURPLE (FOREGROUND_BLUE | FOREGROUND_RED)
#define F_L_PURPLE (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#endif

#ifndef BACKGROUND_COLORS
#define BACKGROUND_COLORS

#define B_GRAY (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define B_L_GRAY (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define B_D_GRAY (BACKGROUND_INTENSITY)

#define B_RED (BACKGROUND_RED)
#define B_L_RED (BACKGROUND_RED | BACKGROUND_INTENSITY)

#define B_GREEN (BACKGROUND_GREEN)
#define B_L_GREEN (BACKGROUND_GREEN | BACKGROUND_INTENSITY)

#define B_BLUE (BACKGROUND_BLUE)
#define B_L_BLUE (BACKGROUND_BLUE | BACKGROUND_INTENSITY)

#define B_YELLOW (BACKGROUND_RED | BACKGROUND_GREEN)
#define B_L_YELLOW (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY)

#define B_CYAN (BACKGROUND_GREEN | BACKGROUND_BLUE)
#define B_L_CYAN (BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY)

#define B_PURPLE (BACKGROUND_BLUE | BACKGROUND_RED)
#define B_L_PURPLE (BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY)
#endif

/************************************************************************
* Class: ScreenBuffer
*
* Purpose: Manages console display.
*
* Manager functions:
* 	ScreenBuffer();
*	~ScreenBuffer();
*
* Methods:
*	GetInstance();
*	SetOrigin(int, int);
*	SetOffset(int, int);
*	GetOffset() const;
*	Draw();
*	Clear();
*	SetcString(int, int, wchar_t *, WORD = F_GRAY);
*	SetChar(int, int, wchar_t, WORD = F_GRAY);
*	SetBlock(int, int, int, int, wchar_t, WORD = F_GRAY);
*	SetCharAttribute(int, int, WORD);
*	GetCharAttribute(int, int) const;
*	SetBlockAttribute(int, int, int, int, WORD);
*************************************************************************/
class ScreenBuffer
{
public:
	struct PointRC {
		short R;
		short C;
	};

	static ScreenBuffer * GetInstance();
	static void DeleteInstance();
	~ScreenBuffer();

	void SetOrigin(int, int); // R, C

	void SetOffset(int, int); // R, C
	PointRC GetOffset() const;
	
	void Draw();
	void Clear();

	void SetcString(int, int, wchar_t *, WORD = F_GRAY); // Use L with \u or TCHAR for this. eg TCHAR(0x2660), L'\u0041', L"Hello!"

	void SetChar(int, int, wchar_t, WORD = F_GRAY); // R, C, TCHAR (wide character)
	wchar_t GetChar(int, int) const;

	void SetCharAttribute(int, int, WORD); // R, C
	WORD GetCharAttribute(int, int) const;

	void SetBlock(int, int, int, int, wchar_t, WORD = F_GRAY); // Can also be used for lines // ULY (R), ULX (C), BRY (R), BRX (C), TCHAR (wide character)
	void SetBlockAttribute(int, int, int, int, WORD); // Can also be used for flat lines // ULY (R), ULX (C), BRY (R), BRX (C), TCHAR (wide character)
	// Typical Attributes:
	// FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
	// BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY

	int GetRows() const;
	int GetColumns() const;

protected:
	ScreenBuffer();

private:
	static ScreenBuffer * _instance;

	HANDLE _hStdout;
	CHAR_INFO _chbuf[SB_WIDTH * SB_HEIGHT];
	COORD _chbuf_size;
	COORD _chbuf_coord;
	SMALL_RECT _write_area;

	int _origin_r, _offset_r;
	int _origin_c, _offset_c;

};

#endif