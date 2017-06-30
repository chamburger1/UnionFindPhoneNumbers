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

#ifndef DISJSETS_H
#define DISJSETS_H

#include "cohort.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>

class DisjSets{
public :
	DisjSets ();

//union function that takes two int indices and an amt and unions them to merge sets 
//this increases the weight of absorbing cohort, sets the weight of absorbed cohort to parent id, adds cardinality and volume of child to parent
	void setunion (int x , int y, double amt);

//the complementary find function to the union-find data structure-takes in an int index and recurses until it find its parent-utilizes path compression to make subsequent function calls fasters
	int find (int x);

//adds a new cohort at a specified index count to act as its ID for easy look up, if the vector is too small it resizes
	void addCohort(Cohort *newCohort, unsigned int count);

//function to return a refernce to a pointer to a cohort object stored at a specific index
	Cohort* at(int x){				return setOfCohorts.at(x);}
//second ostream function to print the set members of a given cohort
	ostream& printCohort(ostream &out, int x);

//wanted to return the vector size 
	int getVectorSize(){				return setOfCohorts.size();}

//these return the cohort with the max size and the max activity-they use priority queues and comparators and op overloads defined in the cohort class
//they each create priority queues when called rather than having them as class members
	ostream& maxActivity(ostream &out)const;
	ostream& maxSize(ostream &out)const;

//operator overload to pass informatiopn to the main function-this prints out the cohorts ids contained in the member vector
	friend ostream& operator<<(ostream &out, DisjSets &x);
private :
	vector <Cohort*> setOfCohorts;
	Cohort* Zero;
};


#endif
