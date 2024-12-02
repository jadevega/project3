#include <map>
using namespace std;
#include<iomanip>
#include <string>
#include<vector>
#include <iostream>
#include "song_object.h"

using namespace std;

#ifndef UNTITLED1_READANDMAP_H
#define UNTITLED1_READANDMAP_H


class readandmap {

private:
    unordered_map<string, vector<string>> data;
    vector<vector<string>>data1;


public:
    vector<vector<string>> ReadFile(string filename);
    unordered_map<string,vector<string>>AddtoMapHappy();
    unordered_map<string, vector<string>>AddtoMapSad();
    unordered_map<string, vector<string>>AddtoMapRelaxed();
    unordered_map<string, vector<string>>AddtoMapEnergetic();
};


#endif //UNTITLED1_READANDMAP_H
