#include "heap.h"
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

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
    while (myFile.good() && test != 1000)
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

        //cout << value << " | " << dailyDouble << ", " << question << " | " << answer << endl;
        JeopardyVector.push_back(Question(moneyValue, question, answer));
        test++;

        //cout << endl;
    }
    return JeopardyVector;
}

int main()
{
    vector<Question> JeopardyVector = ReadTSV("kids_teen.tsv");
    int correct = 0;

    //choose a data structure
    cout << "JEOPARDY STUDY TOOL: CHOOSE A DATA STRUCTURE" << endl << "1. Heap" << endl << "2. Map" << endl;
    int menuChoice, dataStructure, option, answer, stat;
    cin >> dataStructure;

    //heap
    if (dataStructure == 1) {
        //make heap
        Heap heap(JeopardyVector.size());
        heap.makeHeap(JeopardyVector);

        //study mode or stats
        cout << "JEOPARDY STUDY TOOL: MODE" << endl << "1. Study Mode" << endl << "2. My Stats" << endl << "3. Quit" << endl;

        cout << endl;

        cin >> menuChoice;



        while (menuChoice != 3) {
            //study mode

            if (menuChoice == 1) {

                cout << "STUDY MODE: CHOOSE ONE" << endl << "1. Read Question" << endl << "2. Advance Level" << endl << "3. Back" << endl;
                cout << endl;
                int option;
                cin >> option;

                while (option != 3) {
                    //read question
                    if (option == 1) {
                        Question q = heap.getQuestion();
                        cout << "Difficulty: " << q.getMoneyVal() << endl << q.getQuestion() << "?" << endl;
                        cout << "Press Any Button To Display Answer" << endl;
                        int answer;
                        cin >> answer;
                        cout << q.getAnswer() << endl;
                        cout << "Was Your Answer Correct?" << endl << "1. Yes" << endl << "2. No" << endl;
                        cin >> stat;
                        if (stat == 1) {
                            correct++;
                        }
                        if (stat == 2) {
                            correct = 0;
                        }

                        //3 consecutive correct answers advances level
                        if (correct == 3) {
                            heap.advanceLevel(heap.getMin().getMoneyVal(), 0);
                        }
                    }

                    //advance level
                    else if (option == 2) {
                        heap.advanceLevel(heap.getMin().getMoneyVal(), 0);
                        cout << "New Level: " << heap.getMin().getMoneyVal() << endl;
                    }

                    //print choices again: read or advance (heap)
                    cout << "STUDY MODE: CHOOSE ONE" << endl << "1. Read Question" << endl << "2. Advance Level" << endl << "3. Back" << endl;
                    cin >> option;
                }
            }

            //my stats
            else if (menuChoice == 2) {
                cout << "Correct Answers: " << correct << endl << "Level: " << heap.getMin().getMoneyVal() << endl;
            }

            //print choices again: study mode or stats (heap)
            cout << "JEOPARDY STUDY TOOL: MODE" << endl << "1. Study Mode" << endl << "2. My Stats" << endl << "3. Quit" << endl;
            cin >> menuChoice;
        }
    }
    return 0;
}