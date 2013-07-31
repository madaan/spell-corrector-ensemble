#include "FrequencyCounter.h"

using namespace std;

struct WordDetails {
	string word;
	int frequency;
	float probability;
};

set<WordDetails> wordsInfo;
ifstream inFile;

void openFile() {
	inFile.open("../data/out.txt");
}

void closeFile() {
	inFile.close();
}

float getTotalFrequency() {
	return float(18302813);
}

int findWordFrequency(string searchWord) {
	int flag = 0;
	string parseLine;
	openFile();
	while (inFile.good()) {
		getline(inFile, parseLine);
		int pos = parseLine.find(searchWord);

		if (pos > -1
				&& (searchWord.length()
						== parseLine.substr(0, parseLine.find(" ")).length())) // string::npos is returned if string is not found
				{
			flag = 1;
			break;
		}
	}

	closeFile();
	if (flag == 1) {
		string freq = parseLine.substr(parseLine.find(" "), parseLine.length());
		char * S = new char[freq.length() + 1];
		std::strcpy(S, freq.c_str());
		return atoi(S);

	} else {

		return 1;
	}

}

bool operator<(const WordDetails& left, const WordDetails& right) {
	return left.frequency >= right.frequency;
}

void countFrequency(set<string> correctedWordSet) {

	string searchWord;

	set<string>::iterator iter;

	for (iter = correctedWordSet.begin(); iter != correctedWordSet.end();
			++iter) {
		searchWord = *iter;
		int frequency = findWordFrequency(searchWord);
		float probability = (float) frequency / getTotalFrequency();
		WordDetails wdetail;
		wdetail.word = searchWord;
		wdetail.frequency = frequency;
		wdetail.probability = probability;
		wordsInfo.insert(wdetail);

	}

}


void getHighestFrequencyCountWord(set<string> correctList,int priority) {

	if(correctList.size() > 0)
	{
	countFrequency(correctList);

	set<WordDetails>::iterator iter;

	string correctWord = "";

	if (priority == 1) {
		cout << endl << "OneDistanceReplacement Corrections"<<endl;
	} else if (priority == 2) {
		cout << endl << "TwoDistanceReplacement Corrections"<<endl;
	} else if (priority == 3) {
		cout << endl << "Single Deletions Corrections"<<endl;
	} else if (priority == 4) {
		cout << endl << "Single Insertions Corrections"<<endl;
	}

	for (iter = wordsInfo.begin(); iter != wordsInfo.end(); ++iter) {
		WordDetails words = *iter;

	cout<<iter->word<<"  "<<iter->frequency<<"  "<<iter->probability<<endl;
		
	}

	wordsInfo.clear();

	}
}



