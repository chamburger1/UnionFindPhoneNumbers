//disjsets.h inplementation file

#include "disjsets.h"

DisjSets :: DisjSets (){
	Zero= new Cohort(0);
	addCohort(Zero, 0);//to block off the zero index in the vector 
}

void DisjSets :: setunion (int root1, int root2, double amt){ //indexes of cohorts in vector and an amount to add to volume
	if ( find(root1) != find(root2) ) {
		if ( setOfCohorts[ root2 ]->getWeight() < setOfCohorts[ root1 ]->getWeight() ){
			
			if(setOfCohorts[ root1 ]->getWeight()<0){ //if they are both parents 
				setOfCohorts[ root2 ]->addWeight(setOfCohorts[ root1 ]->getWeight()); //parent absborbs small parent weight
				setOfCohorts[ root2 ]->addToVolume(setOfCohorts[ root1 ]->getVolume()+amt);//add volume+ new amt
			}
			else{
				setOfCohorts[ root2 ]->addWeight(-1); //parent absborbs child's weight
				setOfCohorts[ root2 ]->addToVolume(amt);//add the new amount to the volume
			}

			setOfCohorts[ root2 ]->addCardinality(setOfCohorts[ root1 ]->getCardinality());//parent gets size of set
			setOfCohorts[ root1 ]->changeId(root2);//change cohort ID
			setOfCohorts[ root1 ]->ParentIdToChildWeight(root2);
		} 
		else {

			if(setOfCohorts[ root2 ]->getWeight()<0){
				setOfCohorts[ root1 ]->addWeight(setOfCohorts[ root2 ]->getWeight()); //parent absborbs weight
				setOfCohorts[ root1 ]->addToVolume(setOfCohorts[ root2]->getVolume()+amt);
			}
			else{
				setOfCohorts[ root1 ]->addWeight(-1); //parent absborbs weight
				setOfCohorts[ root1 ]->addToVolume(amt);
			}

			setOfCohorts[ root1 ]->addCardinality(setOfCohorts[ root2 ]->getCardinality());
			setOfCohorts[ root2 ]->changeId(root1);
			setOfCohorts[ root2 ]->ParentIdToChildWeight(root1);
		}
	}
	else{
//they are both members of the same set then find the parent id and add to parent's volume. 
		int parentOfCohort=find(setOfCohorts[root1]->getCohortId());
		setOfCohorts[parentOfCohort]->addToVolume(amt);
	}
		//then they're the in the same cohort so add volume of parent node
}

//uses changeID function of the cohort class to return the changed ID which allows recursion
int DisjSets :: find (int x){
	if ( setOfCohorts[x]->getWeight()<0)
		return x;
	else{
		return setOfCohorts[x]->changeId(find ( setOfCohorts[ x ]->getCohortId() ));
	}
}

//adds a cohort to the vector-if the vector is too small it increases the size of the vector
void DisjSets::addCohort(Cohort *newCohort, unsigned int count){
	if(setOfCohorts.empty())
		setOfCohorts.push_back(newCohort);
	else if(setOfCohorts.size()-1<count){
		setOfCohorts.resize(count+1);
		setOfCohorts.at(count)=newCohort;
	}
	else
		setOfCohorts.at(count)=newCohort;
}

//operator overloaded to pass oustream to main function 
//checks that disjsets vector is not empty meaning if only 0 index is stored
ostream& operator<<(ostream &out, DisjSets &x){
	if(x.setOfCohorts.size()==1)
		out<<"No cohorts to display"<<endl;
	else{
		for(auto &y: x.setOfCohorts){
			if(y->getWeight()<0){//parent of solo node
				out<<"Cohort ID "<<y->getCohortId()<<endl;
			}
		}
	}
	return out;
}

ostream& DisjSets::printCohort(ostream &out, int x){
//if 0 it prints out all valid cohorts-recurses 
	if(x==0){
		for(unsigned int i=1; i<setOfCohorts.size(); i++){
			printCohort(out, i);
		}
	}
//if the weight of the cohort if negative then its a parent and its abs vaalue of its weight is how mant children it has
//prints all cohorts that match parent's id	
	if(setOfCohorts[x]->getWeight()<0){//its a child go through vector and find all matching children then print parent
		int numNodes=abs(setOfCohorts[x]->getWeight());
		out<<"Cohort Id "<<x<<endl;
		for(unsigned int i=0; i<setOfCohorts.size(); i++){
			if(x==setOfCohorts[i]->getWeight()){
				out<<(*setOfCohorts[i]);
				numNodes--;
			}
			else if(x==setOfCohorts[i]->getCohortId()){
				out<<(*setOfCohorts[i]);
				numNodes--;
			}
			//if numnodes is 0 then all nodes are printed and loop can stop
			if(numNodes==0)
				break;//all nodes in set printed
		}
	}
	return out;

}

//max activity funtion to print out the cohort with the highest activity
//priority queue maintained only in function scope rather than class member-if no cohorts returns 0
ostream& DisjSets::maxActivity(ostream &out)const {
	int maxcohortId;
	double maxAct;
	priority_queue<Cohort*, vector<Cohort*>, Cohort::ActivityComparator> MaxActivity;
	if(setOfCohorts.size()>1){
		for(unsigned int i=1; i<setOfCohorts.size(); i++){
			if(setOfCohorts.at(i)->getWeight()<0)
				MaxActivity.push(setOfCohorts.at(i));
		}
	
		maxAct=MaxActivity.top()->getActivity();
		while(!!MaxActivity.empty()&&maxAct==MaxActivity.top()->getActivity()){
			maxcohortId=MaxActivity.top()->getCohortId();
			out<<maxcohortId<<"	"<<MaxActivity.top()->getActivity()<<"	";
			out<<MaxActivity.top()->getCardinality()<<"	"<<MaxActivity.top()->getVolume()<<endl;
			MaxActivity.pop();
		}
	}
	else
		out<<"No cohorts."<<endl;

	return out;
}

//max size fundtion to print out cohort id of cohort with highest cardinality(most members)
//priority quuee only lives in function scope-if no cohorts available return 0 
ostream& DisjSets::maxSize(ostream &out)const{
	int maxcohortId;
	int maxSize;
	priority_queue<Cohort*, vector<Cohort*>, Cohort::SizeComparator> MaxSize;
	if(setOfCohorts.size()>1){
		for(unsigned int i=1; i<setOfCohorts.size(); i++){
			if(setOfCohorts.at(i)->getWeight()<0)
				MaxSize.push(setOfCohorts.at(i));
		}
		
		maxSize=MaxSize.top()->getCardinality();
		while(!MaxSize.empty()&&MaxSize.top()->getCardinality()==maxSize){
			
			maxcohortId=MaxSize.top()->getCohortId();
			out<<maxcohortId<<"	"<<MaxSize.top()->getActivity()<<"	";
			out<<MaxSize.top()->getCardinality()<<"	"<<MaxSize.top()->getVolume()<<endl;
			MaxSize.pop();
		}
	}
	else
		out<<"No cohorts."<<endl;

	return out;
}
