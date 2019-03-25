#include <iostream>

using namespace std;

class Assignment3
{
	public:
		Assignment3(); //constructor
		~Assignment3(); //destructor

		void analyzeFile(string f);
	private:
		bool checkFile(string f);
		int checkSyntax(string f);
		char getOpposite(char c);

		char missingBracket;
};
