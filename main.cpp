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

  //read and extract data from 15 files
  for (int i = 1; i <= 15; i++) {
      string filePath = "dataset/380K_US_Restaurants_";
      filePath += to_string(i) + ".csv";
      ifstream file(filePath);

      //add error handling if a file cannot be opened
      if (!file.is_open()) {
          cerr << "Error opening " << filePath << endl;
      }

      //to avoid reading the header row
      string line;
      getline(file, line);

      //testing the first 10 rows from the dataset for now
      //for each iteration, extract the necessary data for each restaurant
      for (int row = 0; row < 10; row++) {
          string line;
          getline(file, line);
          istringstream stream(line);
          vector<string> restaurantData;
          string dataPoint;

          //for each row, read the extract the data from the first 7 columns
          for (int col = 0; col < 7; col++) {
              if (col == 6) {
                  getline(stream, dataPoint, '[');
                  dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                  cout << dataPoint << endl;
                  restaurantData.push_back(dataPoint);
              }
              else {
                  getline(stream, dataPoint, ',');
                  cout << dataPoint << endl;
                  restaurantData.push_back(dataPoint);
              }
          }

          cout << i << endl;

      }



  }



  return 0;
}
