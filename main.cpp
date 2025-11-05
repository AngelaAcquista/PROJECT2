#include <iostream>
#include <chrono>
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
  for(int i = 1; i <= 10; i++){
      
      string filePath = "dataset/380K_US_Restaurants_";
      filePath += to_string(i) + ".csv";
      ifstream file(filePath);
      //add error handling if a file cannot be opened
      if(!file.is_open()){
          
          cerr << "Error opening " << filePath << endl;
      }
      //to avoid reading the header row
      string line;
      getline(file, line);

      //for each iteration, extract the necessary data for each restaurant
      while(getline(file, line)){

          istringstream stream(line);
          vector<string> currRow;
          string dataPoint;

          //for each row, read the extract the data from the first 7 columns
          for(int col = 0; col < 7; col++){
              
              if(col == 6){
                  
                  getline(stream, dataPoint, '[');
                  dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                  currRow.push_back(dataPoint);
                  
              }else{
                  
                  getline(stream, dataPoint, ',');
                  currRow.push_back(dataPoint);
              }
          }
          restaurantData.push_back(currRow);
      }
  }
  //declare hashmap and use the insert function
  Hashtable hashmap;
    
  for(int i = 0; i < restaurantData.size(); i++){

       string title = restaurantData[i][0];
       string category = restaurantData[i][2];
       string ratingStr = restaurantData[i][3];
       string phone = restaurantData[i][5];
       string address = restaurantData[i][6];
       float rating = 0.0f;

        try{
            
            rating = stof(ratingStr);
            
        }catch(const invalid_argument&){
            
            rating = 0.0f;
        }

        //create key-value pair
        string cityState;
        int commaCount = 0;
      
        for(int j = 0; j < address.length(); j++){
            
            if(address[j] == ','){
                
                commaCount++;
                
                if(commaCount == 2){
                    
                    cityState = address.substr(j + 2);
                }
            }
        }
        cityState = cityState.substr(0, cityState.find(',') + 4);
        string key = category + ": " + cityState;
        Restaurant currRestaurant(title, phone, rating, address);
        hashmap.insert(key, currRestaurant);

    }
    //add code here for inserting into max heap or somewhere else idk lol
    MaxHeap();

    //print menu options and handle user input
     bool windowOpen = true;
     string foodCategory;
     string city;
     string state;
    
     while(windowOpen){
         
         cout << "Welcome to Restaurant Scout- find top-rated restaurants near you" << endl;
         cout << "Enter food preference (ex: Fast food restaurant): " << endl;
         getline(cin, foodCategory);

         cout << "Enter city (ex: Gainesville): " << endl;
         getline(cin, city);

         cout << "Enter state (ex: FL): " << endl;
         getline(cin, state);

         string searchKey = foodCategory + ": " + city + ", " + state;
         vector<Restaurant> restaurants = hashmap.search(searchKey);

         if(restaurants.empty()){
             
             cout << "No restaurants found" << endl;
             
         }else{
             
             cout << "Restaurants found: " << endl;
             
             for(int i = 0; i < restaurants.size(); i++){
                 
                 cout << "Name: " << restaurants[i].getTitle() << endl;
                 cout << "Rating: " << restaurants[i].getRating() << endl;
                 cout << "Phone: " << restaurants[i].getPhone() << endl;
                 cout << "Address: " << restaurants[i].getAddress() << endl;
                 cout << endl;
             }
         }
         windowOpen = false;
     }
  return 0;
}
