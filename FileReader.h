#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileReader{
public:
  void Readandextract(vector<vector<string>>& data){
    
    for(int i = 1; i <= 10; i++){
            
            string filePath = "../dataset/380K_US_Restaurants_" + to_string(i) + ".csv";
            ifstream file(filePath);

            if(!file.is_open()){
                
                cerr << "Error opening " << filePath << endl;
                continue;
            }
            string line;
            getline(file, line); // skip header

            //total # of datapoints: 112,000
            for(int row = 0; row < 1600; row++){
                
                if(!getline(file, line)) break;

                istringstream stream(line);
                vector<string> currRow;
                string dataPoint;

                for(int col = 0; col < 7; col++){
                    
                    if(col == 6){
                        
                        getline(stream, dataPoint, '[');
                        
                        if (dataPoint.size() > 4) dataPoint = dataPoint.substr(1, dataPoint.size() - 4);
                            
                        else dataPoint = "";
                        
                    }else getline(stream, dataPoint, ',');
                
                    currRow.push_back(dataPoint);
                 }
                data.push_back(currRow);
             }
        }
  }
};
