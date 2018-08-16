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
	this->currQn = this->questions[index];
	string answer = "";
	for (int i = 0; i < this->answers[index].length() + 1; i++)
	{
		if (i == this->answers[index].length() || this->answers[index][i] == '|')
		{
			this->currAns.push_back(answer);
			answer = "";
			continue;
		}
		else
			answer += (this->answers[index])[i];
	}
}

void Quiz::query()
{
	Quiz::query(rand() % this->questions.size());
}

bool Quiz::checkAns()
{
	//convert both to uppercase
	std::transform(attempt.begin(), attempt.end(), attempt.begin(), ::toupper);
	if (currAns.size() == 0)
		return NULL;
	for (auto i : this->currAns) //loop and check through all possible answers
	{
		std::transform(i.begin(), i.end(), i.begin(), ::toupper);
		//check if same
		if (this->attempt == i) return true;
	}
	return false;
}

void Quiz::reset()
{
	this->currQn = "";
	this->currAns.clear();
	this->attempt = "";
}
