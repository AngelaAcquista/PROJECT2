#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Hashtable.h"
#include "Restaurant.h"
#include <vector>

using namespace std;

int main(){

    //declare a 2D vector to organize data for each restaurant
    vector<vector<string>> restaurantData;

  //read and extract data from 15 files
  for (int i = 1; i <= 15; i++){
      
      string filePath = "dataset/380K_US_Restaurants_";
      filePath += to_string(i) + ".csv";
      ifstream file(filePath);

      //add error handling if a file cannot be opened
      if (!file.is_open()){
          
          cerr << "Error opening " << filePath << endl;
      }
      //to avoid reading the header row
      string line;
      getline(file, line);
      //testing the first 10 rows from the dataset for now
      //for each iteration, extract the necessary data for each restaurant
      for (int row = 0; row < 2; row++){
          string line;
          getline(file, line);
          istringstream stream(line);
          vector<string> currRow;
          string dataPoint;

          //for each row, read the extract the data from the first 7 columns
          for (int col = 0; col < 7; col++){
              
              if (col == 6){
                  
                  getline(stream, dataPoint, '[');
                  dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                  currRow.push_back(dataPoint);
              }
              else{
                  
                  getline(stream, dataPoint, ',');
                  currRow.push_back(dataPoint);
              }
          }
          restaurantData.push_back(currRow);
      }
  }
    //declare a vector of restaurant objects
    vector<Restaurant> restaurants;
    
    for (int i = 0; i < 1; i++){
        
       string title = restaurantData[i][0];
       string category = restaurantData[i][2];
       float rating =  stof(restaurantData[i][3]);
       string phone = restaurantData[i][5];
       string address = restaurantData[i][6];

        restaurants.emplace_back(title, phone, rating, address);
        // cout << title << endl;
        // cout << category << endl;
        // cout << rating << endl;
        // cout << phone << endl;
        // cout << address << endl;
    }
  return 0;
}
