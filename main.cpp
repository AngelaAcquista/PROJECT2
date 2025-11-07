#include <SFML/Graphics.hpp>
#include "MainPage.h"
#include "LocationPage.h"
#include "FoodTypePage.h"
#include "Hashtable.h"
#include "MaxHeap.h"
#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;

void loadingRestaurant(){
    //declare a 2D vector to organize data for each restaurant
    vector<vector<string>> restaurantData;
    //read and extract data from 10 files
    //reference for reading a csv file:
    //https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad
    for(int i = 1; i <= 10; i++){
        
        string filePath = "../dataset/380K_US_Restaurants_";
        filePath += to_string(i) + ".csv";
        ifstream file(filePath);
        //add error handling if a file cannot be opened
        if(!file.is_open()) cerr << "Error opening " << filePath << endl;
        //to avoid reading the header row
        string line;
        getline(file, line);
        //total # of datapoints: 112,000
        //for each iteration, extract the necessary data for each restaurant
        for(int row = 0; row < 1600; row++){
            
            string dataPoint;
            getline(file, line);
            istringstream stream(line);
            vector<string> currRow;
            //for each row, read and extract the data from the first 7 columns
            for(int col = 0; col < 7; col++){
                
                if(col == 6){
                    
                    getline(stream, dataPoint, '[');
                    if (dataPoint.size() > 4) dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                    else dataPoint = "";
                    currRow.push_back(dataPoint);
                    
                }else{
                    
                    getline(stream, dataPoint, ',');
                    currRow.push_back(dataPoint);
                }
            }
            restaurantData.push_back(currRow);
        }
    }
    //declare hashmap
    Hashtable hashmap;

    for(int i = 0; i < 10; i++){
        
        string title = restaurantData[i][0], category = restaurantData[i][2], phone = restaurantData[i][5], address = restaurantData[i][6], key = category + ": ";
        float rating = stof(restaurantData[i][3]);
        Restaurant currRestaurant(title, phone, rating, address);
    }
    cout << "Finished running original PROJECT2 backend logic.\n";
}
int main(){

    RenderWindow window(VideoMode(1000, 1100), "Restaurant Finder", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    //loadingRestaurant();
    //Different windows
    MainPage mainPage;
    LocationPage locationPage;
    FoodTypePage foodTypePage;
    //Controller
    string currPage = "Main";

    while(window.isOpen()){
        
        Event event{};
        
        while(window.pollEvent(event)){
            
            if(event.type == Event::Closed) window.close();
            //Main Info
            if(currPage == "Main"){
                
                if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                    
                    Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                    if(mainPage.isLocationClicked(mousePos)){
                        
                        cout << "[MainPage] Location button clicked.\n";
                        currPage = "Location";
                        
                    }else if(mainPage.isFoodTypeClicked(mousePos)){
                        
                        cout << "[MainPage] Food Type button clicked.\n";
                        currPage = "Food";
                    }
                }
            }

            //Location Info
            else if(currPage == "Location"){
                
                locationPage.Event(event, window);

                if(Keyboard::isKeyPressed(Keyboard::Escape)){
                    
                    cout << "[LocationPage] Returning to Main.\n";
                    currPage = "Main";
                }
            }
            //Food Type Info
            else if(currPage == "Food"){
                
                foodTypePage.Event(event, window);

                if(Keyboard::isKeyPressed(Keyboard::Escape)){
                    
                    cout << "[FoodTypePage] Returning to Main.\n";
                    currPage = "Main";
                }
            }
        }

        //Drawing
        window.clear(Color(250, 243, 232)); // soft beige

        if(currPage == "Main") mainPage.draw(window);
            
        else if(currPage == "Location") locationPage.draw(window);
            
        else if(currPage == "Food") foodTypePage.draw(window);

        window.display();
    }
    return 0;
}
