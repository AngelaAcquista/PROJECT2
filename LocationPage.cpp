#include "LocationPage.h"
#include "MaxHeap.h"
#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

LocationPage::LocationPage() {
    if (!font.loadFromFile("../assets/MomoTrustDisplay-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    //Title Info
    title.setFont(font);
    title.setString("Search by Location");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color(40,40,40));
    title.setPosition(500.f - title.getLocalBounds().width / 2.f, 250.f);

    //Subtitle Info
    subtitle.setFont(font);
    subtitle.setString("Enter a city and state to explore nearby restaurants");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color(110,110,110));
    subtitle.setPosition(500.f - subtitle.getLocalBounds().width / 2.f, 310.f);

    //Results Info
    searchResult.setFont(font);
    searchResult.setCharacterSize(22);
    searchResult.setFillColor(sf::Color(40,40,40));
    searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);

    //Box for result Info (same as FoodTypePage)
    resultBox.setSize(sf::Vector2f(520.f, 130.f));
    resultBox.setFillColor(sf::Color(255,255,255, 230));
    resultBox.setOutlineColor(sf::Color(200,200,200));
    resultBox.setOutlineThickness(2);
    resultBox.setPosition(240.f, 520.f);

    //Input box Info
    input.setSize(sf::Vector2f(400.f, 55.f));
    input.setFillColor(sf::Color::White);
    input.setOutlineColor(sf::Color(180,180,180));
    input.setOutlineThickness(2);
    input.setPosition(260.f, 400.f);

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
    extraTxt.setPosition(
        searchButton.getPosition().x + searchButton.getSize().x / 2.f,
        searchButton.getPosition().y + searchButton.getSize().y / 2.f - 4.f
    );

    //Icon Info
    if (iconTexture.loadFromFile("../assets/pin.png")) {
        iconTexture.setSmooth(true);
        icon.setTexture(iconTexture);
        icon.setScale(0.09f, 0.09f);
        icon.setPosition(205.f, 240.f);
    }

    //Load restaurant data
    loadData();
}

void LocationPage::loadData() {
    std::vector<std::vector<std::string>> restaurantData;

    for (int i = 1; i <= 15; i++) {
        std::string filePath = "../dataset/380K_US_Restaurants_" + std::to_string(i) + ".csv";
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error opening " << filePath << std::endl;
            continue;
        }

        std::string line;
        getline(file, line); // skip header

        for (int row = 0; row < 10; row++) { // just a few for testing
            if (!getline(file, line)) break;

            std::istringstream stream(line);
            std::vector<std::string> currRow;
            std::string dataPoint;

            for (int col = 0; col < 7; col++) {
                if (col == 6) {
                    getline(stream, dataPoint, '[');
                    if (dataPoint.size() > 4)
                        dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                    else
                        dataPoint = "";
                } else {
                    getline(stream, dataPoint, ',');
                }
                currRow.push_back(dataPoint);
            }
            restaurantData.push_back(currRow);
        }
    }

    // 🔹 Insert into hashtable
    for (auto &row : restaurantData) {
        if (row.size() < 7) continue;

        std::string title = row[0];
        std::string city = row[1];
        std::string state = row[4];
        std::string key = city + " " + state;

        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        while (!key.empty() && (key.back() == ',' || key.back() == ' '))
            key.pop_back();

        float rating = 0.0f;
        try {
            if (!row[3].empty()) rating = stof(row[3]);
        } catch (...) { rating = 0.0f; }

        std::string phone = row[5];
        std::string address = row[6];

        Restaurant r(title, phone, rating, address);
        locationTable.insert(key, r);
    }

    std::cout << "Location hashtable loaded successfully.\n";
}

void LocationPage::Event(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        auto mouse = sf::Mouse::getPosition(window);

        if (input.getGlobalBounds().contains(mouse.x, mouse.y)) {
            userIsTyping = true;
            showCursor = true;
            cursorTimer.restart();
        } else {
            userIsTyping = false;
            showCursor = false;
        }

        if (searchButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            std::cout << "Searching for location: " << userIn << std::endl;
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
        std::cout << "Searching for location: " << userIn << std::endl;

        std::string input = userIn;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        // 🔹 First, try exact match
        std::vector<Restaurant> results = locationTable.search(input);

        // 🔹 If not found, try partial substring matches
        if (results.empty()) {
            std::vector<std::string> testInputs;

            //shorter substring to prevent out of range
            for (size_t i = input.size(); i > 3; --i) {
                testInputs.push_back(input.substr(0, i));
            }


            for (const auto& sub : testInputs) {
                auto tempResults = locationTable.search(sub);
                if (!tempResults.empty()) {
                    results.insert(results.end(), tempResults.begin(), tempResults.end());
                }
            }

            // Try a fallback adding " florida" for common cases
            std::string testKey = input + " florida";
            auto stateResults = locationTable.search(testKey);
            if (!stateResults.empty())
                results.insert(results.end(), stateResults.begin(), stateResults.end());
        }

        //Display results
        if (results.empty()) {
            std::cout << "No restaurants found in " << userIn << std::endl;
            searchResult.setString("No restaurants found in " + userIn);
        } else {
            MaxHeap heap;
            heap.insert(results);
            const Restaurant top = heap.highestratedrestaurant();

            // Rating Info
            std::ostringstream rating;
            rating << std::fixed << std::setprecision(1) << top.getRating();

            // Address Formatting
            std::string formatAdd = top.getAddress();
            std::replace(formatAdd.begin(), formatAdd.end(), ',', '\n');

            const std::string dis =
                "Top-rated restaurant in " + userIn + ":\n\n"
                + "Name:\n " + top.getTitle() + "\n"
                + "Rating:\n " + rating.str() + " Stars\n"
                + "\nLocation:\n " + formatAdd
                + "\n\n" + "Phone #:\n " + top.getPhone();

            searchResult.setString(dis);

            // Adjusting text placement + box size (exact match to FoodTypePage)
            searchResult.setPosition(resultBox.getPosition().x + 15.f, resultBox.getPosition().y + 20.f);
            float textHeight = searchResult.getLocalBounds().height + 50.f;
            resultBox.setSize(sf::Vector2f(resultBox.getSize().x, textHeight));
        }
       }
    }
}

void LocationPage::draw(sf::RenderWindow& window) const {
    window.draw(title);
    window.draw(subtitle);
    window.draw(input);
    window.draw(searchButton);
    window.draw(searchTxt);
    window.draw(extraTxt);
    window.draw(icon);

    //Cursor Info
    if (userIsTyping && const_cast<LocationPage*>(this)->cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
        const_cast<LocationPage*>(this)->cursorTimer.restart();
        const_cast<LocationPage*>(this)->showCursor = !const_cast<LocationPage*>(this)->showCursor;
    }

    if (userIsTyping && showCursor) {
        window.draw(textCursor);
    }

    if (!searchResult.getString().isEmpty()) {
        window.draw(resultBox);
        window.draw(searchResult);
    }
}

