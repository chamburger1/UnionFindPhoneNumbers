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

#include <unordered_map>
#include <string>
#include <iostream>
#include "disjsets.h"
#include "cohort.h"
#include "number.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <iomanip>

using namespace std;

int main (int argc, char *argv[]){

cout<<fixed<<setprecision(2);

// Value-Defintions of the different String values that come as commands in data files
enum commandType {data, find, members, max_size, max_activity, cohort_ids, info};

// Map to associate the strings with the enum values to allow switch statements instead of if statements
unordered_map<string, commandType> mapOfCommands;

//assign values to strings in the map 
mapOfCommands["data"]=data;
mapOfCommands["find"]=find;
mapOfCommands["members"]=members;
mapOfCommands["max-size"]=max_size;
mapOfCommands["max-activity"]=max_activity;
mapOfCommands["cohort-ids"]=cohort_ids;
mapOfCommands["info"]=info;

ifstream inFile;
string line, filename;
unsigned int count=1;
unordered_map<string, Number*> allPhoneNumbers;
DisjSets disJntSets;


if(argc==1){
	cerr<<"No input file provided"<<endl;
}
else{
	filename=argv[1];
	inFile.open(filename);
}

if(!inFile){
	cerr<<"File unable to be opened"<<endl;
}
else{	//parse file getting line

	while(getline(inFile, line)){ //get the line
  	string lineCommand;
	istringstream   linestream(line);
	linestream>>lineCommand;

	double moneyTransferred;
	string phoneA, phoneB, amount, phoneToSearch, cohort_ID;
	int convertedID;

    	switch(mapOfCommands[lineCommand]){

      	case data:
		linestream>>phoneA>>phoneB>>amount;

		if(phoneA!=phoneB){//numbers !=
			try{
				moneyTransferred=stod(amount);
			}
			catch(invalid_argument&){
				cerr<<"error with conversion"<<endl;
			};
			
			if(moneyTransferred>0){//money is greater than 0
				if(allPhoneNumbers.count(phoneA)<1&&allPhoneNumbers.count(phoneB)<1) {//neither on table form new cohort
					Cohort *newCohort= new Cohort(count, phoneA, phoneB, moneyTransferred);
 					//starts at 1 and every time a new one created gets incremented to the next space in vector

					//2 new numbers are created and their strings are added to the global hash table for future lookup
					Number *A=new Number(phoneA, count);
					Number *B=new Number(phoneB, count);
					allPhoneNumbers.insert(make_pair(phoneA, A));
					allPhoneNumbers.insert(make_pair(phoneB, B));
					disJntSets.addCohort(newCohort, count);//add to disjntsets vector at index
					count++;//increase count to mark next vector space to uinsert a new cohort if one is created
				}
				else if(allPhoneNumbers.count(phoneA)>0&&allPhoneNumbers.count(phoneB)<1){  
					//only phoneB s not on hash table-get cohort id of Phone A and add Phone B to it, increase that  						cohort's volume by the new amount

			      		int cohortIndex=disJntSets.find(allPhoneNumbers[phoneA]->getCohortId());
					allPhoneNumbers[phoneA]->setCohortid(cohortIndex);
					Number *B=new Number(phoneB, cohortIndex);
					allPhoneNumbers.insert(make_pair(phoneB, B));
					disJntSets.at(cohortIndex)->addMember(phoneB,  moneyTransferred);
				}
				else if(allPhoneNumbers.count(phoneB)>0&&allPhoneNumbers.count(phoneA)<1){  
					//only phoneA s not on table-get cohort of phoneB and add Phone A to it and increase the volume 					with the new amount
					
					int cohortIndex=disJntSets.find(allPhoneNumbers[phoneB]->getCohortId());
					allPhoneNumbers[phoneB]->setCohortid(cohortIndex);
					Number *A=new Number(phoneA, cohortIndex);
					allPhoneNumbers.insert(make_pair(phoneA, A));
					disJntSets.at(cohortIndex)->addMember(phoneA,  moneyTransferred);
				}
				else{			
					//both numbers already on the list hash table-must find their cohort-ids and union them
					int cohortIndexB=allPhoneNumbers[phoneB]->getCohortId();
					int cohortIndexA=allPhoneNumbers[phoneA]->getCohortId();
					disJntSets.setunion(cohortIndexA, cohortIndexB, moneyTransferred);
				}			
			}
		}
       	 	break;

      	case find:

		linestream>>phoneToSearch;

		//checks that the number is on the table first 
		if(allPhoneNumbers.count(phoneToSearch)>0){
		 	cout<<phoneToSearch<<": ";
			//calls find on the numbers cohort as it might be merged and changes it to the newest cohort id
			allPhoneNumbers[phoneToSearch]->setCohortid(disJntSets.find(allPhoneNumbers[phoneToSearch]->getCohortId()));
			int id=allPhoneNumbers[phoneToSearch]->getCohortId();
			cout<<id<<endl;
		}
		else
			cout<<phoneToSearch<<": 0."<<endl;
       		break;

      	case members:
		linestream>>cohort_ID;
		try{
			convertedID=stoi(cohort_ID);
		}
		catch(invalid_argument&){
			cerr<<"error with conversion"<<endl;
		};
			if(disJntSets.getVectorSize()-1>convertedID){
			//if the cohort id to look for is within the vector range ie. a vector of size 200 will 
			//only have a valid vector index of 199, so looiking for vector 200 will fail
				if(disJntSets.at(convertedID)->getWeight()<0 || convertedID==0)
					disJntSets.printCohort(cout, convertedID);
				else
					cerr<<endl;
			}
			else
				cerr<<endl;
		break;

      	case max_size:
//checks that the returned cohort id is not 0 
       		disJntSets.maxSize(cout);
       		break;
//if the number returned by the maxActivity function is not 0 then print out the data
      	case max_activity:
        	disJntSets.maxActivity(cout);
        	break;

      	case cohort_ids:
			cout<<disJntSets<<endl;
        		break;

      	case info:
		linestream>>cohort_ID;
		try{
			convertedID=stoi(cohort_ID);
		}
		catch(invalid_argument&){
			cerr<<"error with conversion"<<endl;
		};
			//make sure the weight of the cohort is negative if its greater than 0 means its a child of a parent & not valid 
			if(disJntSets.at(convertedID)->getWeight()<0){
				cout<<convertedID;
				cout<<"	"<<disJntSets.at(convertedID)->getCardinality();
				cout<<"	"<<disJntSets.at(convertedID)->getActivity();
				cout<<"	"<<disJntSets.at(convertedID)->getVolume()<<endl;
			}
			else
				cerr<<"No cohorts matching ID."<<endl;
			break;

       	default:
        		cerr << "Problem with commands in file" << endl;
        		break;
    }
  }
}//else

  return 0;
}
