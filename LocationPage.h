#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "MaxHeap.h"
#include "Hashtable.h"
#include "Restaurant.h"
#include "FileReader.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

class LocationPage{

    Font font;
    Text title, subtitle, inputFormat, options, maxheap, hashtable, searchTxt, buttonTxt, extraTxt, searchResult;
    RectangleShape input, searchButton, resultBox, textCursor;
    Texture iconTexture;
    RenderTexture staticLayer;
    Sprite icon, staticLayerSprite;
    Clock cursorTimer;
    bool showCursor = false, userIsTyping = false, showResult = false;
    string userIn;
    Hashtable locationTable;

public:

    void loadData(){
        
        vector<vector<string>> restaurantData;
        FileReader(restaurantData);

        //  Insert into hashtable
        for(auto &row : restaurantData){
            
            if(row.size() < 7) continue;

            string title = row[0], category = row[2], phone = row[5], address = row[6], key = "";
            int commaCount = 0;
            
            for(int i = 0; i < address.length(); i++){
                
                if(address[i] == ','){
                    
                    commaCount ++;
                    
                    if(commaCount == 2){
                        
                        key = address.substr(i + 2);
                        break;
                    }
                }
            }
            cout << key << endl;
            key = key.substr(0, key.find(',') + 4);
            cout << key << endl;
            float rating = 0.0f;
            
            try{
                
                if(!row[3].empty()) rating = stof(row[3]);
                
            }catch(...){ rating = 0.0f; }

            Restaurant r(title, phone, rating, address);
            locationTable.insert(key, r);
        }
        cout << "Location hashtable loaded successfully.\n";
    } //loading the city/state

    LocationPage(){
        
        if(!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) cerr << "Error loading font" << endl;
        //Title Info
        title.setFont(font);
        title.setString("Search by Location");
        title.setCharacterSize(42);
        title.setFillColor(Color(40,40,40));
        title.setPosition(500.f - title.getLocalBounds().width / 2.f, 250.f);
        //Subtitle Info
        subtitle.setFont(font);
        subtitle.setString("Enter a city and state to explore nearby restaurants");
        subtitle.setCharacterSize(24);
        subtitle.setFillColor(Color(110,110,110));
        subtitle.setPosition(500.f - subtitle.getLocalBounds().width / 2.f, 310.f);
        //input format
        inputFormat.setFont(font);
        inputFormat.setString("Example: Gainesville, FL");
        inputFormat.setCharacterSize(20);
        inputFormat.setFillColor(Color(110,110,110));
        inputFormat.setPosition(500.f - inputFormat.getLocalBounds().width / 2.f, inputFormat.getLocalBounds().height + 330.f);
        //Hashtable display time
        hashtable.setFont(font);
        hashtable.setString("Hashtable: ");
        hashtable.setCharacterSize(20);
        hashtable.setFillColor(Color(110,110,110));
        hashtable.setPosition(50.f, 1025.f);
        //MaxHeap display time
        maxheap.setFont(font);
        maxheap.setString("MaxHeap: ");
        maxheap.setCharacterSize(20);
        maxheap.setFillColor(Color(110,110,110));
        maxheap.setPosition(800.f, 1025.f);
        //Results Info
        searchResult.setFont(font);
        searchResult.setCharacterSize(22);
        searchResult.setFillColor(Color(40,40,40));
        searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);
        //Box for result Info (same as FoodTypePage)
        resultBox.setSize(Vector2f(520.f, 130.f));
        resultBox.setFillColor(Color(255,255,255, 230));
        resultBox.setOutlineColor(Color(200,200,200));
        resultBox.setOutlineThickness(2);
        resultBox.setPosition(240.f, 520.f);
        //Input box Info
        input.setSize(Vector2f(400.f, 55.f));
        input.setFillColor(Color::White);
        input.setOutlineColor(Color(180,180,180));
        input.setOutlineThickness(2);
        input.setPosition(260.f, 400.f);
        //Search Text Info
        searchTxt.setFont(font);
        searchTxt.setCharacterSize(22);
        searchTxt.setFillColor(Color(40,40,40));
        searchTxt.setPosition(275.f, 410.f);
        //Cursor Info
        textCursor.setSize(Vector2f(2.f, 30.f));
        textCursor.setFillColor(Color(40,40,40));
        textCursor.setPosition(searchTxt.getPosition().x + 2.f, searchTxt.getPosition().y + 5.f);
        cursorTimer.restart();
        //Search Button Info
        searchButton.setSize(Vector2f(140.f, 55.f));
        searchButton.setFillColor(Color(230,230,230));
        searchButton.setOutlineColor(Color(180,180,180));
        searchButton.setOutlineThickness(2);
        searchButton.setPosition(690.f, 400.f);
        
        extraTxt.setFont(font);
        extraTxt.setString("Enter");
        extraTxt.setCharacterSize(22);
        extraTxt.setFillColor(Color(40, 40, 40));
        // --- Center text inside the button dynamically ---
        FloatRect txtBounds = extraTxt.getLocalBounds();
        extraTxt.setOrigin(txtBounds.width / 2.f, txtBounds.height / 2.f + txtBounds.top);
        extraTxt.setPosition(
        searchButton.getPosition().x + searchButton.getSize().x / 2.f,
        searchButton.getPosition().y + searchButton.getSize().y / 2.f - 4.f );
        //Icon Info
        if(iconTexture.loadFromFile("../assets/pin.png")){
            
            iconTexture.setSmooth(true);
            icon.setTexture(iconTexture);
            icon.setScale(0.09f, 0.09f);
            icon.setPosition(205.f, 240.f);
        }
        staticLayer.create(1000.f, 1100.f);
        staticLayer.clear(Color::Transparent);
        staticLayer.draw(title);
        staticLayer.draw(subtitle);
        staticLayer.draw(inputFormat);
        staticLayer.draw(hashtable);
        staticLayer.draw(maxheap);
        staticLayer.draw(searchButton);
        staticLayer.draw(extraTxt);
        staticLayer.draw(icon);
        staticLayer.display();
        staticLayerSprite.setTexture(staticLayer.getTexture());
        //Load restaurant data
        loadData();
    }
    void Event(const sf::Event& event, const RenderWindow& window){
        
        if(event.type == Event::MouseButtonPressed){
            
            auto mouse = Mouse::getPosition(window);

            if(input.getGlobalBounds().contains(mouse.x, mouse.y)){
                
                userIsTyping = true;
                showCursor = true;
                cursorTimer.restart();
                
            }else{
                
                userIsTyping = false;
                showCursor = false;
            }
            if(searchButton.getGlobalBounds().contains(mouse.x, mouse.y)) cout << "Searching for location: " << userIn << endl;
        }
        //Typing Logic
        if(userIsTyping && event.type == Event::TextEntered){
            
            if(event.text.unicode == 8 && !userIn.empty()) userIn.pop_back();
                
            else if(event.text.unicode >= 32 && event.text.unicode < 128) userIn += static_cast<char>(event.text.unicode);
        
            searchTxt.setString(userIn);
            float textX = searchTxt.getPosition().x + searchTxt.getLocalBounds().width + 4.f;
            textCursor.setPosition(textX, searchTxt.getPosition().y +5.f);
            cursorTimer.restart();
            showCursor = true;
        }
        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){
            
            if(!userIn.empty()){
                
                cout << "Searching for location: " << userIn << endl;
                string input = userIn;
                //  First, try exact match
                vector<Restaurant> results = locationTable.search(input);
                //  If not found, try partial substring matches
                if(results.empty()){
                    
                    vector<string> testInputs;
                    //shorter substring to prevent out of range
                    for(size_t i = input.size(); i > 3; --i) testInputs.push_back(input.substr(0, i));
                    
                    for(const auto& sub : testInputs){
                        
                        auto tempResults = locationTable.search(sub);
                        
                        if(!tempResults.empty()) results.insert(results.end(), tempResults.begin(), tempResults.end());
                    }
                    // Try a fallback adding " florida" for common cases
                    string testKey = input + " florida";
                    auto stateResults = locationTable.search(testKey);
                    if(!stateResults.empty())  results.insert(results.end(), stateResults.begin(), stateResults.end());
                }
                //Display results
                if(results.empty()){
                    
                    cout << "No restaurants found in " << userIn << endl;
                    searchResult.setString("No restaurants found in " + userIn);
                    
                }else{
                    
                    MaxHeap heap;
                    
                    for(const auto& result : results) heap.insert(result);
                    
                    const Restaurant top = heap.peekmax();
                    // Rating Info
                    ostringstream rating;
                    rating << fixed << setprecision(1) << top.getRating();
                    // Address Formatting
                    string formatAdd = top.getAddress();
                    replace(formatAdd.begin(), formatAdd.end(), ',', '\n');
                    const string dis = "Top-rated restaurant in " + userIn + ":\n\n" + "Name:\n " + top.getTitle() + "\n" + "Rating:\n " + rating.str() + " Stars\n"
                    + "\nLocation:\n " + formatAdd + "\n\n" + "Phone #:\n " + top.getPhone();
                    searchResult.setString(dis);
                    // Adjusting text placement + box size (exact match to FoodTypePage)
                    searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);
                    float textHeight = searchResult.getLocalBounds().height + 50.f;
                    resultBox.setSize(Vector2f(resultBox.getSize().x, textHeight));
                }
           }
        }
    }
    void draw(RenderWindow& window)const{
        
        window.draw(staticLayerSprite);
        window.draw(input);
        window.draw(searchTxt);
        //Cursor Info
        if(userIsTyping && const_cast<LocationPage*>(this)->cursorTimer.getElapsedTime().asSeconds() >= 0.5f){
            
            const_cast<LocationPage*>(this)->cursorTimer.restart();
            const_cast<LocationPage*>(this)->showCursor = !const_cast<LocationPage*>(this)->showCursor;
        }
        if(userIsTyping && showCursor) window.draw(textCursor);
        
        if(!searchResult.getString().isEmpty()){
            
            window.draw(resultBox);
            window.draw(searchResult);
        }
    }
    string getLocation()const{ return userIn; }
};
