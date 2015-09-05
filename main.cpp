#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <climits>

class myWord;
int similarity(const std::string& left,const std::string& right);
void removeWord(std::string _str,std::vector<myWord>& vect);

class myWord{
	public:
		std::string str;
		int score;
		std::vector<int> fragments(const std::vector<myWord>& vect) const{
			std::vector<int> retVect(this->str.size()+1);
			for (unsigned int i=0;i<vect.size();i++){
				retVect.at(similarity(this->str,vect[i].str))++;
			}
			return retVect;
		}
		int calcScore(const std::vector<myWord>& vect){//The less the score, the better
			std::vector<int> fragVect = this->fragments(vect);
			int scr=0;
			for (unsigned int i=0;i<fragVect.size();i++){
				scr+=pow(fragVect[i],2);
			}
			this->score=scr;
			return scr;
		}
		myWord(std::string& _str): str(_str){}
};

class mySolution{
	public:
		int correct;
		std::string str;
		bool checkSolution(myWord& word) const{
			if(similarity(word.str,this->str)==this->correct){
				return true;
			}
			return false;
		}

};

class myInstance{
	public:
		int wordNumber;
		std::vector<myWord> allWords;
		std::vector<myWord> remainingWords;
		std::vector<mySolution> checkedSolutions;
		void printRemainingWords(){
			for(unsigned int i=0;i<this->remainingWords.size();i++){
				std::cout<<this->remainingWords[i].str;
				std::cout<<":Score: ";
				std::cout<<this->remainingWords[i].calcScore(this->remainingWords)<<std::endl;
			}
		}
		void checkSolutions(){
			this->remainingWords = std::vector<myWord>();
			bool check;
			for (int i=0;i<this->allWords.size();i++){
				check=true;
				for (int j=0;j<this->checkedSolutions.size();j++){
					if(!this->checkedSolutions[j].checkSolution(this->allWords[i])){
						check=false;
						break;
					}
				}
				if(check){
					this->remainingWords.push_back(this->allWords[i]);
				}
			}
		}
};

int similarity(const std::string& left,const std::string& right){
	int correctLetters=0;
	for(unsigned int i=0;i<left.size()&&i<right.size();i++){
		if(left[i]==right[i]){
			correctLetters++;
		}
	}
	return correctLetters;
}

void getWords(std::vector<myWord>& words){
	std::string tword = "";
	while (true) {
		std::cout<<"Input possible word: ";
		std::cin>>tword;
		if(tword[0]=='.'){
			break;
		} else if(tword[0]=='-'){
			removeWord(tword.substr(1,UINT_MAX),words);
		} else {
			words.push_back(myWord(tword));
		}
	}
}

void removeWord(std::string _str,std::vector<myWord>& vect){
	for(unsigned int i=0;i<vect.size();i++){
		if(_str==vect[i].str){
			vect.erase(vect.begin()+i);
			return;
		}
	}
}

void removeSolution(std::string _str,std::vector<mySolution>& vect){
	for(unsigned int i=0;i<vect.size();i++){
		if(_str==vect[i].str){
			vect.erase(vect.begin()+i);
			return;
		}
	}
}

mySolution inputSolution(){
	mySolution retSol;
	std::cout<<"Input Solution Word: ";
	std::cin>>retSol.str;
	if (retSol.str[0]=='.'){
		retSol.correct=0;
	} else if (retSol.str[0]=='-'){
		retSol.correct=0;
	} else {
		std::cout<<"Input Correct Letters: ";
		std::cin>>retSol.correct;
	}
	return retSol;
}

int main(){
	myInstance instance;
	getWords(instance.allWords);
	instance.remainingWords=instance.allWords;
	instance.printRemainingWords();

	mySolution tempSol;
	while (true){
		tempSol = inputSolution();
		if (tempSol.str[0]=='-'){
			removeSolution(tempSol.str.substr(1,UINT_MAX),instance.checkedSolutions);
		} else if (tempSol.str[0]=='.'){
			return 0;
		} else {
			instance.checkedSolutions.push_back(tempSol);
			instance.checkSolutions();
			instance.printRemainingWords();
		}
	}
}