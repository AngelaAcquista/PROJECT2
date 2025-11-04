#pragma once 
#include "Restaurant.h"
#include <vector>
#include <iostream>

using namespace std;

class MaxHeap{

  vector<Restaurant> heap;

  void heapifyup(int n){
    
    while (n != 0 && heap[n] > heap[(n - 1) / 2]){
      
        swap(heap[n], heap[(n - 1) / 2]);
        n = (n - 1) / 2;
    }
  }
  void heapifydown(int n){

    int largest = n;
    int l = 2 * n + 1;
    int r = 2 * n + 2;

    if (l < heap.size() && heap[l] > heap[largest]){
          
        largest = l;
    }
    if (r < heap.size() && heap[r] > heap[largest]){
          
        largest = r;
    }
    if (largest != n){
          
        swap(heap[n], heap[largest]);
        heapifydown(largest);
    }
  }
  public:

    void insert(const Restaurant& newrestaurant){

      heap.push_back(newrestaurant);
      heapifyup(heap.size() - 1);
    }
    const Restaurant peekmax(){

      if(isempty()){
        return Restaurant(); 
      }
      return heap.at(0);
    }
    Restaurant extractmax(){
      
      if(isempty()){
        return Restaurant(); 
      }
      if (heap.size() == 1){
        
            Restaurant max = heap.at(0);
            heap.pop_back();
            return max;
      }
      Restaurant max = heap.at(0);
      heap.at(0) = heap.back();
      heap.pop_back();
      heapifydown(0);

      return max;
    }
    bool isempty() const{
      
      return heap.empty();
    }
    size_t size() const{

      return heap.size();
    }
};
