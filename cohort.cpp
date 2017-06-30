#include "cohort.h"

Cohort::Cohort (int x, string num1, string num2, double amount){
	cohortId=x; 
	cohortMembers.insert(num1); 
	cohortMembers.insert(num2); 
	volume=amount; 	//start with initial amount on construction
	weight =-1;	//all new cohorts start with weight -1
	cardinality=2;	//they all start with cardinbality of 2 since 2 members needed for new cohort
}

ostream& operator<<(ostream &out, Cohort &x){
	for(auto &y: x.cohortMembers){
		out<<y<<endl;
	}
	return out;
}

void Cohort::addMember(string newMember, double amt){
	cohortMembers.insert(newMember);
	addCardinality(1);//adds 1 to the cardinality when a new phone number is added
	addToVolume(amt);//adds to the volume of the cohort
}

//calculates activity which is volume/((N(N-1))/2)
double Cohort::getActivity(){

	int unorderedpairs=(getCardinality()*(getCardinality()-1))/2;
	double activity =getVolume()/unorderedpairs;

	return activity;
}
			
//operator overloads-these are both used in disjsets class for maxsize and maxactivity functions
//declared friends for access outside cohort class
bool operator<(Cohort& lhs, Cohort& rhs){
	return lhs.getCardinality()<rhs.getCardinality();
}

bool operator>(Cohort& lhs, Cohort& rhs){
	return rhs.getActivity()>lhs.getActivity();
}
