/* WordList source file
*
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias m_list in any way that would result
*	in undefined behavior.
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



// Do not include any other libraries

// #include"debugmem.h" 

#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;



/* Function: Wordlist Constructor
*
*	Constructs an empty Wordlist that is allocated enough space to store
*	max_words many words.  If max_words is less than 1, set m_list to nullptr
*	and the other member variables should be made consistent with this state.
*/
WordList::WordList(const int max_words)
{
	m_max = max_words;
	m_count = 0;

	if (m_max < 1)
		m_list = nullptr;
	else
		m_list = new char* [m_max];

	for (int i = 0; i < m_max; i++)
	{
		m_list[i] = new char[MAX_WORD_SIZE];
	}

}


/* Function: Wordlist Copy Constructor
*
*	Constructs a Wordlist that is a copy of an existing WordList
*/
WordList::WordList(const WordList& other)
{
	m_max = other.m_max;
	m_count = other.m_count;
	if (m_max < 1)
	{
		m_list = nullptr;
	}
	else
	{
		m_list = new char* [m_max];

		for (int i = 0; i < m_max; i++)
		{
			m_list[i] = new char[MAX_WORD_SIZE];
			if (i < m_count)
				strcpy(m_list[i], other.m_list[i]);
		}
	}


}


/* Function: Wordlist Destructor
*
*	Cleans up WordList's dynamically allocated memory.
*/
WordList::~WordList() {

	for (int i = 0; i < m_max; i++)
	{
		delete[] m_list[i];
	}
	delete[] m_list;
}

/* Function: printList
*
*	Prints all the words in WordList in a single line with spaces between each
*	word, then followed by a newline after the last word. Returns the number
*	of words printed.  If m_list is nullptr there is nothing to print, return -1.
*/
int	WordList::print() const {

	if (m_list == nullptr)
	{
		return -1;
	}


	for (int i = 0; i < m_count; i++)
	{
		cout << m_list[i] << " ";
	}
	cout << endl;
	return m_count;

}



/* Function: at
*
*	Returns the word at the index position in the WordList.
*	return nullptr if the index is out of bounds.
*/
char* WordList::at(const int index) const {

	if (index >= m_count || index < 0)
		return nullptr;
	else
		return m_list[index];

}


/* Function: count
*
*	Returns the number of words currently stored in WordList.
*/
int	WordList::count() const {

	return m_count;

}


/* Function: add
*
*	Adds the word into WordList (words have no spaces).  If WordList does not have
*	enough space to add word, addWord will resize with just enough space to allow for
*	the addition of word. If addWord needed to resize then return 1, otherwise if there
*	already enough space to add word without resizing, return 0. If word is empty
*	do nothing return -1. If m_list was nullptr, everything above still holds true except
*	return -2.
*/
int	WordList::add(const char word[]) {

	if (strlen(word) == 0)
	{
		return -1;
	}

	else if (m_list == nullptr)
	{
		m_list = new char* [1];
		m_list[0] = new char[MAX_WORD_SIZE];
		m_count = m_max = 1;
		strcpy(m_list[0], word);
		return -2;
	}

	else if (m_count == m_max)
	{
		int tm_max = ++m_max;

		char** temp = new char* [tm_max];
		for (int i = 0; i < tm_max; i++)
		{
			temp[i] = new char[MAX_WORD_SIZE];
			if (i < m_count)
			{
				strcpy(temp[i], m_list[i]);
				delete[] m_list[i];
			}

		}
		delete[] m_list;

		strcpy(temp[m_count], word);

		m_max = tm_max;

		m_list = new char* [m_max];
		for (int i = 0; i < m_max; i++)
		{
			m_list[i] = new char[MAX_WORD_SIZE];
			strcpy(m_list[i], temp[i]);
			delete[] temp[i];
		}
		delete[] temp;

		m_count = m_max;
		return 1;
	}
	else if (m_count < m_max)
	{
		strcpy(m_list[m_count], word);
		++m_count;

		return 0;
	}

}


/* Funtion: remove
*
*	If m_list is nullptr, returns -1.  Otherwise, searches for every
*	occurrence of word[], and removes that word of the list, returns
*	the number of words removed.
*/
int	WordList::remove(const char word[]) {
	int removed = 0;

	if (m_list == nullptr)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < m_count; i++)
		{
			if (strcmp(m_list[i], word) == 0)
			{
				for (int j = i; j < m_count - 1; ++j)
				{
					strcpy(m_list[j], m_list[j + 1]);
				}
				delete[] m_list[m_count - 1];
				m_list[m_count - 1] = new char[MAX_WORD_SIZE];

				++removed;
				--m_count;

			}

		}

		return removed;
	}
}


/* Funtion: append
*
*
*	Appends the contents of other to the WordList.  If WordList does
*	not have enough space appendList should dynamically allocate enough space
*	to append the contents of other to WordList, returns number of words
*	appended.  If other is nullptr or empty appendList does nothing and
*	returns -1. If this WordList::m_list is nullptr everything above still
*	holds but returns -2.
*
*	Note the pointer parameter type as opposed to reference type.
*/
int	WordList::append(const WordList* other) {

	if (other == nullptr || other->m_list == nullptr)
	{
		return -1;
	}

	else if (m_list == nullptr)
	{
		m_count = m_max = other->m_count;

		m_list = new char* [m_max];

		for (int i = 0; i < m_max; i++)
		{
			m_list[i] = new char[MAX_WORD_SIZE];
			strcpy(m_list[i], other->m_list[i]);
		}

		return -2;
	}

	else if (m_max >= (m_count + other->m_count))
	{
		for (int i = 0; i < other->m_count; i++)
		{
			strcpy(m_list[m_count + i], other->m_list[i]);
		}
		m_count += other->m_count;

		return 0;
	}

	else if (m_max < (m_count + other->m_count))
	{
		int tm_max = m_count + other->m_count;

		char** temp = new char* [tm_max];
		for (int i = 0; i < tm_max; i++)
		{
			temp[i] = new char[MAX_WORD_SIZE];
			if (i < m_count)
				strcpy(temp[i], m_list[i]);
			else
				strcpy(temp[i], other->m_list[i - m_count]);

			if (i < m_max)
				delete[] m_list[i];
		}
		delete[] m_list;

		m_max = tm_max;

		char** m_list = new char* [m_max];
		for (int i = 0; i < m_max; i++)
		{
			m_list[i] = new char[MAX_WORD_SIZE];
			strcpy(m_list[i], temp[i]);
			delete[] temp[i];
		}
		delete[] temp;

		m_count = m_max;

		return other->m_count;
	}

}


/* Funtion: find
*
*	Finds the first occurrence of the word in the WordList
*	returns the position of that word in the list.  Otherwise,
*	if the word is not in the WordList or if m_list is nullptr
*	return -1.
*/
int WordList::find(const char word[]) const {

	if (m_list == nullptr)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < m_count; i++)
		{
			if (strcmp(m_list[i], word))
			{
				return i;
			}

		}
	}
	return -1;

}


/* Funtion: sort
*
*	If m_list is nullptr return -1.  If there is only one word
*	in the list return 1.  Otherwise, sortList sorts the
*	words in WordList in ascending order.  Returns 0 on
*	success.
*/
int	WordList::sort() {

	if (m_list == nullptr)
	{
		return -1;
	}
	else if (m_count == 1)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_count - 1; ++i)
		{
			for (int j = i + 1; j < m_count; ++j)
			{
				if (strcmp(m_list[i], m_list[j]) > 0)
				{
					char temp[MAX_WORD_SIZE];

					strcpy(temp, m_list[i]);
					strcpy(m_list[i], m_list[j]);
					strcpy(m_list[j], temp);
				}
			}
		}
		return 0;
	}

}


/* Funtion: Assignment Operator
*
*	Overload the assignment operator for WordList.  Makes a deep
*	copy from other to this WordList.
*/
WordList& WordList::operator=(const WordList& other) {

	if (this == &other)
		return *this;

	for (int i = 0; i < m_max; i++)
	{
		delete[] m_list[i];
	}
	delete[] m_list;

	m_max = other.m_max;
	m_count = other.m_count;

	m_list = new char* [m_max];
	for (int i = 0; i < m_max; i++)
	{
		m_list[i] = new char[MAX_WORD_SIZE];
		if (i < m_count)
			strcpy(m_list[i], other.m_list[i]);
	}

	return *this;
}