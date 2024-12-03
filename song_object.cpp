//
// Created by Isabelle Carminati on 11/28/24.
//

#include "song_object.h"
#include <iostream>
#include <queue>

using namespace std;

// struct functions ----------------------------------------------------------------------------------------------------
bool SongObject::Song::operator<(const Song &other) const {
    // Compare by popularity first
    if (popularity != other.popularity) return popularity < other.popularity;
    // Then by artist
    if (artist != other.artist) return artist < other.artist;
    // Then by track name
    if (track_name != other.track_name) return track_name < other.track_name;
    // Then by album (if you want this considered)
    if (album != other.album) return album < other.album;

    // If we get here, they are essentially the same song
    return false;
}

// Set functions -------------------------------------------------------------------------------------------------------

string SongObject::trim(string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Display all songs in the specified mood queue
void SongObject::displayPlayList(string& mood) {
    cout << "Displaying playlist for mood: " << mood << endl;

    // Pointer to the appropriate set
    set<Song>* moodSet = nullptr;

    // Match the mood string to the corresponding set
    if (mood == "happy") {
        moodSet = &happy;
    } else if (mood == "mysterious") {
        moodSet = &mysterious;
    } else if (mood == "sad") {
        moodSet = &sad;
    } else if (mood == "relaxed") {
        moodSet = &relaxed;
    } else if (mood == "energetic") {
        moodSet = &energetic;
    } else {
        cout << "Invalid mood: " << mood << endl;
        return;
    }

    // Check if the set is empty
    if (moodSet->empty()) {
        cout << "No songs found for the mood: " << mood << endl;
        return;
    }

    // Iterate through the set and display each song

    for (const auto& song : *moodSet) {
        string name = song.track_name;
        string artist = song.artist;
        string album = song.album;

        cout << "Song Name: " << trim(name) << ", Artist: " << trim(artist) << "Album: " << trim(album) << endl;
    }
    cout << "Total Songs: " << moodSet->size() << endl;
}

// Display specific number of songs in the specified mood queue
void SongObject::specific_displayPlayList(string& mood, const int& song_amount)  {
    cout << "Displaying playlist for mood: " << mood << endl;

    // Pointer to the appropriate set
    set<Song>* moodSet = nullptr;
    // Match the mood string to the corresponding set
    if (mood == "happy") {
        moodSet = &happy;
    }else if (mood == "sad") {
        moodSet = &sad;
    } else if (mood == "relaxed") {
        moodSet = &relaxed;
    } else if (mood == "energetic") {
        moodSet = &energetic;
    } else if (mood == "mysterious"){
        moodSet = &mysterious;
    } else {
        cout << "Invalid mood: " << mood << endl;
        return;
    }

    // Check if the set is empty
    if (moodSet->empty()) {
        cout << "No songs found for the mood: " << mood << endl;
        return;
    }

    if (moodSet->size() < song_amount) {
        cout << "You requested too many songs pookie" << endl;
        return;
    }

    // Iterate through the set and display each song
    int count = 0;
    for (const auto& song : *moodSet) {
        cout << "Song Name: " << song.track_name << ", Artist: " << song.artist << "Album: " << song.album << endl;
        count++;
        //so only the specified amount displays
        if (count >= song_amount) {
            cout << "Total Songs: " << count << endl;
            break;
        }
    }
}

// Mood Logic functions ------------------------------------------------------------------------------------------------

// Assigns mood and adds to data container
    //Jade can configure by adding code that allows her map to get populated
void SongObject::mood_logic(vector<Song>& song_objects) {
    for (auto& song : song_objects) {
        for (const string& variable : song_variables) {
            logic_helper(variable, song);
        }

        // Initialize counts for each mood
        int happy_count = 0;
        int sad_count = 0;
        int relaxed_count = 0;
        int energetic_count = 0;

        // Check conditions for happy mood
        if (song.valence_level == "high") happy_count++;
        if (song.energy_level == "medium") happy_count++;
        if (song.danceability_level == "high") happy_count++;
        if (song.tempo_level == "medium" || song.tempo_level == "high") happy_count++;
        if (song.loudness_level == "medium") happy_count++;
        if (song.mode_level == "major") happy_count++;

        // Check conditions for sad mood
        if (song.valence_level == "low") sad_count++;
        if (song.energy_level == "low") sad_count++;
        if (song.danceability_level == "low") sad_count++;
        if (song.acousticness_level == "high") sad_count++;
        if (song.speechiness_level == "medium") sad_count++;
        if (song.mode_level == "minor") sad_count++;
        if (song.liveness_level == "low") sad_count++;
        if (song.tempo_level == "low") sad_count++;

        // Check conditions for relaxed mood
        if (song.valence_level == "medium") relaxed_count++;
        if (song.energy_level == "low" || song.energy_level == "medium") relaxed_count++;
        if (song.acousticness_level == "medium") relaxed_count++;
        if (song.tempo_level == "low" || song.tempo_level == "medium") relaxed_count++;
        if (song.instrumentalness_level == "high") relaxed_count++;
        if (song.liveness_level == "medium" || song.liveness_level == "low") relaxed_count++;

        // Check conditions for energetic mood
        if (song.energy_level == "high") energetic_count++;
        if (song.tempo_level == "high") energetic_count++;
        if (song.danceability_level == "high") energetic_count++;
        if (song.liveness_level == "high") energetic_count++;
        if (song.loudness_level == "high") energetic_count++;
        if (song.mode_level == "major") energetic_count++;
        if (song.acousticness_level == "low") energetic_count++;



        // Determine the mood based on the highest count
        // Set a threshold for assigning the mood
        //if set to 3 then some go into the mysterious mood
        int threshold = 2; // You can adjust this value as needed

        if (happy_count >= threshold && happy_count >= sad_count && happy_count >= relaxed_count && happy_count >= energetic_count) {
            song.mood = "happy";
            happy.insert(song);
        } else if (sad_count >= threshold && sad_count >= happy_count && sad_count >= relaxed_count && sad_count >= energetic_count) {
            song.mood = "sad";
            sad.insert(song);
        } else if (relaxed_count >= threshold && relaxed_count >= happy_count && relaxed_count >= sad_count && relaxed_count >= energetic_count) {
            song.mood = "relaxed";
            relaxed.insert(song);
        } else if (energetic_count >= threshold && energetic_count >= happy_count && energetic_count >= sad_count && energetic_count >= relaxed_count) {
            song.mood = "energetic";
            energetic.insert(song);
        } else {
            song.mood = "mysterious";
            mysterious.insert(song);
        }
    }
}

void SongObject::logic_helper(const string& variable, Song& song) {
    string low = "low";
    string medium = "medium";
    string high = "high";
    string minor = "minor";
    string major = "major";
    trim(song.artist);
    trim(song.track_name);
    trim(song.album);
    trim(song.track_id);
    trim(song.song_explicit);
    trim(song.track_genre);

    if (variable == "danceability") {
        if (song.danceability <= 0.33) {
            song.danceability_level = low;
        } else if (song.danceability > 0.33 && song.danceability <= 0.66) {
            song.danceability_level = medium;
        } else if (song.danceability > 0.66) {
            song.danceability_level = high;
        }
    }

    if (variable == "energy") {
        if (song.energy <= 0.33) {
            song.energy_level = low;
        } else if (song.energy > 0.33 && song.energy <= 0.66) {
            song.energy_level = medium;
        } else if (song.energy > 0.66) {
            song.energy_level = high;
        }
    }

    if (variable == "key") {
        if (song.key <= 3) {
            song.key_level = low;
        } else if (song.key > 3 && song.key <= 7) {
            song.key_level = medium;
        } else if (song.key > 7) {
            song.key_level = high;
        }
    }

    if (variable == "loudness") {
        if (song.loudness <= -15) {
            song.loudness_level = low;
        } else if (song.loudness > -15 && song.loudness <= -5) {
            song.loudness_level = medium;
        } else if (song.loudness > -5) {
            song.loudness_level = high;
        }
    }

    if (variable == "mode") {
        if (song.mode <= 0.5) {
            song.mode_level = minor;
        } else {
            song.mode_level = major;
        }
    }

    if (variable == "speechiness") {
        if (song.speechiness <= 0.33) {
            song.speechiness_level = low;
        } else if (song.speechiness > 0.33 && song.speechiness <= 0.66) {
            song.speechiness_level = medium;
        } else if (song.speechiness > 0.66) {
            song.speechiness_level = high;
        }
    }

    if (variable == "acousticness") {
        if (song.acousticness <= 0.33) {
            song.acousticness_level = low;
        } else if (song.acousticness > 0.33 && song.acousticness <= 0.66) {
            song.acousticness_level = medium;
        } else if (song.acousticness > 0.66) {
            song.acousticness_level = high;
        }
    }

    if (variable == "instrumentalness") {
        if (song.instrumentalness <= 0.33) {
            song.instrumentalness_level = low;
        } else if (song.instrumentalness > 0.33 && song.instrumentalness <= 0.66) {
            song.instrumentalness_level = medium;
        } else if (song.instrumentalness > 0.66) {
            song.instrumentalness_level = high;
        }
    }

    if (variable == "liveness") {
        if (song.liveness <= 0.33) {
            song.liveness_level = low;
        } else if (song.liveness > 0.33 && song.liveness <= 0.66) {
            song.liveness_level = medium;
        } else if (song.liveness > 0.66) {
            song.liveness_level = high;
        }
    }

    if (variable == "valence") {
        if (song.valence <= 0.33) {
            song.valence_level = low;
        } else if (song.valence > 0.33 && song.valence <= 0.66) {
            song.valence_level = medium;
        } else if (song.valence > 0.66) {
            song.valence_level = high;
        }
    }

    if (variable == "tempo") {
        if (song.tempo <= 80) {
            song.tempo_level = low;
        } else if (song.tempo > 80 && song.tempo <= 160) {
            song.tempo_level = medium;
        } else if (song.tempo > 160) {
            song.tempo_level = high;
        }
    }

    if (variable == "time signature") {
        if (song.time_signature <= 2) {
            song.time_signature_level = low;
        } else if (song.time_signature > 2 && song.time_signature <= 4) {
            song.time_signature_level = medium;
        } else if (song.time_signature > 4) {
            song.time_signature_level = high;
        }
    }
}
