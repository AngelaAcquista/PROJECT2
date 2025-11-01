#pragma once 
#include "Restaurant.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class MaxHeap{

  priority_queue<Restaurant, vector<Restaurant>> heap;

  public:

    void insert(const vector<Restaurant>& restaurants){

      for(Restaurant restaurant : restaurants){
        
        heap.push(restaurant);
      }
    }

    Restaurant highestratedrestaurant(){
      
      return heap.top();
    }

    vector<Restaurant> sortedrestaurants(){
      
      vector<Restaurant> sorted;
      
      while(!heap.empty()){

        sorted.push_back(heap.top());
        heap.pop();
      }
      return sorted;
    }
};
