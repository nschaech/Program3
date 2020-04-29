#include "timer.h"
#include "NODE.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

void cleanWord(string& word);

int main()
{
	//variable and string declarations
	ifstream opentext;
	ofstream mispelled;
	ofstream returntext;
	string book, dict;
	myHash<string> dictlist, mispell; //hash objects for dictionary and mispelled words
	Timer timer;
	long long int compare = 0;
	int indictcomp = 0;
	long long int notdictcomp = 0;
	int nondict = 0;
	int indict = 0;
	int notcheck = 0;

	//open files to be written to
	mispelled.open("misspelled.txt");
	opentext.open("dict.txt");
	//create a filled binary search tree for dictionary
	if (opentext.is_open())
	{
		opentext >> dict;
		while (!opentext.eof()) {
			//call cleanword to have all lower case 
			cleanWord(dict);
			dictlist.insert(dict);
			opentext >> dict;
		}
	}
	opentext.close();

	cout << "dictionary size: " << dictlist.getSize() << endl;
	//compare each word in book with dictionary list and start timer
	timer.Start();
	opentext.open("book.txt");
	if (opentext.is_open())
	{
		opentext >> book;
		while (!opentext.eof()) {
			//cleanword called so that non alphanumeric numbers are not checked
			cleanWord(book);

			if (book.length() > 0)
			{
				if (isalpha(book[0]))
				{
					//look for word in dictionary and iterate not in dictionary and in dictionary compares
					if (dictlist.find(book, compare))
					{
						indict++;
						indictcomp = indictcomp + compare;
						compare = 0;
					}
					else {
						nondict++;
						notdictcomp = notdictcomp + compare;
						mispell.insert(book); //insert mispelled words in hash
						compare = 0;
					}
				}
				else
				{
					notcheck++;
				}
			}
			opentext >> book;
		}
	}
	opentext.close();
	timer.Stop();

	
	int mispellSize = mispell.getSize(); //figure out how big the mispelled hash is
	if (mispelled.is_open())
	{
		//print each element of the mispelled words tree on a text document
		for (int i = 0; i < mispellSize; i++)
		{
			mispelled << mispell.elements() + '\n';
		}
	}
	mispelled.close();

	//find average compares per word
	int averagein = indictcomp / indict;
	int averagenot = notdictcomp / nondict;

	cout << "Done checking and these are the results." << endl;
	cout << "Finished in time: " << timer.Time() << endl;
	cout << "Finished in Milliseconds time: " << timer.TimeMS() << endl;
	cout << "There are " << indict << " words found in the dictionary." << endl;
	cout << indictcomp << " compares. Average: " << averagein << endl;
	cout << "There are " << nondict << " words NOT found in the dictionary." << endl;
	cout << notdictcomp << " compares. Average: " << averagenot << endl;
	cout << "There are " << notcheck << " words not checked." << endl;

	return 0;
}

//cleanword method that takes in a word and removes unwanted elements
void cleanWord(string& word)
{
	char let;
	int i = 0;
	int len = 0;
	len = word.length();
	//checks each letter in a given word
	for (int i = 0; i < len; i++)
	{
		let = word.at(i);

		if (let == '\'') {
		}
		else if (isalnum(let)) {
			if (isalpha(let))
			{
				word.at(i) = tolower(word.at(i));
			}
			else {}
		}
		else {
			//erase elements at a given point in the word if the elements are not an apostrophe or alphanumeric
			word.erase(word.begin() + i);
			len--;
			i = -1;
		}
	}
}