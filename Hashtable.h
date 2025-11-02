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
        int numBuckets;
        float loadFactor;
        float maxLoadFactor = 0.75;
        bool searchSuccess = false;

        void rehash() {
            vector<list<pair<string, vector<Restaurant>>>> oldTable = table;
            //add more slots to the hashtable
            vector<list<pair<string, vector<Restaurant>>>> updatedTable;
            updatedTable.resize(numBuckets * 2);

            table = updatedTable;
            //recalculate table size and load factor
            updateTableSize(numBuckets * 2);
            updateLoadFactor();

            //hash all existing keys in the old hashtable
           for (auto &currList: oldTable) {
               for (auto &pair: currList) {
                   int newIndex = hash(pair.first);
                   table[newIndex].push_back(pair);
               }
           }

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
        Hashtable() {
            //initialize the hashtable with default values
            table.resize(80009);
            this->numEntries = 0;
            this->numBuckets = int(table.size());
            this->loadFactor =  float(numEntries)/float(table.size());
        }

        void updateLoadFactor() {
                this->loadFactor = float(numEntries) / float(table.size());
        }

        float getLoadFactor() {
                return this->loadFactor;
        }

        void updateTableSize(int numSlots) {
                this->numBuckets = numSlots;
        }

        int getNumBuckets() {
                return numBuckets;
        }

        bool getSearchSuccess() {
            return this->searchSuccess;
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
                    bool keyFound = false;
                    for (auto &pair: table[hashIndex]) {
                            if (pair.first == key) {
                                pair.second.push_back(obj);
                                keyFound = true;
                            }
                    }
                    //for collision handling
                    if (keyFound == false) {
                        vector<Restaurant> vec = {obj};
                        pair<string, vector<Restaurant>> keyValue(key, vec);
                        table[hashIndex].push_back(keyValue);
                    }
                }
            updateLoadFactor();
            //rehash the table if necessary
            if (loadFactor >= maxLoadFactor) {
                rehash();
            }

        }

        vector<Restaurant>& search(const string& key){
            //searches for the list of restaurants based on food category
            //and location


        }

        void makeEmpty() {
            //deletes all entries in the hashtable
            for (int i = 0; i < table.size(); i++) {
                table[i].clear();
            }
            table.resize(80009);
            this->numEntries = 0;
            this->loadFactor =  float(numEntries)/float(table.size());
        }


};
