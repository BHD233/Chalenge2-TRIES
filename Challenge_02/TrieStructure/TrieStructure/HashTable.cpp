#include "HashTable.h"

int HashTable::s_prime = 65713;

int HashTable::s_alphabetSize = 26;

HashTable::HashTable()
{
	m_hashTableSize = 150000; // Gần bằng số lượng từ trong từ điển.
	m_hashTable = new string[m_hashTableSize];
}

int HashTable::hashFuntion(string value)
{
	int result = 0;
	for (int i = 0; i < value.length(); i++)
	{
		result += value[i] * powInt(s_alphabetSize, i);
	}
	result = result % s_prime;
	if (result < 0)
	{
		result += m_hashTableSize;
	}
	return result;
}

int HashTable::powInt(int x, int y)
{
	int result=1;
	for (int i = 1; i <= y; i++)
	{
		result *= x;
	}
	return result;
}

void HashTable::insert(string value)
{
	int index = 0;
	int i = 0;
	while (i < m_hashTableSize)
	{
		index = (hashFuntion(value) + i) % m_hashTableSize;
		if (index < 0)
		{
			index += m_hashTableSize;
		}
		if (m_hashTable[index] == "")
		{
			m_hashTable[index] = value;
			break;
		}
		i++;
	}
}

bool HashTable::search(string value)
{
	int index = 0;
	int i = 0;
	while (i < m_hashTableSize)
	{
		index = (hashFuntion(value) + i) % m_hashTableSize;
		if (index < 0)
		{
			index += m_hashTableSize;
		}
		if (m_hashTable[index] == value)
		{
			return true;
		}
		i++;
	}
	return false;
}



HashTable::~HashTable()
{
	delete[] m_hashTable;
}