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

    void insert(float& rating){

      heap.push_back(newrating);
      heapifyup(heap.size() - 1);
    }
    Restaurant peekmax(){

      
    }
    Restaurant extractmax(){

      
    }
    bool isempty() const{
      
      return heap.empty();
    }
    size_t size() const{

      return heap.size();
    }
};
