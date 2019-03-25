#include <iostream>
#include <fstream>
#include <string>
#include "GenStack.h"
#include "Assignment3.h"

using namespace std;

char missingBracket;

//PRIVATE
bool Assignment3::checkFile(string f) //true = readible
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

int Assignment3::checkSyntax(string f)
{
	cout << "Checking syntax..." << endl;
	string fn = f;
	ifstream inputfile;

	GenStack<char> myStack;

	inputfile.open(fn);
	string currentline;
	int line = 0;
	int openBracketLine = 0;

	while(getline(inputfile, currentline))
	{
		cout << "Line " << ++line << ": " << currentline << "#" << endl;

		bool singlecomment = false; //sees if bracket is in a comment
		bool strline = false;

		for (int i = 0; i < currentline.length(); i++)
		{
			char curr = currentline[i];

			if(curr == '/') singlecomment = true;
			if(curr == '"' && strline == false) strline = true; //open string
			else if (curr == '"' && strline == true) strline = false; //close string

			if (!singlecomment && !strline) //if singlecomment is true, rest of line is part of a comment
			{
				if (curr == '(' || curr == '{' || curr == '[') //Opening Brackets
				{
					myStack.push(curr);
					missingBracket = curr;
					openBracketLine = line; //setting line of open bracket
					cout << curr << endl;
				}
				else if (curr == ')')
				{
					cout << curr << endl;
					missingBracket = curr;
					if (myStack.isEmpty()) return -openBracketLine-4; //nothing to match with

					if (myStack.peek() != '(') return line; //wrong matching bracket
					myStack.pop();
				}
				else if (curr == '}')
				{
					cout << curr << endl;
					missingBracket = curr;
					if (myStack.isEmpty()) return -openBracketLine-4; //nothing to match with

					if (myStack.peek() != '{') return line; //wrong matching bracket
					myStack.pop();
				}
				else if (curr == ']')
				{
					cout << curr << endl;
					missingBracket = curr;
					if (myStack.isEmpty()) return -openBracketLine-4; //nothing to match with

					if (myStack.peek() != '[') return line; //wrong matching bracket
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

		}
		cout << "#######" << endl;
	}

	inputfile.close();
	if (myStack.isEmpty()) return -1; //every symbol matched
	//some brackets were never matched
	else if(myStack.peek() == '(') return -2;
	else if(myStack.peek() == '{') return -3;
	else if(myStack.peek() == '[') return -4;
}

char Assignment3::getOpposite(char c)
{
	switch(c)
	{
		case '(':
			return ')';
			break;
		case '{':
			return '}';
			break;
		case '[':
			return ']';
			break;
		case ')':
			return '(';
			break;
		case '}':
			return '{';
			break;
		case ']':
			return '[';
			break;
	}
}

//PUBLIC
void Assignment3::analyzeFile(string f)
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
				cout << "Reached end of file: missing )" << endl;
			else if (isCorrect == -3)
				cout << "Reached end of file: missing }" << endl;
			else if (isCorrect == -4)
				cout << "Reached end of file: missing ]" << endl;
			else if (isCorrect < -4)
				cout << "Error on line " << abs(isCorrect+5) << ": expected " << getOpposite(missingBracket) << " bracket" << endl;
			else
				cout << "Error on line " << isCorrect << endl;
		}
	}
}

//CONSTRUCTORS
Assignment3::Assignment3() {}

Assignment3::~Assignment3() {}
