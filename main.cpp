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
  //testing parsing through one csv file first
  ifstream file1("dataset/380K_US_Restaurants_1.csv");

  //add an if condition in case the file cannot be opened
  if (!file1.is_open()) {
     cerr << "Unable to open file" << endl;
  }

    //to avoid reading the header row
    string line;
    getline(file1, line);

    //testing the first 10 rows from the dataset for now
    //for each iteration, extract the necessary data for each restaurant
     for (int i = 0; i < 10; i++) {
         string line;
         getline(file1, line);
         istringstream stream(line);
         vector<string> restaurantData;
         string dataPoint;

         //for each row, read the extract the data from the first 7 columns
         for (int j = 0; j < 7; j++) {
             if (j == 6) {
               getline(stream, dataPoint, '[');
                 dataPoint = dataPoint.substr(0, dataPoint.size() - 3);
                 cout << dataPoint << endl;
                 restaurantData.push_back(dataPoint);
             }
             else {
                 getline(stream, dataPoint, ',');
                 cout << dataPoint << endl;
                 restaurantData.push_back(dataPoint);
             }
         }

    }




  return 0;
}
