#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MaxHeap.h"
#include "Hashtable.h"
#include "Restaurant.h"
#include <vector>

using namespace std;

int main(){

    //declare a 2D vector to organize data for each restaurant
    vector<vector<string>> restaurantData;

  //read and extract data from 10 files
  for (int i = 1; i <= 2; i++){
      
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

      //for each iteration, extract the necessary data for each restaurant
      while (getline(file, line)){

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

    //declare hashmap
    Hashtable hashmap;
    
    for (int i = 0; i < restaurantData.size(); i++){

       string title = restaurantData[i][0];
       string category = restaurantData[i][2];
       string ratingStr = restaurantData[i][3];
       string phone = restaurantData[i][5];
       string address = restaurantData[i][6];
       float rating = 0.0f;

        try {
            rating = stof(ratingStr);
        } catch (const invalid_argument&) {
            rating = 0.0f;
        }


        //create key-value pair
        string cityState;
        int commaCount = 0;
        for (int j = 0; j < address.length(); j++) {
            if (address[j] == ',') {
                commaCount++;
                if (commaCount == 2) {
                    cityState = address.substr(j + 2);
                    break;
                }
            }
        }

        string key = category + ": ";

        Restaurant currRestaurant(title, phone, rating, address);
        hashmap.insert(key, currRestaurant);

        cout << cityState << endl;
    }




  return 0;
}
