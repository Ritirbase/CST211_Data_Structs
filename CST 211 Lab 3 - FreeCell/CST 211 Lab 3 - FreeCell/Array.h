/*************************************************************
* Author:			Daniel Stotts
* Filename:			Array.h
* Date Created:		3/28/2016
* Modifications:	None
**************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"

/************************************************************************
* Class: Array
*
* Purpose: This class manages a single dimension, templated, dynamic array.
*
* Manager functions:
* 	Array()
*	Array(int length, int index = 0)
*	Array (const Array & copy)
*	~Array()
*	operator = (const Array & copy)
*
* Methods:
*	operator [] (int index)
*	getStartIndex()
*	setStartIndex(int)
*	getLength()
*	setLength(int)
*************************************************************************/
template <typename T>
class Array
{
public:
	Array();
	Array(int, int = 0);
	Array(const Array<T> &);
	~Array();

	const Array<T> & operator = (const Array<T> &);

	T & operator [] (int);
	const T & operator [] (int) const;

	int GetStartIndex() const;
	void SetStartIndex(int);

	int GetLength() const;
	void SetLength(int);

private:
	T * m_array;
	int m_length;
	int m_start_index;

};

/**********************************************************************
* Purpose: Constructs an instance of an Array object.
*
* Precondition:
*     None
*
* Postcondition:
*     None
*
************************************************************************/
template <typename T>
Array<T>::Array() : 
	m_array(nullptr),
	m_length(0),
	m_start_index(0)
{ }

/**********************************************************************
* Purpose: Constructs an instance of an Array object, using two
		   integer values for configuration.
*
* Precondition:
*     None
*
* Postcondition:
*     Array configured using input.
*
************************************************************************/
template <typename T>
Array<T>::Array(int length, int start_index)
{
	if (length < 0)
		throw Exception("Length must be positive!");

	m_length = length;
	m_start_index = start_index;

	if (m_length > 0)
		m_array = new T[m_length];
	else
		m_array = nullptr;
}

/**********************************************************************
* Purpose: Constructs an instance of an Array object, using another
		   Array instance as a reference for configuration.
*
* Precondition:
*     None
*
* Postcondition:
*     Array configured using input.
*
************************************************************************/
template <typename T>
Array<T>::Array(const Array & copy) :
	m_length(copy.m_length),
	m_start_index(copy.m_start_index)
{
	m_array = new T[m_length];

	for (int i = 0; i < m_length; ++i)
		m_array[i] = copy.m_array[i];
}

/**********************************************************************
* Purpose: Destroys the instance of an Array object.
*
* Precondition:
*     None
*
* Postcondition:
*     All data members reset to their default values.
*
************************************************************************/
template <typename T>
Array<T>::~Array()
{
	if (m_array != nullptr)
	{
		delete[] m_array;
		m_array = nullptr;
	}
	m_length = 0;
	m_start_index = 0;
}

/**********************************************************************
* Purpose: Sets the instance of an Array equal to another Array instance.
*
* Precondition:
*     Source instance must not equal destination instance.
*
* Postcondition:
*     Array configured using input from other instance.
*
************************************************************************/
template <typename T>
const Array<T> & Array<T>::operator = (const Array & rhs)
{
	if (this != &rhs)
	{
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
		m_array = new T[m_length];

		for (int i = 0; i < m_length; ++i)
			m_array[i] = rhs.m_array[i];
	}
		return *this;
}

/**********************************************************************
* Purpose: Allows referencing Array elements using brackets.
*
* Precondition:
*     None
*
* Postcondition:
*     Array element returned from input index value.
*
************************************************************************/
template <typename T>
T & Array<T>::operator [] (int index)
{
	if (index < m_start_index || index >= (m_start_index + m_length))
		throw Exception("Index out of bounds!");

	return m_array[index - m_start_index];
}

/**********************************************************************
* Purpose: Allows referencing Array elements using brackets.
*
* Precondition:
*     None
*
* Postcondition:
*     Array element returned from input index value.
*
************************************************************************/
template <typename T>
const T & Array<T>::operator [] (int index) const
{
	if (index < m_start_index || index >= (m_start_index + m_length))
		throw Exception("Index out of bounds!");

	return m_array[index - m_start_index];
}

/**********************************************************************
* Purpose: Returns m_start_index member.
*
* Precondition:
*     None
*
* Postcondition:
*     Data member returned.
*
************************************************************************/
template <typename T>
int Array<T>::GetStartIndex() const
{
	return m_start_index;
}

/**********************************************************************
* Purpose: Sets m_start_index member.
*
* Precondition:
*     None
*
* Postcondition:
*     Data member set to input value.
*
************************************************************************/
template <typename T>
void Array<T>::SetStartIndex(int index)
{
	m_start_index = index;
}

/**********************************************************************
* Purpose: Returns m_length member.
*
* Precondition:
*     None
*
* Postcondition:
*     Data member returned.
*
************************************************************************/
template <typename T>
int Array<T>::GetLength() const
{
	return m_length;
}

/**********************************************************************
* Purpose: Sets m_length member.
*
* Precondition:
*     None
*
* Postcondition:
*     Data member set to input value.
*
************************************************************************/
template <typename T>
void Array<T>::SetLength(int length)
{
	if (length < 0)
		throw Exception("Length must be positive!");

	if (m_array == nullptr)
		m_array = new T[length];
	else
	{
		Array<T> temp(*this);

		delete[] m_array;
		m_array = new T[length];

		for (int i = 0; i < m_length && i < length; ++i)
			m_array[i] = temp.m_array[i];
	}
	m_length = length;
}

#endif