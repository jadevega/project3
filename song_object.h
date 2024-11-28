//
// Created by Isabelle Carminati on 11/28/24.
//

#ifndef SONG_OBJECT_H
#define SONG_OBJECT_H

#include <queue>
#include <string>

using namespace std;

class SongObject{
    public:
    //Comments represent range in data
        struct Song {
            //Score TBA range
            string mood;
            int mood_score = 0;
            // 0 - 114k
            int song_number;
            //0 - 89,741
            string track_id;
            //0 - 31,438
            string artist;
            //0 - 46,590
            string album;
            //0 - 73,609
            string track_name;
            //0 - 100
            int popularity;
            //0 - 5.24 milliseconds
            float duration_ms;
            //T or F
            string song_explicit;
            //0 - 0.98
            float danceability;
            //0 - 1
            float energy;
            //0 - 11
            float key;
            //-49.5 - 4.53
            float loudness;
            //0 - 1
            float mode;
            //0 - speechiness
            float speechiness;
            //0 - 1
            float acousticness;
            //0 - 1
            float instrumentalness;
            //0 - 1
            float liveness;
            //0 - 0.99
            float valence;
            //0 - 243
            float tempo;
            //0 - 5;
            float time_signature;
            //0 - 114 unique values
            string track_genre;

        //Overloaded operator to prioritize higher mood scores
            bool operator<(const Song& other) const;
        };

    //Functions
    void addSongToQueue(Song& song, string& mood);
    void displayQueue(string& mood);
    void specific_displayQueue(string &mood, const int &song_amount);

    //Determines mood
    void mood_logic(Song& song);



private:
    //More moods may be added. Utilizing priority queues for displays and mood data container.

    // High valence, high energy, high danceability, fast tempo, high loudness
    priority_queue<Song> happy;

    // High valence, high energy, high loudness, moderate speechiness, medium-to-high tempo
    priority_queue<Song> motivational;

    // Medium valence, high energy, high danceability, high tempo, major mode
    priority_queue<Song> energetic;

    // Medium valence, medium-to-high energy, high danceability, moderate tempo, low liveness
    priority_queue<Song> danceable;

    // Medium valence, medium energy, high acousticness, low tempo, medium liveness
    priority_queue<Song> romantic;

    // Medium valence, low energy, low tempo, high instrumentalness, very low speechiness
    priority_queue<Song> studious_chill;

    // Medium valence, low energy, high liveness, high acousticness, low tempo
    priority_queue<Song> mellow;

    // Low valence, high energy, high loudness, high speechiness, minor mode
    priority_queue<Song> aggressive;

    // Low valence, low energy, low danceability, high acousticness, moderate speechiness
    priority_queue<Song> sad;

    // Medium valence, low energy, high acousticness, low tempo, high instrumentalness
    priority_queue<Song> relaxed;

    // High instrumentalness, extreme speechiness, extreme tempo
    priority_queue<Song> experimental;

    // Medium valence, medium energy, high danceability, moderate loudness, medium tempo
    priority_queue<Song> groovy;

    // Getter functionn
    priority_queue<Song>& getQueue(string& mood);
};

#endif //SONG_OBJECT_H
