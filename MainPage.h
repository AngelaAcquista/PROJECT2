//
// Created by evava on 10/30/2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef MAINPAGE_H
#define MAINPAGE_H



class MainPage {
    sf::Font font;
    sf::Text title;
    sf::Text message;
    sf::Text subText;
    sf::RectangleShape line;
    sf::Text subtitle;

    //Buttons:
    sf::RectangleShape buttons[3];
    sf::Text buttonText[3];

    //Icon textures
    sf::Texture iconTexture[3];
    sf::Sprite icon[3];
public:
    MainPage();
    void draw(sf::RenderWindow& window) const;
    bool isLocationClicked(sf::Vector2f mousePos) const;
    bool isFoodTypeClicked(sf::Vector2f mousePos) const;

};



#endif //MAINPAGE_H
