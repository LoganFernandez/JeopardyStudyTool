#include "question.h"
#include <vector>

using namespace std;

class Heap {
    Question *heap;
    int capacity;
    int heapSize;
public:
    //constructor
    Heap(int numMoneyVal) {
        heapSize = 0;
        capacity = numMoneyVal;
        heap = new Question[capacity];
    }

    void insert(Question& q){
        heapSize++;
        int child = heapSize - 1;
        heap[child] = q;

        heapifyUp(q, child);
    }

    void heapifyUp(Question& q, int child){
        int parent = (child - 1) / 2;

        if(heap[parent].getMoneyVal() > heap[child].getMoneyVal()){
            Question temp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = temp;

            heapifyUp(q, parent);
        }
    }

    Question extractMin(){

        Question min = heap[0];
        heap[0] = heap[heapSize-1];
        heapSize--;
        heapifyDown(0);

        return min;
    }

    void heapifyDown(int index){

        if(heapSize <= (2 * index) + 1){
            return;
        }

        //find the smallest child
        int left = (2 * index) + 1;
        int right = (2 * index) + 2;
        int smallest = index;
        if(heap[left].getMoneyVal() < heap[smallest].getMoneyVal()){
            smallest = left;
        }
        if(heap[right].getMoneyVal() < heap[smallest].getMoneyVal()){
            smallest = right;
        }
        if(heap[left].getMoneyVal() < heap[right].getMoneyVal()){
            smallest = left;
        }
        if(heap[right].getMoneyVal() < heap[left].getMoneyVal()){
            smallest = right;
        }

        if(smallest != index){
            //swap child and node
            Question temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;

            //continue heapify down
            heapifyDown(smallest);
        }

    }

    void deleteLevel(int index, int startLevel){
        heap[index] = heap[heapSize-1];
        heapSize--;
        heapifyDown(index);

        int left = (2 * index) + 1;
        int right = (2 * index) + 2;
        if(heap[left].getMoneyVal() == startLevel){
            deleteLevel(left, startLevel);
        }
        if(heap[right].getMoneyVal() == startLevel){
            deleteLevel(right, startLevel);
        }
    }

    void advanceLevel(int startLevel, int curr){

        for(int i = 0; i < heapSize; i++){
            if(heap[i].getMoneyVal() == startLevel){
                deleteLevel(i, startLevel);
                advanceLevel(startLevel, curr);
            }
        }
    }

    void makeHeap(vector<Question> jeopardy){
        for(int i = 0; i < jeopardy.size(); i++){
            insert(jeopardy[i]);
        }
    }

    Question getQuestion(){
        return extractMin();
    }

    Question getMin(){
        return heap[0];
    }

    void print(){
        for(int i = 0; i < heapSize; i++){
            cout << "level: " << heap[i].getMoneyVal();
        }
    }
};