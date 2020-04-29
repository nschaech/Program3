#ifndef NODE	
#define NODE
#include <iostream>
using namespace std;

//Hash data structure template class
template<class T>
class myHash {
private:
	//declare variables
	const static long long int HASHSIZE = 1381693; //choose a prime hash size value that is ~10 times the size of the list intended to be stored
	T* hash;
	int size;
public:
	//destructor deallocates the hash since hash values are stored like an array one can use delete[] 
	~myHash() 
	{
		delete[] hash;
	}

	//constructor creates a string type hash of hashsize declared above
	myHash()
	{
		hash = new T[HASHSIZE];
		size = 0;
		for (int i = 0; i < HASHSIZE; i++)
		{
			hash[i] = "";//fills each index with ""
		}
	}

	//insert function to find a space for a given element
	void insert(T item)
	{
		//call find hash function to determine the key of the item being inserted
		int key = findHash(item);  
		//if element value outside size of HASH or negative return 
		if (key > HASHSIZE && key < 0)
		{
			return; 
		}
		//if there is no element at a given key insert the element and increase size of the filled list
		else if (hash[key] == "")
		{
			hash[key] = item;
			size++;
		}
		//case where there happens to be an element at a given hash key
		else
		{
			bool entered = false;
			while (!entered)
			{
				//increase key by 1111 to give best results for time
				key = key + 1111;
				//if a key is found that is empty insert new element in that location and increase size of filled list
				if (hash[key] == "")
				{
					hash[key] = item;
					entered = true;
					size++;
				}
			}
		}
	}

	//find function to cross check a list with a stored hash
	bool find(T item, long long int& compare)
	{
		//determine key size of the element being checked
		int key = findHash(item); 
		//if the key being checked is out of bounds return a false
		if (key > HASHSIZE && key < 0)
		{
			compare++;
			return false;
		}
		//if the element at a given key is the same as the element being check return true
		else if (hash[key].compare(item) == 0)
		{
			compare++;
			return true;
		}
		//if the element being check is "" return false
		else if (hash[key].compare("") == 0)
		{
			compare++;
			return false;
		}
		//case where the element at a key is not the same as the element being checked
		else
		{
			bool found = false;
			while (!found)
			{
				//increment key by 1111 for more effective find time
				key = key + 1111;
				compare++;
				//if key value is greater than HASHSIZE the element is not in the list
				if (key > HASHSIZE)
				{
					compare++;
					return false;
				}
				//if element found at a given key return true
				else if (hash[key].compare(item) == 0)
				{
					compare++;
					return true;
				}
			}
		}
	}

	//findHash to determine the size of a string in terms of ascii character values to be used for hash key
	int findHash(string word)
	{
		int i;
		long long int val = 0;
		for (i = 0; i <= word.size(); i++)
		{
			//convert character of word to its ascii value
			val += (int)word[i] * (i * i);
		}
		return val % HASHSIZE;
	}

	//elements will traverse the hash to return the elements stored
	T elements()
	{
		int key = 0;
		T word = "";
		//if the element at a given key is empty ("") then keep searching exit if search reaches end of list
		while (hash[key].compare("") == 0 && key < HASHSIZE)
		{
			key++;
		}
		//use temp element word to store element of hash key
		word = hash[key];
		//set hash key to "" so this key will be skipped the next time this function is called
		hash[key] = "";
		//return the temp element word
		return word;
		

	}

	int getSize()
	{
		return size;
	}

};
#endif