#pragma once
#include <vector>
#include <list>
#include <string>
#include "Restaurant.h"
using namespace std;

//hashtable class structure was gotten from provided textbook: Data Structures and Algorithm Analysis in C++
class Hashtable {
    private:
        //key: [category: City, State]
        //value: a vector of restaurant objects: <restaurant name (title), phone, rating, address>
        //each bucket will hash to key-value pairs
        vector<list<pair<string, vector<Restaurant>>>> table;
        int numEntries;
        float loadFactor;

        void rehash() {

        }
        size_t hash(const string& key) {
            return 0;
        }

    public:
        Hashtable() {
            //initialize the hashtable with default values
            table.resize(50000);
            this->numEntries = 0;
            this->loadFactor =  numEntries/(table.size());
        }

        void insert(const string& key, Restaurant& obj) {

        }

        bool search(const string& key) {
            return false;
        }

        void makeEmpty() {
            //deletes all entries in the hashtable
            for (int i = 0; i < table.size(); i++) {
                table[i].clear();
            }
            table.resize(50000);
            this->numEntries = 0;
            this->loadFactor =  numEntries/(table.size());
        }



};
