#pragma once 
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class MaxHeap{

  priority_queue<float> heap;

  public:

    void insert(const vector<float>& ratings){

      for(float rating : ratings){
        
        heap.push(rating);
      }
    }

    float highestrating(){
      
      return heap.top();
    }

    vector<float> sortedratings(){
      
      vector<float> sorted;
      
      while(!heap.empty()){

        sorted.push_back(heap.top());
        heap.pop();
      }
      return sorted;
    }
};
