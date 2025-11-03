#include <SFML/Graphics.hpp>
#include "MainPage.h"
#include "LocationPage.h"
#include "FoodTypePage.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1100), "Restaurant Finder", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    //Different windows
    MainPage mainPage;
    LocationPage locationPage;
    FoodTypePage foodTypePage;

    //Controller
    std::string currPage = "Main";

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //Main Info
            if (currPage == "Main") {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                    if (mainPage.isLocationClicked(mousePos)) {
                        std::cout << "[MainPage] Location button clicked.\n";
                        currPage = "Location";
                    }
                    else if (mainPage.isFoodTypeClicked(mousePos)) {
                        std::cout << "[MainPage] Food Type button clicked.\n";
                        currPage = "Food";
                    }
                }
            }

            //Location Info
            else if (currPage == "Location") {
                locationPage.Event(event, window);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    std::cout << "[LocationPage] Returning to Main.\n";
                    currPage = "Main";
                }
            }

            //Food Type Info
            else if (currPage == "Food") {
                foodTypePage.Event(event, window);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    std::cout << "[FoodTypePage] Returning to Main.\n";
                    currPage = "Main";
                }
            }
        }

        //Drawing
        window.clear(sf::Color(250, 243, 232)); // soft beige

        if (currPage == "Main")
            mainPage.draw(window);
        else if (currPage == "Location")
            locationPage.draw(window);
        else if (currPage == "Food")
            foodTypePage.draw(window);

        window.display();
    }

    return 0;
}

