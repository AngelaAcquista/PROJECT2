//
// Created by evava on 11/3/2025.
//

#ifndef RESTAURANTFINDER_FOODTYPEPAGE_H
#define RESTAURANTFINDER_FOODTYPEPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class FoodTypePage {
    sf::Font font;
    sf::Text title, subtitle;
    sf::Text searchTxt, extraTxt;
    sf::RectangleShape in, searchButton;
    sf::Sprite icon;
    sf::Texture iconTexture;

    //User typing info
    std::string userIn;
    bool userIsTyping = false;

    //Text Cursor
    sf::RectangleShape textCursor;
    sf::Clock cursorTimer;
    bool showCursor = false;

public:
    FoodTypePage();
    void Event(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
};


#endif //RESTAURANTFINDER_FOODTYPEPAGE_H