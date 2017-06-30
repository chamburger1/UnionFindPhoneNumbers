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

#ifndef COHORT_H
#define COHORT_H

#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Cohort{

public:
//constructor that thats a int as the id, 2 strings as numbers and an amount added to the cohort's volume	
	Cohort (int x, string num1, string num2, double amount);

//Zero cohort to reserve the 0 index in a vector
	Cohort(int zero){weight =zero;}
	~Cohort();

//adds a string and and ammount to the cohort-used when a cohort adds a new number to its cohort
	void addMember(string newMember, double amt);

//getter to return the cohort id
	int getCohortId(){			return cohortId;}

//getter to get the cohort's size
	int getSize(){				return cohortMembers.size();}

//this adds an amount to the cohort's volume
	void addToVolume(double x){		volume+=x;}

//getter to return the cohort's volume
	double getVolume(){			return volume;}

//simultaneous getter/setter to work with the disjsets find function to allow recursion
	int changeId(int x){			cohortId=x; return cohortId;}

//getter to return the weight of the cohort
	int getWeight(){			return weight;}

//getter to return cardinality-similar to size but this is used when a cohort merges with another
	int getCardinality(){			return cardinality;}

//adds weight to cohort
	void addWeight(int x){			weight+=x;}

//this sets the weight of an absorbved child with the id of its parent
	void ParentIdToChildWeight(int x){	weight=x;}

//fundtion to increase cardinality used if a union occurs
	void addCardinality(int x){		cardinality+=x;}

//getter to calculate and return cohort's activity
	double getActivity();	

//operator overloads-pases outstream to main for console output
//overloading greater and less than operators
	friend ostream& operator<<(ostream &out, Cohort &x);
	friend bool operator<(Cohort& lhs, Cohort& rhs);
	friend bool operator>(Cohort& lhs, Cohort& rhs);

//comparators to allow insertion into priority queue see: disjsets.h
    	struct SizeComparator{
    		public:
      			bool operator()(Cohort * left, Cohort * right){
			       return (*left) < (*right);
      			}
    	};
    	struct ActivityComparator{
    		public:
      			bool operator()(Cohort * left, Cohort * right){
			       return (*left) > (*right);
      		}
    	};
	

private:
	unordered_set<string> cohortMembers; //phone numbers stroed as strings for fast look up
	int cohortId, weight, cardinality;
	double volume;

};

#endif
