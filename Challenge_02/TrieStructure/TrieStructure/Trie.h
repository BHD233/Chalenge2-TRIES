#ifndef _TRIE_H_
#define _TRIE_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "HashTable.h"

using namespace std;

#define ALPHABET_SIZE 26

class TrieNode
{
public:
	shared_ptr<TrieNode> children[ALPHABET_SIZE];
	
	bool isEndOfWord;

	TrieNode()
	{
		for (int i = 0; i < ALPHABET_SIZE; ++i)
		{
			children[i] = shared_ptr<TrieNode>();
		}
		isEndOfWord = false;
	}
};


class Trie
{
private:
	int m_maxWordLength;
	shared_ptr<TrieNode> m_root;// Node gốc của cây Trie
	int m_countWord;
	ifstream m_inputFile;
	ofstream m_outputFile;

	vector<string> m_outputData;

	string m_inputData; //Lấy dữ liệu từ file input

	HashTable m_hashTable; // Tạo mảng băm để lưu các từ.

public:
	//Nhận input tạo thành một chuỗi kiểu string
	string getInput(string);
	//In output ra file có tên là file output.txt
	void printOutput(int arr[], int k, string result);
	void process(int n, int k, int arr[], int i,bool check[], string& result);

public:
	Trie();
	void interFace();
	void loadDictionary();
	void insertWord(string&);
	bool searchWord(string&);

	//bool partRemove(string&, shared_ptr<TrieNode>&);
	//bool isEmpty(shared_ptr<TrieNode>);
	//bool removeWord(string&);

	
	~Trie();
};


#endif // !_TRIE_H_

