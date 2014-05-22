#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* Created by Gavin Whitehall (GW) - 22/05/2014 */
/// Current Functionality :: Reads the file line by line and outputs it.

int main ()
{
	string text;							//Temp string for testing file read - GW

	string filedir = "";					//Use this for an external directory location	- GW
	string filename = "reimadmt.dat";		//Name of the input file	- GW

	ifstream file (filedir+filename);		//Open the file with the above variables - GW

	/* Check the file is open*/
	if (file.is_open())
	{
		cout << "File Contents:" << '\n';

		/* Iterate while there is a line to read - GW */
		while (getline(file, text))
		{
			cout << text << '\n';	//Output the line - GW
		}

		file.close();	//When it's finished close the file - GW
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Unable to open file";
	}
	
	getchar();		//Slight hack to keep output open upon run - GW
	return 0;
	
}