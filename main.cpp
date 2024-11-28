#include <iostream>
#include "readandmap.h"
#include "song_object.h"


int main() {
    readandmap hi;
    //stores all song objects
    vector<SongObject> song_containter;

    vector<vector<string>>data = hi.ReadFile("dataset.csv", song_containter);
//    for(int i = 0; i< data.size(); i++){
//        for (int j = 0; j< data[i].size(); j++){
//            cout<<data[i][j]<< " ";
//        }
//        cout<<endl;
//    }
}
