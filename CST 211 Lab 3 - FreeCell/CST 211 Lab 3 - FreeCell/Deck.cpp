/*************************************************************
* Author:			Daniel Stotts
* Filename:			Deck.cpp
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#include "Deck.h"

/**********************************************************************
* Purpose: Constructs an instance of a Deck object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
Deck::Deck() :
	m_cards(52),
	m_discards(52)
{
	for (int s = 0; s < 4; ++s)
		for (int r = 0; r < 13; ++r)
			m_cards.Push(Card(static_cast<Card::Rank>(r),
				static_cast<Card::Suit>(s)));
}

/**********************************************************************
* Purpose: Constructs an instance of a Deck object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
Deck::Deck(const Deck & copy) :
	m_cards(copy.m_cards),
	m_discards(copy.m_discards)
{ }

/**********************************************************************
* Purpose: Destroys the instance of a Deck object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
Deck::~Deck()
{

}

/**********************************************************************
* Purpose: Sets this deck equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
const Deck & Deck::operator = (const Deck & rhs)
{
	if (this != &rhs)
	{
		m_cards = rhs.m_cards;
		m_discards = rhs.m_discards;
	}
	return *this;
}

/**********************************************************************
* Purpose: Deals a card.
*
* Precondition:
*     None
*
* Postcondition:
*     Card returned.
*
************************************************************************/
Card Deck::Deal()
{
	Card returndata = m_cards.Pop();
	m_discards.Push(returndata);
	return returndata;
}

/**********************************************************************
* Purpose: Adds all dealt cards back to the deck.
*
* Precondition:
*     None
*
* Postcondition:
*     Cards returned to deck stack.
*
************************************************************************/
void Deck::Rebuild()
{
	for (int i = 0; i < m_discards.Size() + i; ++i)
		m_cards.Push(m_discards.Pop());
}

/**********************************************************************
* Purpose: Shuffles the deck of cards.
*
* Precondition:
*     None
*
* Postcondition:
*     Cards shuffled.
*
************************************************************************/
void Deck::Shuffle()
{
	srand(time(nullptr));

	Card temp[52];

	Rebuild();
	for (int i = 0; i < 52; ++i)
		temp[i] = m_cards.Pop();

	random_shuffle(&temp[0], &temp[52]);

	for (int i = 0; i < 52; ++i)
		m_cards.Push(temp[i]);
}