#include "Trie.h"

Trie::Trie()
{
	m_maxWordLength = 0;
	m_root = shared_ptr<TrieNode>(new TrieNode());
	m_countWord = 0;
	loadDictionary();
}

void Trie::interFace()
{
	string nameInputFile;
	string nameOutputFile;

	//cout << "=>Enter the name of the input file: ";
	//cin >> nameInputFile;
	//cout << "=>Enter the name of the output file: ";
	//cin >> nameOutputFile;
	//Mở file input để đọc dữ liệu:
	m_inputData = getInput("input.txt");

	//Xử lý dữ liệu:
	int n = m_inputData.length();
	bool* check = new bool[n];


	for (int k = 7; k <= n && k <= m_maxWordLength; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			check[i] = true;
		}
		int* arr = new int[k];
		
		string result = "";
		cout << k << endl;
		process(n, k, arr, 0, check, result);
		delete[] arr;
	}

	m_outputFile.open("output.txt");
	if (m_outputFile.is_open() == false)
	{
		cout << "Couldn't open file " << nameOutputFile << endl;
		exit(0);
	}
	m_outputFile << m_countWord << endl;
	for (int i = 0; i < m_inputData.size(); i++)
	{
		m_outputFile << m_outputData[i] << endl;
	}

	delete[] check;
}

void Trie::insertWord(string &key)
{
	shared_ptr<TrieNode> pCrawl = m_root;

	for (int i = 0; i < key.length(); ++i)
	{
		int index = int(key[i]) - int('a');
		if (pCrawl->children[index] == shared_ptr<TrieNode>(nullptr))
		{
			pCrawl->children[index] = shared_ptr<TrieNode>(new TrieNode());
		}

		pCrawl = pCrawl->children[index];
	}
	pCrawl->isEndOfWord = true;
}

bool Trie::searchWord(string &key)
{
	shared_ptr<TrieNode> pCrawl = m_root;
	
	for (int i = 0; i < key.length(); ++i)
	{
		int index =int(key[i]) - int('a');
		if (pCrawl->children[index] == shared_ptr<TrieNode>(nullptr))
			return false;		
		pCrawl = pCrawl->children[index];
	}

	if (pCrawl->isEndOfWord == true)
	{
		return true;
	}
	return false;
}

//arr là mảng chứa k phần tử
void Trie::process(int n, int k, int arr[], int i, bool check[], string &result)
{
	int j;
	for (j = 0; j < n; j++)
	{
		if (check[j] == true)
		{
			arr[i] = j + 1;
			result += m_inputData[arr[i] - 1];
			check[j] = false;

			if (i == (k - 1))
			{
				//check and print answer
				printOutput(arr, k, result);
				//cout << result << endl;
			}
			else
			{
				process(n, k, arr, i + 1, check, result);
			}
			//delete last char
			if (result.length() == 1)
			{
				result.clear();
			}
			else if (result.length() > 1)
			{
				result.erase(result.length() - 1);
			}
			check[j] = true;
		}
		
	}
}

//check if result is in hash or not, if not, add to hash and print output
void Trie::printOutput(int arr[], int k, string result)
{
	if (searchWord(result)==true && m_hashTable.search(result)==false)
	{
		m_hashTable.insert(result);
		m_outputData.push_back(result);
		cout << result;
		m_countWord++;
	}
}
//bool Trie::isEmpty(shared_ptr<TrieNode> root)
//{
//	for (int i = 0; i < ALPHABET_SIZE; ++i)
//	{
//		if (root->children[i]!=nullptr||root->isEndOfWord==true)
//		{
//			return false;
//		}
//	}
//	return true;
//}

//bool Trie::partRemove(string& key, shared_ptr<TrieNode>& checkout)
//{
//	if (checkout == nullptr)
//	{
//		return false;
//	}
//
//	if (key.length() == 0)
//	{
//		if (checkout->isEndOfWord == true)
//		{
//			checkout->isEndOfWord = false;
//			return true;
//		}
//		return false;
//	}
//
//	string part = key.substr(1);
//	int index =static_cast<int> (key[0] - 'a');
//	if (partRemove(part, checkout->children[index]))
//	{
//		if (isEmpty(checkout->children[index]))
//		{
//			checkout->children[index].reset();
//			checkout->children[index] = nullptr;
//			return true;
//		}
//		else
//		{
//			return true;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return false;
//}
//
//bool Trie::removeWord(string& key)
//{
//	if (partRemove(key, m_root))
//	{
//		return true;
//	}
//	return false;
//}

void Trie::loadDictionary()
{
	cout << "Loading dictionary..." << endl;
	ifstream input_file;
	input_file.open("Dic.txt", ifstream::in);
	if (input_file.is_open())
	{
		string temp;
		char checkEOF;
		while (true)
		{
			checkEOF = input_file.peek();
			getline(input_file, temp);
			if (temp.length() > m_maxWordLength)
			{
				m_maxWordLength = temp.length();
			}
			if (checkEOF==EOF)
			{
				break;
			}
			insertWord(temp);
		}
	}
	else
	{
		cout << "Coudn't open file Dic.txt!" << endl;
		exit(0);
	}

	input_file.close();
	cout << "=> Done." << endl;
}

string Trie::getInput(string nameFile)
{
	cout << "=> Reading file: "<<nameFile<<"..." << endl;
	string result;
	m_inputFile.open(nameFile, ifstream::in);
	if (m_inputFile.is_open() == false)
	{
		cout << "Couldn't open file " << nameFile << endl;
	}
	string temp;
	char checkEOF;
	while (true)
	{
		checkEOF = m_inputFile.peek();
		if (checkEOF == EOF)
		{
			break;
		}
		m_inputFile >> temp;
		if (temp != " " && temp!="\n")
		{
			result += temp;
			temp = "";
		}
	}
	m_inputFile.close();
	return result;
}


Trie::~Trie()
{
	m_outputFile.seekp(ofstream::beg);
	m_outputFile << to_string(m_countWord);
	m_outputFile.close();
	m_inputFile.close();
	cout << "=> Program is ended." << endl;
	//Need not delete anything.
}
