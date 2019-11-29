#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable
{
private:
	static int s_prime;
	static int s_alphabetSize;
	int m_hashTableSize; //Kích thước tối đa của bảng băm, lấy luôn kích thước tối đa của từ điển
	string* m_hashTable; // Bảng băm để lưu giá trị của từ.

public:
	int Size() { return m_hashTableSize; }
	int powInt(int, int);
	int hashFuntion(string);
	void insert(string);
	bool search(string);
public:
	HashTable();
	~HashTable();
};

#endif // !_HASH_TABLE_H
