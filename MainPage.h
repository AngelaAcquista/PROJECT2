//
// Created by evava on 10/30/2025.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef MAINPAGE_H
#define MAINPAGE_H

using namespace sf;

class MainPage {
    Font font;
    Text title;
    Text message;
    Text subText;
    RectangleShape line;
    Text subtitle;

    //Buttons:
    RectangleShape buttons[3];
    Text buttonText[3];

    //Icon textures
    Texture iconTexture[3];
    Sprite icon[3];
public:
    MainPage();
    void draw(RenderWindow& window) const;
    bool isLocationClicked(Vector2f mousePos) const;
    bool isFoodTypeClicked(Vector2f mousePos) const;

};



#endif //MAINPAGE_H
