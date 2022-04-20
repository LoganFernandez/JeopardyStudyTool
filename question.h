#include <iostream>
#pragma once
using namespace std;

class Question{
    int moneyVal;
    string question;
    string answer;
public:
    Question(){
        moneyVal = 0;
        question = "";
        answer = "";
    }
    Question(int money, string q, string a){
        moneyVal = money;
        question = q;
        answer = a;
    }

    int getMoneyVal(){
        return moneyVal;
    }

    string getQuestion(){
        return question;
    }

    string getAnswer(){
        return answer;
    }
};
