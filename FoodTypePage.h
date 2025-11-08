#pragma once
#include "Hashtable.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "MaxHeap.h"
#include "Restaurant.h"
#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <format>
#include <chrono>

using namespace std;
using namespace sf;
using namespace std::chrono;

class FoodTypePage{
    
    Font font;
    Text title, subtitle, maxheap, hashtable, searchTxt, searchResult;
    RectangleShape in, resultBox;
    Sprite icon, staticLayerSprite;
    RenderTexture staticLayer;
    Texture iconTexture;
    string userIn;
    bool userIsTyping = false, showCursor = false;
    RectangleShape textCursor;
    Clock cursorTimer;
    Hashtable restaurantTable;

    void loadData(){
        FileReader filereader;
        vector<vector<string>> restaurantData;
        filereader.ReadFile(restaurantData);
        // Insert into hashtable
        for(auto &row : restaurantData){
            
            if(row.size() < 7) continue;

            string title = row[0], category = row[2];

            transform(category.begin(), category.end(), category.begin(), ::tolower);
            size_t findComma = category.find(',');
            
            if(findComma != string::npos) category = category.substr(0, findComma);
            
            size_t findSpace = category.find(' ');
            
            if(findSpace != string::npos) category = category.substr(0, findSpace);

            float rating = 0.0f;
        
            try{
                
                if (!row[3].empty()) rating = stof(row[3]);
            }
            catch(const invalid_argument& e){
                
                rating = 0.0f;
            }
            catch(const out_of_range& e){
                
                rating = 0.0f; 
            }
            string phone = row[5], address = row[6];

            Restaurant r(title, phone, rating, address);
            string key = category; // Key = food type
            restaurantTable.insert(key, r);
        }

        //cout << "Hashtable loaded successfully."<<endl;
    }
    public:

        FoodTypePage(){
            
            if(!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) cerr << "Error loading font" << std::endl;
            //Title Info
            title.setFont(font);
            title.setString("Search by Food Type");
            title.setCharacterSize(42);
            title.setFillColor(Color(40,40,40));
            title.setPosition(500.f - title.getLocalBounds().width / 2.f, 250.f);
            //Subtitle Info
            subtitle.setFont(font);
            subtitle.setString("Enter a cuisine or dish to explore nearby restaurants");
            subtitle.setCharacterSize(24);
            subtitle.setFillColor(Color(110,110,110));
            subtitle.setPosition(500.f - subtitle.getLocalBounds().width / 2.f, 310.f);
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
            maxheap.setPosition(600.f, 1025.f);
            //Results Info
            searchResult.setFont(font);
            searchResult.setCharacterSize(22);
            searchResult.setFillColor(Color(40,40,40));
            searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);
            //Box for result Info
            resultBox.setSize(Vector2f(580.f, 130.f));
            resultBox.setFillColor(Color(255,255,255, 230));
            resultBox.setOutlineColor(Color(200,200,200));
            resultBox.setOutlineThickness(2);
            resultBox.setPosition(200.f, 520.f);
            //Input box Info
            in.setSize(Vector2f(400.f, 55.f));
            in.setFillColor(Color::White);
            in.setOutlineColor(Color(180,180,180));
            in.setOutlineThickness(2);
            in.setPosition(260.f, 400.f);
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
            
            //Icon Info
            if(iconTexture.loadFromFile("../assets/balanced-diet.png")){
                
                iconTexture.setSmooth(true);
                icon.setTexture(iconTexture);
                icon.setScale(0.11f, 0.11f);
                icon.setPosition(205.f, 240.f);
            }
            staticLayer.create(1000.f, 1100.f);
            staticLayer.clear(Color::Transparent); 
            staticLayer.draw(title);
            staticLayer.draw(subtitle);
            staticLayer.draw(icon);
            staticLayer.display();
            staticLayerSprite.setTexture(staticLayer.getTexture());
            //Loading restaurant data into Hash
            loadData();
        }
        void Event(const Event& event, const RenderWindow& window){
            
            if(event.type == Event::MouseButtonPressed){
                
                auto mouse = Mouse::getPosition(window);

                if(in.getGlobalBounds().contains(mouse.x, mouse.y)){
                    
                    userIsTyping = true;
                    showCursor = true;
                    cursorTimer.restart();
                    
                }else{
                    
                    userIsTyping = false;
                    showCursor = false;
                }
            }
            //Typing Logic
            if(userIsTyping && event.type == Event::TextEntered){
                
                if(event.text.unicode == 8 && !userIn.empty()){
                    
                    userIn.pop_back();
                    
                }else if(event.text.unicode >= 32 && event.text.unicode < 128){
                    
                    userIn += static_cast<char>(event.text.unicode);
                }
                searchTxt.setString(userIn);
                float textX = searchTxt.getPosition().x + searchTxt.getLocalBounds().width + 4.f;
                textCursor.setPosition(textX, searchTxt.getPosition().y +5.f);
                cursorTimer.restart();
                showCursor = true;
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){

                //if(event.type == Event::KeyPressed) cout << "Key pressed: " << event.key.code << endl;

                if(!userIn.empty()){
                    
                    //cout << "Searching for food type: " << userIn << endl;
                    string input = userIn;
                    transform(input.begin(), input.end(), input.begin(), ::tolower);
                    size_t inSpace = input.find(' ');
                    
                    if (inSpace != std::string::npos) input = input.substr(0, inSpace);

                    auto results = restaurantTable.search(input);

                    if (results.empty()){
                        
                        //cout << "No restaurants found for " << userIn << endl;
                        searchResult.setString("No restaurants found for " + userIn);
                        
                    }else{
                        auto hashTableStart = high_resolution_clock::now();
                        Restaurant hashtableTop = results[0];
                        for (const auto& r: results) {
                            if (r.getRating() > hashtableTop.getRating()) {
                                hashtableTop = r;
                            }
                        }

                        //timer logic gotten from stack overflow: https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
                        auto hashTableEnd = high_resolution_clock::now();
                        duration<double, std::milli> hashTableTime = hashTableEnd - hashTableStart;
                        
                        MaxHeap heap;
                        
                        for(const auto& result : results) heap.insert(result);

                        auto maxHeapStart = high_resolution_clock::now();
                        const Restaurant top = heap.peekmax();
                        auto maxHeapEnd = high_resolution_clock::now();
                        duration<double, std::milli> maxHeapTime = maxHeapEnd - maxHeapStart;

                        hashtable.setString("Hashtable: " + to_string(hashTableTime.count()) + " ms");
                        maxheap.setString("Max-heap: " + to_string(maxHeapTime.count()) + " ms");

                        //Rating Info
                        ostringstream rating;
                        rating << fixed << setprecision(1) << top.getRating();
                        //Address Info
                        string formatAdd = top.getAddress();
                        replace(formatAdd.begin(), formatAdd.end(), ',', '\n');
                        const string dis = "Top-rated " + userIn + " restaurant:\n\n" + "Name:\n " + top.getTitle() + "\n" + "Rating:\n " + rating.str() + " Stars\n" + "\nLocation:\n " + formatAdd
                                        + "\n\n" + "Phone #:\n " + top.getPhone();
                        searchResult.setString(dis);
                        //Adjusting text placement + box size
                        searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);
                        float textHeight = searchResult.getLocalBounds().height + 50.f;
                        resultBox.setSize(Vector2f(resultBox.getSize().x, textHeight));
                    }
                }
            }
        }
        void draw(RenderWindow& window)const{

            window.draw(staticLayerSprite);
            window.draw(in);
            window.draw(searchTxt);
            //Cursor Info
            if(userIsTyping && const_cast<FoodTypePage*>(this)->cursorTimer.getElapsedTime().asSeconds() >= 0.5f){
                
                const_cast<FoodTypePage*>(this)->cursorTimer.restart();
                const_cast<FoodTypePage*>(this)->showCursor = !const_cast<FoodTypePage*>(this)->showCursor;
            }
            if(userIsTyping && showCursor) window.draw(textCursor);
            
            if(!searchResult.getString().isEmpty()){
                window.draw(resultBox);
                window.draw(searchResult);
            }
            window.draw(hashtable);
            window.draw(maxheap);
        }
};
