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
		std::vector<myWord> allWords;
		std::vector<myWord> remainingWords;
		std::vector<mySolution> checkedSolutions;
		void getWords(){
			std::string tword = "";
			while (true) {
				std::cout<<"Input possible word: ";
				std::cin>>tword;
				if(tword[0]=='.'){
					break;
				} else if(tword[0]=='-'){
					this->removeWord(tword.substr(1,UINT_MAX));
				} else {
					allWords.push_back(myWord(tword));
				}
			}
			this->remainingWords=this->allWords;
			this->printRemainingWords();
		}
		void getSolutions(){
			mySolution retSol;
			while(true){
				std::cout<<"Input Solution Word: ";
				std::cin>>retSol.str;
				if (retSol.str[0]=='.'){
					break;
				} else if (retSol.str[0]=='-'){
					this->removeSolution(retSol.str.substr(1,UINT_MAX));
				} else {
					std::cout<<"Input Correct Letters: ";
					std::cin>>retSol.correct;
					this->checkedSolutions.push_back(retSol);
					this->checkSolutions();
					this->printRemainingWords();
				}
			}
		}
		void printRemainingWords(){
			std::cout<<"Score: The lower the better."<<std::endl;
			for(unsigned int i=0;i<this->remainingWords.size();i++){
				std::cout<<this->remainingWords[i].str;
				std::cout<<" Score: ";
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
		void removeWord(std::string _str){
			for(unsigned int i=0;i<this->allWords.size();i++){
				if(_str==this->allWords[i].str){
					this->allWords.erase(this->allWords.begin()+i);
					return;
				}
			}
		}
		void removeSolution(std::string _str){
			for(unsigned int i=0;i<this->checkedSolutions.size();i++){
				if(_str==this->checkedSolutions[i].str){
					this->checkedSolutions.erase(this->checkedSolutions.begin()+i);
					return;
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


int main(){
	myInstance instance;
	instance.getWords();
	instance.getSolutions();
}
