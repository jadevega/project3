#include <map>
#include <string>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "readandmap.h"
#include "song_object.h"

using namespace std;

vector<vector<string>>readandmap::ReadFile(string filename, vector<SongObject::Song>& song_objects ){
    vector<vector<string>>data;
    ifstream file(filename);
    if(file.is_open()){
        cout<<"you opened it bb"<<endl;
        string line;

        //Counter to skip the first two rows
        int linecount = 0;

       while(getline(file, line)){
            //skipping headers
           if (linecount < 2) {
               linecount++;
               continue;
           }
           string tracknum;
           string trackid, artists, album_name, trackname, popularity, duration, explicitlyrics,
           dance, energy, key, loudness, mode, speechniess, accousticness, instrumentallness, liveness,
           valence, tempo, timesignature, track_genre;

           stringstream ss(line);
           string current;
           int count = 0;

           bool parsing_error = false;

           SongObject::Song my_song;
           while(getline(ss, current, ',')) {
               if (count == 2 or count == 3 or count == 4) {
                   if (current.front() == '"') {
                       current = current.substr(1);
                       string next;
                       while (getline(ss, next, ',')) {
                           current += "," + next;
                           if (!next.empty() && next.back() == '"') {
                               current = current.substr(0, current.size() - 1); // Remove trailing quote
                               break;
                           }
                       }
                   }
               }

               if (count == 0){
                   tracknum = current;
                   try {
                       my_song.song_number = stoi(tracknum);
                   }
                   catch (const invalid_argument&) {
                       std::cerr << "Error: Invalid argument - unable to convert \"" << tracknum << "\" to an integer." << std::endl;
                   }
               }

               else if(count == 1){
                   trackid = current;
                   cout << "trackid: " << trackid << endl;
                   my_song.track_id = trackid;
                   // my_song.track_id = trackid;
               }
               else if(count == 2){
                   artists = current;
                   my_song.artist = artists;
               }
               else if(count == 3){
                   album_name = current;
                   my_song.album = album_name;
               }
               else if(count == 4){
                   trackname = current;
                   my_song.track_name = trackname;
               }
               else if(count == 5){
                   popularity = current;
                   try {
                       my_song.popularity = stoi(popularity);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if (count == 6){
                   duration = current;
                   try {
                       my_song.duration_ms = stof(duration);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if(count == 7){
                   explicitlyrics = current;
                   my_song.song_explicit = explicitlyrics;
               }
               else if(count == 8){
                   dance = current;
                   try {
                       my_song.danceability = stof(dance);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if(count == 9){
                   energy = current;
                   my_song.energy = stof(energy);
               }
               else if(count == 10){
                   key = current;
                   my_song.key = stof(key);
               }
               else if(count == 11){
                   loudness = current;
                   my_song.loudness = stof(loudness);
               }
               else if (count == 12){
                   mode = current;
                   my_song.mode = stof(mode);
               }
               else if(count == 13){
                  speechniess = current;
                   my_song.speechiness = stof(speechniess);
               }
               else if(count == 14){
                   accousticness = current;
                   my_song.acousticness = stof(accousticness);
               }
               else if(count == 15){
                   instrumentallness = current;
                   my_song.instrumentalness = stof(instrumentallness);
               }
               else if(count == 16){
                   liveness = current;
                   my_song.liveness = stof(liveness);
               }
               else if(count == 17){
                  valence = current;
                   my_song.valence = stof(valence);
               }
               else if(count == 18){
                   tempo = current;
                   try {
                       my_song.tempo = stof(tempo);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                   }
               }
               else if(count == 19){
                   timesignature = current;
                   my_song.time_signature = stof(timesignature);
               }
               else if(count == 20){
                   track_genre = current;
                   my_song.track_genre = track_genre;
               }
               count++;
           }
           if (parsing_error) {
               // Skip adding the song object and continue with the next line
               continue;
           }

           song_objects.push_back(my_song);
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


