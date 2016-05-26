/*************************************************************
* Author:			Daniel Stotts
* Filename:			Card.cpp
* Date Created:		4/22/2016
* Modifications:	None
**************************************************************/

#include "Card.h"

//Card::Card() :
//	m_rank(NOR),
//	m_suit(NOS)
//{ }

/**********************************************************************
* Purpose: Constructs an instance of a Card object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
Card::Card(Rank rank, Suit suit) :
	m_rank(rank),
	m_suit(suit)
{ }

/**********************************************************************
* Purpose: Constructs an instance of a Card object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
Card::Card(const Card & copy) :
	m_rank(copy.m_rank),
	m_suit(copy.m_suit)
{ }

/**********************************************************************
* Purpose: Destroys the instance of a Card object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
Card::~Card()
{

}

/**********************************************************************
* Purpose: Sets this card object equal to another.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance copied.
*
************************************************************************/
const Card & Card::operator = (const Card & rhs)
{
	if (this != &rhs)
	{
		m_rank = rhs.m_rank;
		m_suit = rhs.m_suit;
	}
	return *this;
}

/**********************************************************************
* Purpose: Determines whether another card is the same as this one.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool Card::operator == (const Card & rhs) const
{
	return ((m_rank == rhs.m_rank && m_suit == rhs.m_suit) ? true : false);
}

/**********************************************************************
* Purpose: Determines whether another card is not the same as this one.
*
* Precondition:
*     None
*
* Postcondition:
*     Boolean returned.
*
************************************************************************/
bool Card::operator != (const Card & rhs) const
{
	return ((m_rank != rhs.m_rank || m_suit != rhs.m_suit) ? true : false);
}

/**********************************************************************
* Purpose: Returns rank of card.
*
* Precondition:
*     None
*
* Postcondition:
*     Value returned.
*
************************************************************************/
Card::Rank Card::GetRank() const
{
	return m_rank;
}

/**********************************************************************
* Purpose: Sets rank of card.
*
* Precondition:
*     None
*
* Postcondition:
*     Value set.
*
************************************************************************/
void Card::SetRank(Rank rank)
{
	m_rank = rank;
}

/**********************************************************************
* Purpose: Returns suit of card.
*
* Precondition:
*     None
*
* Postcondition:
*     Value returned.
*
************************************************************************/
Card::Suit Card::GetSuit() const
{
	return m_suit;
}

/**********************************************************************
* Purpose: Sets suit of card.
*
* Precondition:
*     None
*
* Postcondition:
*     Value set.
*
************************************************************************/
void Card::SetSuit(Suit suit)
{
	m_suit = suit;
}
