#include <iostream>
#include <string>
#include <vector>


class mySolution{
	public:
		std::string word;
		int correct;
};

void removeNonAnswers(std::vector<std::string>& words,mySolution solution){
	for(unsigned int i=0;i<words.size();i++){
		std::string tword=words[i];
		int posscorrect=0;
		for(unsigned int j=0;j<tword.size();j++){
			if(tword[j]==solution.word[j]){
				posscorrect++;
			}
		}
		if(posscorrect!=solution.correct){
			words.erase(words.begin()+i);
			i--;
		}
	}
}

void getWords(std::vector<std::string>& words){
	std::string tword = "";
	while (true) {
		std::cout<<"Input possible word: ";
		std::cin>>tword;
		if(tword[0]!='.'){
			words.push_back(tword);
		} else {
			break;
		}
	}
}

mySolution inputSolution(){
	mySolution retSol;
	std::cout<<"Input Solution Word: ";
	std::cin>>retSol.word;
	std::cout<<"Input Correct Letters: ";
	std::cin>>retSol.correct;
	return retSol;
}

void printPossibleSolutions(std::vector<std::string> words){

}


int main(){
	std::vector<mySolution> solutions;
	std::vector<std::string> words;
	std::vector<std::string> solVector;
	getWords(words);
	solVector=words;
	while(true){
		removeNonAnswers(solVector,inputSolution());
		std::cout<<"Possible Answers:";
		for(unsigned int i=0;i<solVector.size();i++){
			std::cout<<solVector[i]<<std::endl;
		}
		std::cout<<"------------"<<std::endl;
	}
}