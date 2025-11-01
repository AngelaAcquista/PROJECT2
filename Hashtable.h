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
        float maxLoadFactor = 0.75;

        void rehash() {
            //add more slots to the hashtable
            table.resize(table.size() * 2);



            //recalculate the load factor
            updateLoadFactor();


        }
        int hash(const string& key) {
            /*performs the hashing operation on the string and
            *returns the associated index
            */
            int hashValue = 0;
            for (int i = 0; i < key.length(); i++) {
                hashValue = hashValue * 227 + key[i];
            }
            return hashValue % table.size();
        }

    public:
        void updateLoadFactor() {
            this->loadFactor = numEntries / table.size();
        }

        float getLoadFactor() {
            return this->loadFactor;
        }
        Hashtable() {
            //initialize the hashtable with default values
            table.resize(80009);
            this->numEntries = 0;
            this->loadFactor =  numEntries/(table.size());
        }

        void insert(const string& key, Restaurant& obj) {
                int hashIndex = hash(key);
                numEntries += 1;

                if (table[hashIndex].empty()) {
                    vector<Restaurant> vec = {obj};
                    pair<string, vector<Restaurant>> keyValue(key, vec);
                    table[hashIndex].push_back(keyValue);
                }
                else {
                   for each (pair<string, vector<Restaurant>> &item in table[hashIndex]) {
                      if (item.first == key) {
                        item.second.push_back(obj);
                      }
                   }
                }
            updateLoadFactor();
            //rehash the table if necessary
            if (loadFactor >= maxLoadFactor) {
                rehash();
            }

        }

        bool search(const string& key) {


        }


        void makeEmpty() {
            //deletes all entries in the hashtable
            for (int i = 0; i < table.size(); i++) {
                table[i].clear();
            }
            table.resize(80009);
            this->numEntries = 0;
            this->loadFactor =  numEntries/(table.size());
        }


};
