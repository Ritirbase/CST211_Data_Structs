#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

//#include <iostream>
//using std::cout;
//using std::endl;
//using std::wcout;

//#include "Deck.h"
#include "ScreenBuffer.h"
//#include "GameBoard.h"
//#include "KBInput.h"

#include "FreeCell.h"

#ifndef ATTEMPT
#include <iostream>
using std::cout; using std::endl;
#include "Exception.h"
#define ATTEMPT(function) try { function; } catch(Exception msg) { cout \
	<< " Location: " << __LINE__ << "\tError: <" << msg << '>' << endl; }
#endif

using std::wcout;

//void DrawCard(Card, int = 0, int = 0);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FreeCell a;
	a.Play();

	////_setmode(_fileno(stdout), _O_WTEXT);
	////wcout << L'\u2660' << endl;
	////wcout << TCHAR(0x2660) << endl;

	//ScreenBuffer * sb = ScreenBuffer::GetInstance();

	//sb->Clear();
	//sb->SetOrigin(2, 2);
	//b.DrawBoard();
	//b.DrawFree();
	//b.DrawHome();
	//b.DrawPlay();

	//sb->SetOrigin(2, 2);
	//sb->SetBlock(0, 0, sb->GetRows() - 1, sb->GetColumns() - 1, TCHAR(0x0000), B_L_GREEN);
	//sb->SetBlock(1, 1, sb->GetRows() - 2, sb->GetColumns() - 2, TCHAR(0x0000), B_GREEN);
	//sb->Draw();

	////ATTEMPT(sb->SetChar(0, 87, TCHAR(0x0000)));

	//Deck a;
	//a.Rebuild();
	//a.Shuffle();
	//Card b = a.Deal();
	//a.Rebuild();
	//a.Shuffle();

	//Card d(Card::Five, Card::Club);
	//Card e(Card::Six, Card::Diamond);

	//// ORIGIN OF BUFFER
	//// Draw test card(s)
	//DrawCard(d, 2, 2);
	//DrawCard(e, 4, 2);
	//DrawCard(Card(Card::King, Card::Heart), 6, 2);

	///*sb->SetChar(3, 2, TCHAR(0x2660));
	//sb->SetChar(3, 1, L'\u0061');s
	//sb->SetcString(2, 1, L"hello");
	//sb->Draw();

	//sb->SetChar(4, 4, char(0x183));
	//sb->Draw();*/

	ScreenBuffer::DeleteInstance();
	return 0;
}

//void DrawCard(Card card, int R, int C)
//{
//	ScreenBuffer * sb = ScreenBuffer::GetInstance();
//	wchar_t out;
//	WORD color = F_GRAY;
//	// SET CARD OFFSET
//	sb->SetOffset(R, C);
//	// CLEAR SPACE
//	sb->SetBlock(0, 0, 4, 6, TCHAR(0x0000));
//	// TOP
//	sb->SetChar(0, 0, TCHAR(0x250C));
//	sb->SetBlock(0, 1, 0, 5, TCHAR(0x2500));
//	sb->SetChar(0, 6, TCHAR(0x2510));
//	// SIDES
//	sb->SetBlock(1, 0, 3, 0, TCHAR(0x2502));
//	sb->SetBlock(1, 6, 3, 6, TCHAR(0x2502));
//	// BOTTOM
//	sb->SetChar(4, 0, TCHAR(0x2514));
//	sb->SetBlock(4, 1, 4, 5, TCHAR(0x2500));
//	sb->SetChar(4, 6, TCHAR(0x2518));
//	// RANK
//	switch (card.GetRank())
//	{
//	case 0:  out = TCHAR(0x0041); break;
//	case 10: out = TCHAR(0x004A); break;
//	case 11: out = TCHAR(0x0051); break;
//	case 12: out = TCHAR(0x004B); break;
//	default: out = TCHAR(card.GetRank() + 0x0031); break;
//	}
//	sb->SetChar(1, 5, out);
//	sb->SetChar(3, 1, out);
//	if (card.GetRank() == 9) // Extra character for rank 10
//	{
//		sb->SetcString(1, 4, L"10");
//		sb->SetcString(3, 1, L"10");
//	}
//	// SUIT
//	out = 0;
//	switch(card.GetSuit())
//	{
//	case Card::Spade:	out = TCHAR(0x2660); color = F_GRAY; break;
//	case Card::Club:	out = TCHAR(0x2663); color = F_GRAY; break;
//	case Card::Heart:	out = TCHAR(0x2665); color = F_L_RED; break;
//	case Card::Diamond:	out = TCHAR(0x2666); color = F_L_RED; break;
//	}
//	sb->SetChar(1, 1, out, color);
//	sb->SetChar(2, 3, out, color);
//	sb->SetChar(3, 5, out, color);
//
//	// DRAW CARD
//	sb->Draw();
//}