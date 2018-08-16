#ifndef _QUIZ_H
#define _QUIZ_H
#include "game.h"
#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::string;

class Quiz
{
public:
	
	Quiz(int index);
	
	vector<string> questions;
	vector<string> answers;

	string currQn = "";
	string currAns = "";
	string attempt = "";

	void loadQuiz(); //load from files

	void query(int index); //ask the question at index

	bool checkAns(); //checks if given input is same as answer

};

#endif