//
// Created by Isabelle Carminati on 11/28/24.
//

#ifndef SONG_OBJECT_H
#define SONG_OBJECT_H

#include <set>
#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>


template <typename T>
class HashSet {
private:
    std::vector<std::list<T>> buckets;
    size_t numBuckets;

    size_t hash(const T& key) const {
        // You'll need a good hash function for your data type
        std::hash<T> hasher;
        return hasher(key) % numBuckets;
    }


public:
    HashSet(size_t numBuckets = 162857) : numBuckets(numBuckets), buckets(numBuckets) {}

    void insert(T& key) {
        size_t index = hash(key);
        std::list<T>& bucket = buckets[index];

        // Check if the key already exists
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it == bucket.end()) {
            bucket.push_back(key);
        }
    }

    bool contains(const T& key) const {
        size_t index = hash(key);
        const std::list<T>& bucket = buckets[index];

        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }

    void remove(const T& key) {
        size_t index = hash(key);
        std::list<T>& bucket = buckets[index];

        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) {
            bucket.erase(it);
        }
    }

    bool empty() const {
        for (const auto& bucket : buckets) {
            if (!bucket.empty()) {
                return false;
            }
        }
        return true;
    }

    size_t size() const {
        size_t totalSize = 0;
        for (const auto& bucket : buckets) {
            totalSize += bucket.size();
        }
        return totalSize;
    }

    // Iterable structure
    std::vector<T> getAllElements() const {
        std::vector<T> elements;
        for (const auto& bucket : buckets) {
            elements.insert(elements.end(), bucket.begin(), bucket.end());
        }
        return elements;
    }
};

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
        bool operator==(const Song& other) const;

        Song() = default;
    };

    //Functions
    void displayPlayList(string& mood);
    void specific_displayPlayList(string &mood, const int &song_amount);
    string trim(string& str);

    //Determines mood
    void mood_logic(HashSet<Song>& song_objects);
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

    HashSet<Song> happy;
    HashSet<Song> sad;
    HashSet<Song> relaxed;
    HashSet<Song> energetic;
    HashSet<Song> mysterious;

};

#endif //SONG_OBJECT_H

