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
    vector<vector<string>> data;
        map<string,vector<string>>upbeatenergy;
        map<string,vector<string>>sadsongs;
        map<string, vector<string>>happysongs;
        map<string, vector<string>> chill;

public:
    vector<vector<string>> ReadFile(string filename, vector<SongObject>& song_objects);
    map<float,vector<string>>AddtoMap();
};


#endif //UNTITLED1_READANDMAP_H
