#include<bits/stdc++.h>
using namespace std;

// QUESTION OBJECT
class Question
{
public:
	Question(int _moneyVal, string _question, string _answer);
private:
	int moneyVal;
	string question;
	string answer;
};
Question::Question(int _moneyVal, string _question, string _answer)
{
	moneyVal = _moneyVal;
	question = _question;
	answer = _answer;
}
// read for jeopardy or double jeopardy, money value, questions, and answers
vector<Question> ReadTSV(string file)
{
	vector<Question> JeopardyVector;
	ifstream myFile;
	myFile.open(file);
	int test = 0;

	// 9 categories
	string round;
	string value;
	int moneyValue;
	string dailyDouble;
	string category;
	string comments;
	string question;
	string answer;
	string airDate;
	string notes;
	string line;
	
	// take out first line
	getline(myFile, line);

	// push values into Question object vector
	while (myFile.good() && test != 35) 
	{
		getline(myFile, round, '\t');
		getline(myFile, value, '\t');
		moneyValue = stoi(value);
		getline(myFile, dailyDouble, '\t');
		getline(myFile, category, '\t');
		getline(myFile, comments, '\t');
		getline(myFile, question, '\t');
		getline(myFile, answer, '\t');
		getline(myFile, line);


		cout << value << " | " << dailyDouble << ", " << question << " | " << answer << endl;
		JeopardyVector.push_back(Question(moneyValue, question, answer));
		test++;
		cout << endl;

	}
	return JeopardyVector;
}

int main()
{
	vector<Question> JeopardyVector = ReadTSV("kids_teen.tsv");

	cout << "JeopardyVector size: " << JeopardyVector.size() << endl;
	cout << endl;

	cout << "JEAPARDY STUDY TOOL MENU" << endl << "1. Study Mode" << endl << "2. My Stats" << endl;
	// 3 CONSECUTIVE CORRECTS BRINGS YOU TO NEXT LEVEL ONE.
	// 1 INCORRECT RESETS YOUR CONSECUTIVE CHECK.
	// 2 CONSECUTIVE INCORRECT BRINGS YOU BACK 1. 
	return 0;
};