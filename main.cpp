#include <SFML/Graphics.hpp>
#include "MainPage.h"
#include "LocationPage.h"
#include "FoodTypePage.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main(){

    RenderWindow window(VideoMode(1000, 1100), "Restaurant Finder", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
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
