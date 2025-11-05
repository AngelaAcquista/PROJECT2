//
// Created by evava on 10/31/2025.
//

#ifndef LOCATIONPAGE_H
#define LOCATIONPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Hashtable.h"
#include "Restaurant.h"

class LocationPage {
    sf::Font font;
    sf::Text title, subtitle, options;
    sf::RectangleShape input, searchButton, resultBox;
    sf::Text searchTxt, buttonTxt, extraTxt;
    sf::Text searchResult;
    sf::Texture iconTexture;
    sf::Sprite icon;

    //Text Cursor info
    sf::RectangleShape textCursor;
    sf::Clock cursorTimer;
    bool showCursor = false;

    //User info
    std::string userIn;
    bool userIsTyping = false;

    //Including the hashtable
    Hashtable locationTable;
    bool showResult = false;


public:
    LocationPage();
    void loadData(); //loading the city/state
    void Event(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    std::string getLocation() const {
        return userIn;
    };
};



#endif //LOCATIONPAGE_H
