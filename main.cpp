#include <iostream>
#include <fstream>
#include <sstream>
//#include <queue>
#include <string>
#include "Hashtable.h"
#include "Restaurant.h"
#include <vector>

using namespace std;

int main(){
  ifstream file1("dataset/380K_US_Restaurants_1.csv");

  if (!file1.is_open()) {
     cout << "Unable to open file" << endl;
  }


  return 0;
}
