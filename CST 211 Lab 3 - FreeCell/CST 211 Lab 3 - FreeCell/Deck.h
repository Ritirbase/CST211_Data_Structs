/*************************************************************
* Author:			Daniel Stotts
* Filename:			Deck.h
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#ifndef DECK_H
#define DECK_H

#include <ctime>
#include <algorithm>
using std::random_shuffle;

#include "Card.h"
#include "ArrayStack.h"

/************************************************************************
* Class: Card
*
* Purpose: This class implements a generic deck of cards.
*
* Manager functions:
* 	Deck();
*	Deck(const Deck &);
*	~Deck();
*	operator = (const Deck &);
*
* Methods:
*	Deal();
*	void Rebuild();
*	void Shuffle();
*************************************************************************/
class Deck
{
public:
	Deck();
	Deck(const Deck &);
	~Deck();

	const Deck & operator = (const Deck &);

	Card Deal();

	void Rebuild();
	void Shuffle();

private:
	ArrayStack<Card> m_cards;
	ArrayStack<Card> m_discards;
};

#endif