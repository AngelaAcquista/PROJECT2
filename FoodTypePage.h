//
// Created by evava on 11/3/2025.
//

#ifndef RESTAURANTFINDER_FOODTYPEPAGE_H
#define RESTAURANTFINDER_FOODTYPEPAGE_H

#pragma once
#include "Hashtable.h"
#include <SFML/Graphics.hpp>
#include <string>


class FoodTypePage {
    sf::Font font;
    sf::Text title, subtitle;
    sf::Text searchTxt, extraTxt;
    sf::RectangleShape in, searchButton, resultBox;
    sf::Sprite icon;
    sf::Texture iconTexture;
    sf::Text searchResult;

    //User typing info
    std::string userIn;
    bool userIsTyping = false;

    //Text Cursor
    sf::RectangleShape textCursor;
    sf::Clock cursorTimer;
    bool showCursor = false;

    Hashtable restaurantTable;
    void loadData(); //helper func

public:
    FoodTypePage();
    void Event(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
};


#endif //RESTAURANTFINDER_FOODTYPEPAGE_H