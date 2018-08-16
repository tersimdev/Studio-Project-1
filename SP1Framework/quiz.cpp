#include "quiz.h"
#include <algorithm> // for std::transform


void Quiz::loadQuiz()
{

}

void Quiz::query(int index)
{
	this->currAns = this->answers[index];
	this->currQn = this->questions[index];
}

bool Quiz::checkAns(string attempt)
{
	//convert both to uppercase
	std::transform(attempt.begin(), attempt.end(), attempt.begin(), ::toupper);
	std::transform(currAns.begin(), currAns.end(), currAns.begin(), ::toupper);
	//check if same
	if (attempt == this->currAns) return true;
	else return false;
}
