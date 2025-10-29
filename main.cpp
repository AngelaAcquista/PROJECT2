#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
  ifstream file1("dataset/380K_US_Restaurants_1.csv");

  if (!file1.is_open()) {
     cout << "Unable to open file" << endl;
  }

 for (int i = 0; i < 1; i++) {
     string line;
     getline(file1, line);
     istringstream stream(line);

     string token;
     while (getline(stream, token, ',')) {
         cout << "Column: " << token << endl;
     }


 }


  return 0;
}
