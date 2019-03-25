#include <iostream>
#include <fstream>
#include <string>
#include "GenStack.h"

using namespace std;

bool checkFile(string f) //true = readible
{
	string fn = f;
	ifstream inputfile;

	if (fn.substr(fn.find_last_of(".") + 1) == "cpp") //checking cpp extension
		cout << "File Inputted: " << fn << endl;
	else //not .cpp file
	{
		cout << "Inputted a non .cpp file." << endl;
		cout << "Please input a proper .cpp file (including extension) to analyze" << endl;
		return false;
		exit(1);
	}

	inputfile.open(fn);
	if (inputfile.fail()) //if .cpp is readible
	{
		cout << ".cpp filename entered but cannot be read." << endl;
		cout << "Please input a proper .cpp file (including extension) to analyze" << endl;
		return false;
		exit(1);
	}

	inputfile.close();
	return true;
}

int checkSyntax(string f)
{
	cout << "Checking syntax..." << endl;
	string fn = f;
	ifstream inputfile;

	GenStack<char> myStack;

	inputfile.open(fn);
	string currentline;
	int line = 1;
	while(getline(inputfile, currentline))
	{
		cout << "Line " << line++ << ": " << currentline << endl;
		for (int i = 0; i < currentline.length(); i++)
		{
			char curr = currentline[i];

			if (curr == '(' || curr == '{' || curr == '[') //Opening Brackets
			{
				myStack.push(curr);
				//cout << curr;
			}
			else if (curr == ')')
			{
				//cout << curr;
				if (myStack.isEmpty()) return i; //nothing to match with

				if (myStack.peek() != '(') return i; //wrong matching bracket
				myStack.pop();
			}
			else if (curr == '}')
			{
				//cout << curr;
				if (myStack.isEmpty()) return i; //nothing to match with

				if (myStack.peek() == '{') return i; //wrong matching bracket
				myStack.pop();
			}
			else if (curr == ']')
			{
				//cout << curr;
				if (myStack.isEmpty()) return i; //nothing to match with

				if (myStack.peek() != '[') return i; //wrong matching bracket
				myStack.pop();
			}


			/**
			else if (curr == ')' || curr == '}' || curr == ']') //Closing Brackets
			{
				cout << curr;
				if (myStack.isEmpty()) return i; //nothing to match with

				if (myStack.peek() == '(') myStack.pop();
				else if (myStack.peek() == '{') myStack.pop();
				else if (myStack.peek() == '[') myStack.pop();

				myStack.pop();
				else return i; //wrong matching bracket
			}
			**/
		}
		//cout << endl;
	}

	inputfile.close();
	if (myStack.isEmpty()) return -1; //every symbol matched
	//some brackets were never matched
	else if(myStack.peek() == '(') return -2;
	else if(myStack.peek() == '{') return -3;
	else if(myStack.peek() == '[') return -4;
}

void analyzeFile(string f)
{
	bool isValidFile = checkFile(f);
	int isCorrect = -1; //-1 = no problems
	if (isValidFile) //else is checked by checkFile()
	{
		isCorrect = checkSyntax(f);
		if (isCorrect == -1)
		{
			cout << "Delimeter Syntax is correct." << endl;
			cout << "Enter another valid .cpp file to process if you want to analyze another file" << endl;
			cout << "If not, type anything else" << endl;
			string input;
			cin >> input;
			analyzeFile(input);
		}
		else
		{
			if (isCorrect == -2)
				cout << "Reached end of file: missing (" << endl;
			else if (isCorrect == -3)
				cout << "Reached end of file: missing {" << endl;
			else if (isCorrect == -4)
				cout << "Reached end of file: missing [" << endl;
			else
				cout << "Error on line " << isCorrect << endl;
		}
	}
}

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		analyzeFile(argv[1]);
	}
	else //wrong number of args
	{
		cout << "Wrong number of args" << endl;
		cout << "Please input a proper .cpp file (including extension) to analyze" << endl;
		exit(1);
	}

	cout << "Program exited succesfully." << endl;
	return 0;
}
