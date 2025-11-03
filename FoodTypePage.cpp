//
// Created by evava on 11/3/2025.
//

#include "FoodTypePage.h"
#include <iostream>

FoodTypePage::FoodTypePage() {
    if (!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    //Title Info
    title.setFont(font);
    title.setString("Search by Food Type");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(40,40,40));
    title.setPosition(500.f - title.getLocalBounds().width / 2.f, 250.f);

    //Subtitle Info
    subtitle.setFont(font);
    subtitle.setString("Enter a cuisine or dish to explore nearby restaurants");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color(110,110,110));
    subtitle.setPosition(500.f - subtitle.getLocalBounds().width / 2.f, 310.f);

    //Input box Info
    in.setSize(sf::Vector2f(400.f, 55.f));
    in.setFillColor(sf::Color::White);
    in.setOutlineColor(sf::Color(180,180,180));
    in.setOutlineThickness(2);
    in.setPosition(260.f, 400.f);

    //Search Text Info
    searchTxt.setFont(font);
    searchTxt.setCharacterSize(22);
    searchTxt.setFillColor(sf::Color(40,40,40));
    searchTxt.setPosition(275.f, 410.f);

    //Cursor Info
    textCursor.setSize(sf::Vector2f(2.f, 30.f));
    textCursor.setFillColor(sf::Color(40,40,40));
    textCursor.setPosition(searchTxt.getPosition().x + 2.f, searchTxt.getPosition().y + 5.f);
    cursorTimer.restart();

    //Search Button Info
    searchButton.setSize(sf::Vector2f(140.f, 55.f));
    searchButton.setFillColor(sf::Color(230,230,230));
    searchButton.setOutlineColor(sf::Color(180,180,180));
    searchButton.setOutlineThickness(2);
    searchButton.setPosition(690.f, 400.f);

    extraTxt.setFont(font);
    extraTxt.setString("Enter");
    extraTxt.setCharacterSize(22);
    extraTxt.setFillColor(sf::Color(40, 40, 40));

    // --- Center text inside the button dynamically ---
    sf::FloatRect txtBounds = extraTxt.getLocalBounds();
    extraTxt.setOrigin(txtBounds.width / 2.f, txtBounds.height / 2.f + txtBounds.top);
    extraTxt.setPosition( searchButton.getPosition().x + searchButton.getSize().x / 2.f, searchButton.getPosition().y + searchButton.getSize().y / 2.f - 4.f // fine-tune vertical centering
    );


    //Icon Info
    if (iconTexture.loadFromFile("../assets/balanced-diet.png")) {
        iconTexture.setSmooth(true);
        icon.setTexture(iconTexture);
        icon.setScale(0.11f, 0.11f);
        icon.setPosition(205.f, 240.f);
    }
}

void FoodTypePage::Event(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        auto mouse = sf::Mouse::getPosition(window);

        if (in.getGlobalBounds().contains(mouse.x, mouse.y)) {
            userIsTyping = true;
            showCursor = true;
            cursorTimer.restart();
        } else {
            userIsTyping = false;
            showCursor = false;
        }

        if (searchButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            std::cout << "Searching for food type: " << userIn << std::endl;
        }
    }

    //Typing Logic
    if (userIsTyping && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !userIn.empty()) {
            userIn.pop_back();
        } else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            userIn += static_cast<char>(event.text.unicode);
        }

        searchTxt.setString(userIn);
        float textX = searchTxt.getPosition().x + searchTxt.getLocalBounds().width + 4.f;
        textCursor.setPosition(textX, searchTxt.getPosition().y +5.f);

        cursorTimer.restart();
        showCursor = true;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (!userIn.empty()) {
            std::cout << "Searching for food type: " << userIn << std::endl;
        }
    }
}

void FoodTypePage::draw(sf::RenderWindow& window) const {
    window.draw(title);
    window.draw(subtitle);
    window.draw(in);
    window.draw(searchButton);
    window.draw(searchTxt);
    window.draw(extraTxt);
    window.draw(icon);

    //Cursor Info
    if (userIsTyping && const_cast<FoodTypePage*>(this)->cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
        const_cast<FoodTypePage*>(this)->cursorTimer.restart();
        const_cast<FoodTypePage*>(this)->showCursor = !const_cast<FoodTypePage*>(this)->showCursor;
    }

    if (userIsTyping && showCursor) {
        window.draw(textCursor);
    }
}

