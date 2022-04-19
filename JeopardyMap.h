#pragma once
#include "question.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;
//hash table to implement questions
class JeopardyHashTable {
private:
    static const int HashGroups = 100;
    list<pair<int, vector<Question> > > table[HashGroups];
public:
    int hashFunction(int key){
        return (key / 100);
    };
    bool isEmpty() const{
        int sum = 0;
        for (int i = 0; i<HashGroups; i++){
            sum += table[i].size();
        }
        if (!sum){
            return true;
        }
        return false;
    }
    void insertQuestion(int key, Question q){
        int hashVal = hashFunction(key);
        auto& cell = table[hashVal];
        auto iterBegin = begin(cell);
        bool keyExists = false;
        for (;iterBegin != end(cell); iterBegin++){
            if (iterBegin->first == key){
                keyExists = true;
                iterBegin->second.push_back(q);
                break;
            }
        }

        if (!keyExists) {
            vector<Question> questions;
            questions.push_back(q);
            cell.emplace_back(key, questions);
        }
        return;
    };
    Question getQuestion(int key){
        int hashVal = hashFunction(key);
        auto& cell = table[hashVal];
        auto iter = begin(cell);
        for(;iter!=end(cell); iter++){
            if (iter->first == key){
                srand((unsigned)time(0));
                int randomIndex = rand() % iter->second.size();
                return iter->second[randomIndex];
            }
        }
        //return a question telling no question or answer found at that level
        return Question(key, "no question found at level", "no answer found at level");
    };
    bool checkLevel(int key){
        int hashVal = hashFunction(key);
        auto& cell = table[hashVal];
        auto iter = begin(cell);
        for(;iter!=end(cell); iter++){
            if (iter->first == key && iter->second.size()>0){
                return true;
            }
        }
        return false;
    }
};



