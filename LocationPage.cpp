//
// Created by evava on 10/31/2025.
//

#include "LocationPage.h"
#include <iostream>

LocationPage::LocationPage() {
    if (!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    //Title
    title.setFont(font);
    title.setString("Search by Location");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(40, 40, 40));

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.f, 0);
    title.setPosition(500.f, 250.f);

    //Subtitle
    subtitle.setFont(font);
    subtitle.setString("Enter your state and city to explore restaurants near you");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color(110, 110, 110));

    sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setOrigin(subtitleBounds.width / 2.f, 0);
    subtitle.setPosition(500.f, 310.f);

     //Input box
    input.setSize(sf::Vector2f(400.f, 55.f));
    input.setFillColor(sf::Color::White);
    input.setOutlineColor(sf::Color(180, 180, 180));
    input.setOutlineThickness(2);
    input.setPosition(300.f, 380.f);

    //Search text (user input)
    searchTxt.setFont(font);
    searchTxt.setCharacterSize(22);
    searchTxt.setFillColor(sf::Color(40,40,40));
    searchTxt.setPosition(315.f, 390.f);

    //Cursor Info
    textCursor.setSize(sf::Vector2f(2.f, 30.f));
    textCursor.setFillColor(sf::Color(40, 40, 40));
    textCursor.setPosition(searchTxt.getPosition().x + 2.f, searchTxt.getPosition().y + 5.f);
    cursorTimer.restart();


    //Search button
    searchButton.setSize(sf::Vector2f(140.f, 55.f));
    searchButton.setFillColor(sf::Color(230, 230, 230));
    searchButton.setOutlineColor(sf::Color(180, 180, 180));
    searchButton.setOutlineThickness(2);
    searchButton.setPosition(720.f, 380.f);

    //Button Text ("Enter")
    extraTxt.setFont(font);
    extraTxt.setString("Enter");
    extraTxt.setCharacterSize(22);
    extraTxt.setFillColor(sf::Color(40, 40, 40));

    //Center text inside the search button
    sf::FloatRect txtBounds = extraTxt.getLocalBounds();
    extraTxt.setOrigin(txtBounds.width / 2.f, txtBounds.height / 2.f);
    extraTxt.setPosition(
        searchButton.getPosition().x + searchButton.getSize().x / 2.f,
        searchButton.getPosition().y + searchButton.getSize().y / 2.f - 4.f // adjust for vertical alignment
    );


    buttonTxt.setFont(font);
    buttonTxt.setString("Search");
    buttonTxt.setCharacterSize(22);
    buttonTxt.setFillColor(sf::Color(40, 40, 40));
    buttonTxt.setPosition(750.f, 390.f);

    //icon
    if (iconTexture.loadFromFile("../assets/pin.png")) {
        iconTexture.setSmooth(true);
        icon.setTexture(iconTexture);
        icon.setScale(0.08f, 0.08f);
        icon.setPosition(250.f, 380.f);
    }
}

void LocationPage::Event(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        auto mouse = sf::Mouse::getPosition(window);

        if (input.getGlobalBounds().contains(mouse.x, mouse.y)) {
            userIsTyping = true;
            showCursor = true;
            cursorTimer.restart();
        }
        else {
            userIsTyping = false;
            showCursor = false;
        }

        //checking if the enter button is clicked (debugging)
        if (searchButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            std::cout << "Searching for restaurants in: " << userIn << std::endl;
        }
    }

    //Handling the typing logic
    if (userIsTyping && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !userIn.empty()) { // backspace
            userIn.pop_back();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) { // printable characters
            userIn += static_cast<char>(event.text.unicode);
        }
        //Updating the text display
        searchTxt.setString(userIn);

        //Move the cursor with the text
        float textMove = searchTxt.getPosition().x + searchTxt.getLocalBounds().width + 4.f;
        textCursor.setPosition(textMove, searchTxt.getPosition().y + 5.f);

        cursorTimer.restart();
        showCursor = true;
    }

    //Handling the Enter
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (!userIn.empty()) {
            std::cout << "Searching for restaurants in: " << userIn << std::endl;
        }
    }
}

void LocationPage::draw(sf::RenderWindow& window) const {
    window.draw(title);
    window.draw(subtitle);
    window.draw(input);
    window.draw(searchTxt);
    window.draw(buttonTxt);
    window.draw(searchButton);
    window.draw(icon);
    window.draw(extraTxt);

    //Text cursor info:
    if (userIsTyping && const_cast<LocationPage*>(this)->cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
        const_cast<LocationPage*>(this)->cursorTimer.restart();
        const_cast<LocationPage*>(this)->showCursor = !const_cast<LocationPage*>(this)->showCursor;
    }
    if (userIsTyping && showCursor) {
        window.draw(textCursor);
    }

}
