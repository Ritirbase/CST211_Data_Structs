/*************************************************************
* Author:			Daniel Stotts
* Filename:			Array2D.h
* Date Created:		4/5/2016
* Modifications:	None
**************************************************************/

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "Array.h"
#include "Row.h"
#include "Exception.h"

/************************************************************************
* Class: Array2D
*
* Purpose: This class manages a double dimension, templated, dynamic array.
*
* Manager functions:
* 	Array2D();
*	Array2D(int, int);
*	Array2D(const Array2D<T> &);
*	~Array2D();
*	operator = (const Array2D<T> &);
*
* Methods:
*	operator [] (int);
*	operator [] (int) const;
*	GetRow() const;
*	SetRow(int);
*	GetColumn() const;
*	SetColumn(int);
*	Select(int, int);
*	Select(int, int) const;
*************************************************************************/
template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int, int);
	Array2D(const Array2D<T> &);
	~Array2D();

	const Array2D<T> & operator = (const Array2D<T> &);

	Row<T> operator [] (int);
	const Row<T> operator [] (int) const;

	const int GetRow() const;
	void SetRow(int);

	const int GetColumn() const;
	void SetColumn(int);

	friend Row<T>;

private:
	T & Select(int, int);
	const T & Select(int, int) const;

	Array<T> m_array;
	int m_row;
	int m_column;

};

/**********************************************************************
* Purpose: Constructs an instance of an Array2D object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Array2D<T>::Array2D()
{
	m_row = 0;
	m_column = 0;
}

/**********************************************************************
* Purpose: Constructs an instance of an Array2D object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Array2D<T>::Array2D(int row, int column)
{
	if (row < 0 || column < 0)
		throw Exception("Boundaries must be positive!");

	m_row = row;
	m_column = column;
	m_array.SetLength((m_row * m_column));
}

/**********************************************************************
* Purpose: Constructs an instance of an Array2D object, using another
			Array2D to copy.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Array2D<T>::Array2D(const Array2D<T> & copy)
{
	m_row = copy.m_row;
	m_column = copy.m_column;

	m_array = copy.m_array;
}

/**********************************************************************
* Purpose: Destroys the instance of an Array2D object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
Array2D<T>::~Array2D()
{
	m_row = 0;
	m_column = 0;
}

/**********************************************************************
* Purpose: Sets instance equal to another Array2D instance.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance set equal to other instance.
*
************************************************************************/
template <typename T>
const Array2D<T> & Array2D<T>::operator = (const Array2D<T> & rhs)
{
	if (this != &rhs)
	{
		m_row = rhs.m_row;
		m_column = rhs.m_column;

		m_array = rhs.m_array;
	}
	return *this;
}

/**********************************************************************
* Purpose: Returns a row object to be used to retrieve actual data 
			element.
*
* Precondition:
*     None
*
* Postcondition:
*     Row returned.
*
************************************************************************/
template <typename T>
Row<T> Array2D<T>::operator [] (int row)
{
	return Row<T>(*this, row);
}

/**********************************************************************
* Purpose: Returns a const row object to be used to retrieve actual 
			data element.
*
* Precondition:
*     None
*
* Postcondition:
*     Row returned.
*
************************************************************************/
template <typename T>
const Row<T> Array2D<T>::operator [] (int row) const
{
	return Row<T>(*this, row);
}

/**********************************************************************
* Purpose: Returns row data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Row data member returned.
*
************************************************************************/
template <typename T>
const int Array2D<T>::GetRow() const
{
	return m_row;
}

/**********************************************************************
* Purpose: Sets row data member.
*
* Precondition:
*     None
*
* Postcondition:
*     Row data member set.
*
************************************************************************/
template <typename T>
void Array2D<T>::SetRow(int row)
{
	if (row < 0)
		throw Exception("Value must be positive!");

	Array2D<T> temp(*this);

	m_array = Array<T>((row * m_column));
	m_row = row;

	for (int x = 0; x < temp.m_row && x < row; ++x)
		for (int y = 0; y < m_column; ++y)
			Select(x, y) = temp.Select(x, y);

}

/**********************************************************************
* Purpose: Sets column data member.
*
* Precondition:
*     None
*
* Postcondition:
*     column data member set.
*
************************************************************************/
template <typename T>
const int Array2D<T>::GetColumn() const
{
	return m_column;
}

/**********************************************************************
* Purpose: Sets column data member.
*
* Precondition:
*     None
*
* Postcondition:
*     column data member set.
*
************************************************************************/
template <typename T>
void Array2D<T>::SetColumn(int column)
{
	if (column < 0)
		throw Exception("Value must be positive!");

	Array2D<T> temp(*this);

	m_array = Array<T>((m_row * column));
	m_column = column;

	for (int x = 0; x < m_row; ++x)
		for (int y = 0; y < temp.m_column && y < column; ++y)
			Select(x, y) = temp.Select(x, y);
}

/**********************************************************************
* Purpose: Returns data at specified "row" and "column" location.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element returned from specified location.
*
************************************************************************/
template <typename T>
T & Array2D<T>::Select(int row, int column)
{
	//if ((row * column) < 0 || (row * column) >= (m_row * m_column))
	if (row < 0 || row >= m_row || column < 0 || column >= m_column)
		throw Exception("Index out of bounds!");

	return m_array[((row * m_column) + column)];
}

template <typename T>
const T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0 || row >= m_row || column < 0 || column >= m_column)
		throw Exception("Index out of bounds!");

	return m_array[((row * m_column) + column)];
}

#endif