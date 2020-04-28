#ifndef NODE	
#define NODE
#include <iostream>
using namespace std;

template<class T>
class myHash {
private:
	const static long long int HASHSIZE = 1381693; //change this value
	T* hash;
	int size;
public:
	~myHash() 
	{
		delete[] hash;
	}

	myHash()
	{
		hash = new T[HASHSIZE];
		size = 0;
		for (int i = 0; i < HASHSIZE; i++)
		{
			hash[i] = "";
		}
	}

	void insert(T item)
	{
		int key = findHash(item);
		if (key > HASHSIZE && key < 0)
		{
			return;
		}
		else if (hash[key] == "")
		{
			hash[key] = item;
			size++;
		}
		else
		{
			bool entered = false;
			while (!entered)
			{
				
				key++;
				if (hash[key] == "")
				{
					hash[key] = item;
					entered = true;
					size++;
				}
			}
		}
	}

	bool find(T item, long long int& compare)
	{
		int key = findHash(item);
		if (key > HASHSIZE && key < 0)
		{
			return false;
		}
		else if (hash[key].compare(item) == 0)
		{
			compare++;
			return true;
		}
		else if (hash[key].compare("") == 0)
		{
			compare++;
			return false;
		}
		else
		{
			bool found = false;
			while (!found)
			{
				key++;
				compare++;
				if (key > HASHSIZE)
				{
					return false;
				}
				else if (hash[key].compare(item) == 0)
				{
					compare++;
					return true;
				}
				else if (hash[key].compare("") == 0)
				{
					compare++;
					return false;
				}
			}
		}
	}

	int findHash(string word)
	{
		int i;
		long long int val = 0;
		for (i = 0; i <= word.size(); i++)
		{
			val += (int)word[i] * (i * i);
		}
		if (val > HASHSIZE)
		{
			return -1;
		}
		else
		{
			return val % HASHSIZE;
		}
	}

	int getSize()
	{
		return size;
	}

};
#endif
