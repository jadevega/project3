#include <map>
#include <string>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "readandmap.h"
#include "song_object.h"

using namespace std;

vector<vector<string>>readandmap::ReadFile(string filename, vector<SongObject>& song_objects ){
    vector<vector<string>>data;
    ifstream file(filename);
    if(file.is_open()){
        cout<<"you opened it bb"<<endl;
       string line;
       while(getline(file, line)){

           string tracknum;
           string trackid, artists, album_name, trackname, popularity, duration, explicitlyrics,
           dance, energy, key, loudness, mode, speechniess, accousticness, instrumentallness, liveness,
           valence, tempo, timesignature, track_genre;

           stringstream ss(line);
           string current;
           int count = 0;
           while(getline(ss, current, ',')) {
               if (count == 2 or count == 3 or count == 4) {
                   if (current.front() == '"') {
                       current = current.substr(1);
                       string next;
                       while (getline(ss, next, ',')) {
                           current += "," + next;
                           if (next.back() == '"') {
                               current = current.substr(0, current.size() - 1);
                               break;
                           }
                       }
                   }

               }
               if (count == 0){
                   tracknum = current;
               }
               else if(count == 1){
                   trackid = current;
               }
               else if(count == 2){
                   artists = current;
               }
               else if(count == 3){
                   album_name = current;
               }
               else if(count == 4){
                   trackname = current;
               }
               else if(count == 5){
                   popularity = current;
               }
               else if (count == 6){
                   duration = current;
               }
               else if(count == 7){
                   explicitlyrics = current;
               }
               else if(count == 8){
                   dance = current;
               }
               else if(count == 9){
                   energy = current;
               }
               else if(count == 10){
                   key = current;
               }
               else if(count == 11){
                   loudness = current;
               }
               else if (count == 12){
                   mode = current;
               }
               else if(count == 13){
                  speechniess= current;
               }
               else if(count == 14){
                   accousticness = current;
               }
               else if(count == 15){
                   instrumentallness = current;
               }
               else if(count == 16){
                   liveness = current;
               }
               else if(count == 17){
                  valence = current;
               }
               else if(count == 18){
                   tempo = current;
               }
               else if(count == 19){
                   timesignature = current;
               }
               else if(count == 20){
                   track_genre = current;
               }
               count++;
           }
           vector<string>specificinfo = {artists, trackname, dance, energy, accousticness, liveness};
           data.push_back(specificinfo);
       }

       file.close();
    }
    else{
        cout<<"Error"<<endl;
    }
    return data;
};

map<float,vector<string>>readandmap::AddtoMap(){
    float danceability = 0;
    for(auto row: data) {
        try {
            float danceability = stof(row[2]);
            if (danceability > 0.8) {
                if (upbeatenergy.find(row[1]) == upbeatenergy.end()) {
                    upbeatenergy[row[1]] = row;
                }
            }
        }
        catch (invalid_argument) {
            cout << "not an interger"<<endl;
        }

        try{
            float energyflo = stof(row[3]);
            if(energyflo > 0.8){
                if(happysongs.find(row[1]) == happysongs.end()){
                    happysongs[row[1]] = row;
                }
            }
        }
        catch(invalid_argument){
            cout << "not an interger"<<endl;
        }
        try{
            float accoustic = stof(row[4]);
            if(accoustic > 0.7){
                if(chill.find(row[1]) == chill.end()){
                    chill[row[1]] = row;
                }
            }
        }
        catch(invalid_argument){
            cout<<"not an integer"<<endl;
        }
    }
}


