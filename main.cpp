#include <iostream>
#include "Assignment3.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Assignment3 checker;
		checker.analyzeFile(argv[1]);
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
