#include "base.h"

int main()
{
	char ch = '\0';

	do
	{
		InitVariables();
		GetInput(); // get input information
		CalcInfo(); // calculate the basic information
		CreateCache();   // initialize Cache
		FileTest();    // test the testfile
		PrintOutput(); // output the result
		std::cout << "Continue/Exit(C/E)" << std::endl;
		std::cin >> ch;
	} while ((ch != 'e') && (ch != 'E'));

	return 0;
}
