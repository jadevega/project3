//
// Created by Isabelle Carminati on 11/28/24.
//

#ifndef SONG_OBJECT_H
#define SONG_OBJECT_H

#include <set>
#include <string>

using namespace std;

class SongObject{
    public:
    //Comments represent range in data
        struct Song {
            string mood;

            float danceability = 0;         // 0 - 0.98
            float energy = 0;               // 0 - 1
            float key = 0;                  // 0 - 11
            float loudness = 0;             // -49.5 - 4.53
            float mode = 0;                 // 0 - 1
            float speechiness = 0;          // 0 - 1
            float acousticness = 0;         // 0 - 1
            float instrumentalness = 0;     // 0 - 1
            float liveness = 0;             // 0 - 1
            float valence = 0;              // 0 - 0.99
            float tempo = 0;                // 0 - 243
            float time_signature = 0;       // 0 - 5

            // Corresponding string variables for levels
            string danceability_level;
            string energy_level;
            string key_level;
            string loudness_level;
            string mode_level;
            string speechiness_level;
            string acousticness_level;
            string instrumentalness_level;
            string liveness_level;
            string valence_level;
            string tempo_level;
            string time_signature_level;

            // Other variables
            int song_number;
            string track_id;
            string artist;
            string album;
            string track_name;
            int popularity;
            float duration_ms;
            string song_explicit;
            string track_genre;

        //Overloaded operator to prioritize higher mood scores
            bool operator<(const Song &other) const;
        };

    //Functions
    void displayPlayList(string& mood);
    void specific_displayPlayList(string &mood, const int &song_amount);
    string trim(string& str);

    //Determines mood
    void mood_logic(vector<Song>& song_objects);
    void logic_helper(const string& variable, Song& song);

private:
    //list of variables that determine a moood
    set<string> song_variables = {
        "danceability",
        "energy",
        "key",
        "loudness",
        "mode",
        "speechiness",
        "acousticness",
        "instrumentalness",
        "liveness",
        "valence",
        "tempo",
        "time signature"
    };

    //Comparable data contianer 1: Sets --------------------------------------------------------------------------------

    set<Song> happy;
    set<Song> sad;
    set<Song> relaxed;
    set<Song> energetic;
    set<Song> mysterious;

};

#endif //SONG_OBJECT_H
