#include "quiz.h"
#include <algorithm> // for std::transform


Quiz::Quiz(int index)
{
	this->loadQuiz();
	this->query(index);
	this->attempt = "";
}

void Quiz::loadQuiz()
{
	std::ifstream Qns("Quiz/Questions.txt");
	std::ifstream Ans("Quiz/Answers.txt");
	string line = "";
	while (getline(Qns, line))
	{
		this->questions.push_back(line);
	}
	while (getline(Ans, line))
	{
		this->answers.push_back(line);
	}
}

void Quiz::query(int index)
{
	this->currAns = this->answers[index];
	this->currQn = this->questions[index];
}

bool Quiz::checkAns()
{
	//convert both to uppercase
	std::transform(attempt.begin(), attempt.end(), attempt.begin(), ::toupper);
	std::transform(currAns.begin(), currAns.end(), currAns.begin(), ::toupper);
	//check if same
	if (this->attempt == this->currAns) return true;
	else return false;
}
