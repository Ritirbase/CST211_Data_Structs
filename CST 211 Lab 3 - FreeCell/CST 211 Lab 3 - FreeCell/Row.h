/*************************************************************
* Author:			Daniel Stotts
* Filename:			Row.h
* Date Created:		4/4/2016
* Modifications:	None
**************************************************************/

#ifndef ROW_H
#define ROW_H

template <typename T>
class Array2D;

/************************************************************************
* Class: Row
*
* Purpose: This class allows a second operator[] to function, ultimately
			enabling two dimension array notation.
*
* Manager functions:
* 	Row();
*	Row(const Array2D<T> &, int);
*	Row(const Row<T> &);
*	~Row();
*
* Methods:
*	operator [] (int);
*	operator [] (int) const;
*************************************************************************/
template <typename T>
class Row
{
public:
	Row();
	Row(const Array2D<T> &, int);
	Row(const Row<T> &);
	~Row();

	T & operator [] (int);
	const T & operator [] (int) const;

private:
	const Array2D<T> & m_array2D;
	int m_row;

};

/**********************************************************************
* Purpose: Constructs an instance of a Row object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Row<T>::Row()
{
	m_row = 0;
}

/**********************************************************************
* Purpose: Constructs an instance of a Row object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Row<T>::Row(const Array2D<T> & arr, int row) : m_array2D(arr)
{
	m_row = row;
}

/**********************************************************************
* Purpose: Constructs an instance of a Row object, using another
			instance as a means of doing so.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance created.
*
************************************************************************/
template <typename T>
Row<T>::Row(const Row<T> & copy)
{
	m_array2D = copy.m_array2D;
	m_row = copy.m_row;
}

/**********************************************************************
* Purpose: Destroys an instance of a Row object.
*
* Precondition:
*     None
*
* Postcondition:
*     Instance destroyed.
*
************************************************************************/
template <typename T>
Row<T>::~Row()
{
	m_row = 0;
}

/**********************************************************************
* Purpose: Returns data element at given index.
*
* Precondition:
*     None
*
* Postcondition:
*     Data element returned.
*
************************************************************************/
template <typename T>
T & Row<T>::operator [] (int column)
{
	return const_cast<T &>(m_array2D.Select(m_row, column));
}

/**********************************************************************
* Purpose: Returns const data element at given index.
*
* Precondition:
*     None
*
* Postcondition:
*     Const data element returned.
*
************************************************************************/
template <typename T>
const T & Row<T>::operator [] (int column) const
{
	return m_array2D.Select(m_row, column);
}

#endif