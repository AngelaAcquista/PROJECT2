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
using namespace std;

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
    MainPage(){
        const float windowWidth = 1000.f;
        const float windowHeight = 1100.f;
        const float centerX = windowWidth / 2.f;

        // Load font
        if (!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) {
            cerr << "Error loading font" << endl;
        }
        // --- Header (top-left corner) ---
        title.setFont(font);
        title.setString("Restaurant Scout");
        title.setCharacterSize(18);
        title.setFillColor(Color(40, 40, 40));
        title.setPosition(40.f, 30.f);

        // --- Underline under title ---
        FloatRect titleBounds = title.getGlobalBounds();
        line.setSize(Vector2f(titleBounds.width, 2));
        line.setFillColor(Color(40, 40, 40));
        line.setPosition(titleBounds.left, titleBounds.top + titleBounds.height + 5);

        // --- Main heading (centered) ---
        message.setFont(font);
        message.setString("Discover restaurants your way");
        message.setCharacterSize(46);
        message.setFillColor(Color(40, 40, 40));
        FloatRect messageBounds = message.getLocalBounds();
        message.setOrigin(messageBounds.width / 2.f, 0);

        // --- Group vertical alignment ---
        float groupOffsetY = windowHeight / 2.f - 300.f;
        message.setPosition(centerX, groupOffsetY);

        // --- Subtitle ---
        subText.setFont(font);
        subText.setString("Choose how you would like to explore");
        subText.setCharacterSize(26);
        subText.setFillColor(Color(110, 110, 110));
        FloatRect subBounds = subText.getLocalBounds();
        subText.setOrigin(subBounds.width / 2.f, 0);
        subText.setPosition(centerX, groupOffsetY + messageBounds.height + 18.f);

        // --- Buttons ---
        string options[3] = {"Location", "Food Type"};
        string icons[3] = {"../assets/pin.png", "../assets/balanced-diet.png",};

        float startY = groupOffsetY + 140.f;
        float buttonWidth = 320.f;
        float buttonHeight = 75.f;

        for (int i = 0; i < 2; i++) {
            // Button rectangle
            buttons[i].setSize(Vector2f(buttonWidth, buttonHeight));
            buttons[i].setFillColor(Color::White);
            buttons[i].setOutlineColor(Color(180, 180, 180));
            buttons[i].setOutlineThickness(2);

            float buttonX = centerX - buttonWidth / 2.f;
            float buttonY = startY + i * 100.f;
            buttons[i].setPosition(buttonX, buttonY);

            // Icon
            if (!iconTexture[i].loadFromFile(icons[i])) {
                cerr << "Error loading icon: " << icons[i] << std::endl;
            }
            iconTexture[i].setSmooth(true);
            icon[i].setTexture(iconTexture[i]);
            icon[i].setScale(0.1f, 0.1f);
            icon[i].setPosition(buttonX + 25.f, buttonY + 8.f);

            // Button text
            buttonText[i].setFont(font);
            buttonText[i].setString(options[i]);
            buttonText[i].setCharacterSize(22);
            buttonText[i].setFillColor(Color(40, 40, 40));
            buttonText[i].setPosition(buttonX + 110.f, buttonY + 22.f);
        }
    }
    void draw(RenderWindow& window) const{
        window.draw(title);
        window.draw(line);
        window.draw(message);
        window.draw(subText);

        for (int i = 0; i < 3; i++) {
            window.draw(buttons[i]);
            window.draw(icon[i]);
            window.draw(buttonText[i]);
        }
    }
    bool isLocationClicked(Vector2f mousePos) const{
        return buttons[0].getGlobalBounds().contains(mousePos);
    }
    bool isFoodTypeClicked(Vector2f mousePos) const{
        return buttons[1].getGlobalBounds().contains(mousePos);
    }

};

#endif //MAINPAGE_H
