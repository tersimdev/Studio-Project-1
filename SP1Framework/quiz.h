#ifndef _QUIZ_H
#define _QUIZ_H
#include "Framework\console.h"
#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::string;

enum OUTCOMES
{
	WIN_ENEMY = 0,
	LOSE_ENEMY,
	WIN_BOSS,
	LOSE_BOSS
};

class Quiz
{
public:
	
	Quiz(int index);
	
	vector<string> questions;
	vector<string> answers;

	string currQn = "";
	vector<string> currAns;
	string attempt = "";

	void loadQuiz(); //load from files

	void query(); //ask question at random
	void query(int index); //ask the question at index

	bool checkAns(); //checks if given input is same as answer(s)

	void quizResult(int choice, string* output, string* answers); //feedback for quiz- answers etc

private:

	void reset(); //reinits the current answers, qns and attempt
};

#endif