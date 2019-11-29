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
	int temp = 0;
	//Băm từng thành phần để chống tràn số (a+b)mod m= (a mod m + b mod m) mod m
	for (int i = 0; i < value.length(); i++)
	{
		temp = ((value[i] - 'a') * powInt(s_alphabetSize, i)) % s_prime;
		result += temp;
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
	int index = hashFuntion(value)%m_hashTableSize;
	while (m_hashTable[index] != "")
	{
		index = (index + 1) % m_hashTableSize;
	}
	m_hashTable[index] = value;
}

bool HashTable::search(string value)
{
	
	int index = hashFuntion(value)%m_hashTableSize;
	while (m_hashTable[index] != value && m_hashTable[index] != "")
	{
		index = (index + 1) % m_hashTableSize;
	}
	if (m_hashTable[index] != value)
	{
		return false;
	}
	return true;
}



HashTable::~HashTable()
{
	delete[] m_hashTable;
}