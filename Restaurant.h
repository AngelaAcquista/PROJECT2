#pragma once
#include <string>

using namespace std;

class Restaurant{
    private:
        string title;
        string phone;
        float rating;
        string address;

    public:

        Restaurant() : title(""), phone(""), rating(0.0f), address("") {}

        Restaurant(const string& title, const string& phone, const float& rating, const string& address){
            
            this->title = title;
            this->phone = phone;
            this->rating = rating;
            this->address = address;
        }

        string getTitle()const{ return title; }

        string getPhone()const{ return phone; }

        float getRating()const{ return rating; }

        string getAddress()const{ return address; }

        bool operator>(const Restaurant& other)const{
            
            return this->rating > other.rating; 
        }
};
