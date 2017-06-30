/***************************************************************************************************************
Title: Union-Find/Assignment4

Author: Chris Hamburger

Created: 5/3/17

Description: Parsing through a data file to create a database of phone numbers and money transfers to build cohorts that are linked and connected. 

Purpose: To practice using union find data structure 

Compile: Navigate to the program directory and run the make command to create an executable file.

Executable name: assignment4

To run: copy command inside the brackets [./assignment4 name_of_text_file_argument.csv]

*****************************************************************************************************************/

#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using namespace std;

class Number{

public:
//constructor that takes in a string number and an int cohort id
	Number(string x, int y){		number=x; cohort_id=y;}
	~Number();

//getter function-returns the string member "number"
	string getNumber(){			return number;}

//allows a number's cohort_id to be changed if it is unioned with another cohort 
	void setCohortid(int x)	{		cohort_id=x;}

//getter to return the cohort id of the number object
	int getCohortId(){			return cohort_id;}

private:
	string number;
	int cohort_id;
};

#endif


