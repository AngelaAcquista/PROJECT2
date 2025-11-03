//
// Created by evava on 10/31/2025.
//

#ifndef LOCATIONPAGE_H
#define LOCATIONPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class LocationPage {
    sf::Font font;
    sf::Text title, subtitle, options;
    sf::RectangleShape input, searchButton;
    sf::Text searchTxt, buttonTxt, extraTxt;
    sf::Texture iconTexture;
    sf::Sprite icon;

    //Text Cursor info
    sf::RectangleShape textCursor;
    sf::Clock cursorTimer;
    bool showCursor = false;

    //User info
    std::string userIn;
    bool userIsTyping = false;

public:
    LocationPage();
    void Event(const sf::Event& event, const sf::RenderWindow& window);

    void draw(sf::RenderWindow& window) const;
    std::string getLocation() const {
        return userIn;
    };
};



#endif //LOCATION_H
