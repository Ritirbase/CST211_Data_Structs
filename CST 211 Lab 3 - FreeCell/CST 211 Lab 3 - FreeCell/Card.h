/*************************************************************
* Author:			Daniel Stotts
* Filename:			Card.h
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#ifndef CARD_H
#define CARD_H

/************************************************************************
* Class: Card
*
* Purpose: This class implements a generic card.
*
* Manager functions:
* 	Card(Rank, Suit);
*	Card(const Card &);
*	~Card();
*	operator = (const Card &);
*
* Methods:
*	operator == (const Card &) const;
*	operator != (const Card &) const;
*	GetRank() const;
*	SetRank(Rank);
*	GetSuit() const;
*	SetSuit(Suit);
*************************************************************************/
class Card
{
public:
	enum Rank
	{
		NOR = -1, Ace, Two, Three, Four,
		Five, Six, Seven, Eight, Nine,
		Ten, Jack, Queen, King
	};
	enum Suit
	{
		NOS = -1, Spade, Club,
		Heart, Diamond,
	};
	//Card();
	Card(Rank = NOR, Suit = NOS); // Defines card in order of general english description. Eg. "A nine of diamonds"
	Card(const Card &);
	~Card();

	const Card & operator = (const Card &);

	bool operator == (const Card &) const;
	bool operator != (const Card &) const;

	Rank GetRank() const;
	void SetRank(Rank);
	Suit GetSuit() const;
	void SetSuit(Suit);

private:
	Rank m_rank;
	Suit m_suit;

};

#endif