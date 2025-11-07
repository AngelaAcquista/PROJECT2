//
// Created by evava on 10/31/2025.
//
#ifndef LOCATIONPAGE_H
#define LOCATIONPAGE_H
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "MaxHeap.h"
#include "Hashtable.h"
#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace sf;
using namespace std;

class LocationPage {
    Font font;
    Text title, subtitle, inputFormat, options;
    RectangleShape input, searchButton, resultBox;
    Text searchTxt, buttonTxt, extraTxt;
    Text searchResult;
    Texture iconTexture;
    Sprite icon;

    //Text Cursor info
    RectangleShape textCursor;
    Clock cursorTimer;
    bool showCursor = false;

    //User info
    string userIn;
    bool userIsTyping = false;

    //Including the hashtable
    Hashtable locationTable;
    bool showResult = false;


public:
    LocationPage();
    void loadData(); //loading the city/state
    void Event(const sf::Event& event, const RenderWindow& window);
    void draw(RenderWindow& window) const;
    string getLocation() const {
        return userIn;
    };
};



#endif //LOCATIONPAGE_H
