#include <map>
#include <string>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "readandmap.h"
#include "song_object.h"

using namespace std;

// Helper function to parse a single CSV field, handling quotes and commas
string readandmap::readCSVField(stringstream &ss) {
    string field;
    if (!getline(ss, field, ',')) {
        return field; // Return empty if no more fields.
    }

    // If the field starts with a quote, we need to handle quoted fields
    if (!field.empty() && field.front() == '"') {
        // Remove the initial quote
        string accumulated = field.substr(1);
        int quoteCount = (int)count(accumulated.begin(), accumulated.end(), '"');

        // If quotes aren't balanced, continue reading until they are
        while (quoteCount % 2 != 1) {
            string nextPart;
            if (!getline(ss, nextPart, ',')) {
                break; // No more data
            }
            accumulated += "," + nextPart;
            quoteCount = (int)count(accumulated.begin(), accumulated.end(), '"');
        }

        // Remove trailing quote if present
        if (!accumulated.empty() && accumulated.back() == '"') {
            accumulated.pop_back();
        }

        // Replace any "" with "
        size_t pos = 0;
        while ((pos = accumulated.find("\"\"", pos)) != string::npos) {
            accumulated.replace(pos, 2, "\"");
            pos += 1;
        }

        field = accumulated;
    }

    return field;
}

void readandmap::ReadFileSet(const string& filename, vector<SongObject::Song>& songs) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "File opened for set implementation." << endl;
        string line;
        int linecount = 0;

        while (getline(file, line)) {
            // Skipping headers
            if (linecount < 2) {
                linecount++;
                continue;
            }

            stringstream ss(line);
            vector<string> fields;
            fields.reserve(21);

            for (int i = 0; i < 21; i++) {
                fields.push_back(readCSVField(ss));
            }

            SongObject::Song my_song;
            bool parsing_error = false;
            try {
                my_song.song_number = stoi(fields[0]);
                my_song.track_id = fields[1];
                my_song.artist = fields[2];
                my_song.album = fields[3];
                my_song.track_name = fields[4];
                my_song.popularity = stoi(fields[5]);
                my_song.duration_ms = stof(fields[6]);
                my_song.song_explicit = fields[7];
                my_song.danceability = stof(fields[8]);
                my_song.energy = stof(fields[9]);
                my_song.key = stof(fields[10]);
                my_song.loudness = stof(fields[11]);
                my_song.mode = stof(fields[12]);
                my_song.speechiness = stof(fields[13]);
                my_song.acousticness = stof(fields[14]);
                my_song.instrumentalness = stof(fields[15]);
                my_song.liveness = stof(fields[16]);
                my_song.valence = stof(fields[17]);
                my_song.tempo = stof(fields[18]);
                my_song.time_signature = stof(fields[19]);
                my_song.track_genre = fields[20];
            } catch (const invalid_argument&) {
                parsing_error = true;
            }

            if (!parsing_error) {
                songs.push_back(my_song);
            }
        }

        file.close();
    } else {
        cout << "Error opening file for set implementation." << endl;
    }
}


vector<vector<string>>readandmap::ReadFileMap(const string& filename){
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

           float tracks, art, alb, track, pop, dur, exp, dan, ene, ky, loud, mod, speech, acc, instr, live,
           val, temp, time, trackgen;

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
               }

               else if(count == 1){
                   trackid = current;
//                   my_song.track_id = trackid;
               }
               else if(count == 2){
                   artists = current;
//                   my_song.artist = artists;
               }
               else if(count == 3){
                   album_name = current;
//                   my_song.album = album_name;
               }
               else if(count == 4){
                   trackname = current;
//                   my_song.track_name = trackname;
               }
               else if(count == 5){

                   try {
                       pop = stof(current);
//                       my_song.popularity = stoi(popularity);
                       popularity = current;
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if (count == 6){

                   try {
                       dur = stof(current);
                       duration = current;
//                       my_song.duration_ms = stof(duration);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if(count == 7){
                   explicitlyrics = current;
//                   my_song.song_explicit = explicitlyrics;
               }
               else if(count == 8){
                   try {
                       dan = stof(current);
                       dance = current;
//                       my_song.danceability = stof(dance);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                       break;
                   }
               }
               else if(count == 9){
                   energy = current;
//                   my_song.energy = stof(energy);
               }
               else if(count == 10){
                   key = current;
//                   my_song.key = stof(key);
               }
               else if(count == 11){
                   loudness = current;
//                   my_song.loudness = stof(loudness);
               }
               else if (count == 12){
                   mode = current;
//                   my_song.mode = stof(mode);
               }
               else if(count == 13){
                  speechniess = current;
//                   my_song.speechiness = stof(speechniess);
               }
               else if(count == 14){
                   accousticness = current;
//                   my_song.acousticness = stof(accousticness);
               }
               else if(count == 15){
                   instrumentallness = current;
//                   my_song.instrumentalness = stof(instrumentallness);
               }
               else if(count == 16){
                   liveness = current;
//                   my_song.liveness = stof(liveness);
               }
               else if(count == 17){
                  valence = current;
//                   my_song.valence = stof(valence);
               }
               else if(count == 18){
//
                   try {
                       temp = stof(current);
                       tempo = current;
//                       my_song.tempo = stof(tempo);
                   }
                   catch (const invalid_argument&) {
                       parsing_error = true;
                   }
               }
               else if(count == 19){
                   timesignature = current;
//                   my_song.time_signature = stof(timesignature);
               }
               else if(count == 20){
                   track_genre = current;
//                   my_song.track_genre = track_genre;
               }
               count++;
           }
           if (parsing_error) {
               // Skip adding the song object and continue with the next line
               continue;
           }

//
           vector<string>specificinfo = {artists, trackname, dance, energy, valence, accousticness, liveness, mode,
                                         speechniess, tempo, instrumentallness, loudness};
           data1.push_back(specificinfo);
       }

       file.close();
    }
    else{
        cout<<"Error"<<endl;
    }

    return data1;
}

unordered_map<string,vector<string>>readandmap::AddtoMapHappy() {
    for (auto row: data1) {

        try {
            float valenceflo = stof(row[4]);
            if (valenceflo > 0.66) {
                float danceability = stof(row[2]);
                if (danceability > 0.66) {
                    float energyflo = stof(row[3]);
                    if (energyflo > 0.33 and energyflo < 0.66) {
                        float tempoflo = stof(row[9]);
                        if (tempoflo > 80) {
                            float loudflo = stof(row[11]);
                            if (loudflo > -15.0 and loudflo < -5.0) {
                                float modeflo = stof(row[7]);
                                if (modeflo > 0.5) {
                                    string important = row[0] + " " + row[1] ;
                                    if (data.find("happy") == data.end()) {
                                        data["happy"] = {};
                                    }
                                    if (find(data["happy"].begin(), data["happy"].end(), important) ==
                                        data["happy"].end()) {
//                                        string important = row[0] + " " + row[1] ;
                                        data["happy"].push_back(important);
                                    }
//                                    else{
//                                        continue;
//                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        catch (invalid_argument) {
//            break;
            continue;

        }
    }
    return data;
}
unordered_map<string, vector<string>>readandmap::AddtoMapSad(){
    for (auto row: data1) {
        try {
            float valenceflo = stof(row[4]);
            if (valenceflo <= 0.33) {
                float danceability = stof(row[2]);
                if (danceability <= 0.33) {
                    float energyflo = stof(row[3]);
                    if (energyflo <=0.33) {
                        float accoustflo = stof(row[5]);
                        if (accoustflo > 0.66) {
                            float speechflo = stof(row[8]);
                            if (speechflo< .66) {
                                float modeflo = stof(row[7]);
                                if (modeflo < 0.5) {
                                    float liveflo = stof(row[6]);
                                    if(liveflo <=0.33){
                                        float tempoflo = stof(row[9]);
                                            if(tempoflo <=80) {
                                                string important = row[0] + " " + row[1] ;
                                                if (data.find("sad") == data.end()) {
                                                    data["sad"] = {};
                                                }
                                                if (find(data["sad"].begin(), data["sad"].end(), important) ==data["sad"].end()) {
                                                    data["sad"].push_back(important);
                                                }
                                            }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        catch (invalid_argument) {
            continue;
        }
    }
    return data;
}
unordered_map<string, vector<string>>readandmap::AddtoMapRelaxed(){

    for (auto row: data1) {
        try {
            float valenceflo = stof(row[4]);
            if (valenceflo > 0.33 and valenceflo <0.66) {
                    float energyflo = stof(row[3]);
                    if (energyflo <= 0.66){
                        float accoustflo = stof(row[5]);
                        if (accoustflo > 0.33 and accoustflo <=.66) {
                                    float liveflo = stof(row[6]);
                                    if(liveflo <=0.66) {
                                        float tempoflo = stof(row[9]);
                                        if (tempoflo <= 160) {
                                            float instruflo = stof(row[10]);
                                            if(instruflo > 0.66) {
                                                string important = row[0] + " " + row[1];
                                                if (data.find("relaxed") == data.end()) {
                                                    data["relaxed"] = {};
                                                }
                                                if (find(data["relaxed"].begin(), data["relaxed"].end(), important) ==
                                                    data["relaxed"].end()) {
                                                    data["relaxed"].push_back(important);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
        catch (invalid_argument) {
           continue;
        }
    }
    return data;
}
unordered_map<string, vector<string>>readandmap::AddtoMapEnergetic(){
    for(auto row: data1){
        try{
            float energyflo = stof(row[3]);
            if (energyflo > .66){
                float tempoflo = stof(row[9]);
                if(tempoflo> 160.0){
                    float danceflo = stof(row[2]);
                        if(danceflo > 0.66){
                            float liveflo = stof(row[6]);
                            if(liveflo > .66){
                                float loudflo = stof(row[11]);
                                    if(loudflo > -5){
                                        float modeflo = stof(row[7]);
                                        if(modeflo > .5){
                                            float accoustflo = stof(row[5]);
                                            if(accoustflo < .66){
                                                string important = row[0] + " " + row[1];
                                                if (data.find("energetic") == data.end()) {
                                                    data["energetic"] = {};
                                                }
                                                if (find(data["energetic"].begin(), data["energetic"].end(), important) ==
                                                    data["energetic"].end()) {
                                                    data["energetic"].push_back(important);
                                                }
                                            }
                                        }
                                    }

                            }
                    }
                }
            }
        }
        catch (invalid_argument) {
            continue;
        }
    }
    return data;
}