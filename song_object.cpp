//
// Created by Isabelle Carminati on 11/28/24.
//

#include "song_object.h"
#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;


// struct functions ----------------------------------------------------------------------------------------------------
bool SongObject::Song::operator<(const Song &other) const {
    return mood_score < other.mood_score; // Higher scores have higher priority
}

// Queue functions -----------------------------------------------------------------------------------------------------

// Add a song to the appropriate mood queue
void SongObject::addSongToQueue(Song& song, string& mood) {
    try {
        getQueue(mood).push(song);
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Get the appropriate queue based on the mood
priority_queue<SongObject::Song>& SongObject::getQueue(string& mood) {
    if (mood == "happy") return happy;
    if (mood == "sad") return sad;
    if (mood == "energetic") return energetic;
    if (mood == "relaxed") return relaxed;
    if (mood == "romantic") return romantic;
    if (mood == "aggressive") return aggressive;
    if (mood == "danceable") return danceable;
    if (mood == "studious_chill") return studious_chill;
    if (mood == "groovy") return groovy;
    if (mood == "mellow") return mellow;
    if (mood == "inspirational") return motivational;
    throw invalid_argument("Invalid mood: " + mood);
}

// Display all songs in the specified mood queue
void SongObject::displayQueue(string& mood)  {
    auto my_queue = getQueue(mood); // Copy the queue to display elements
    cout << "Songs in " << mood << " queue:" << endl;
    while (!my_queue.empty()) {
        auto song = my_queue.top();
        cout << "Track: " << song.track
                  << ", Artist: " << song.artist
                  << ", Mood Score: " << song.mood_score << endl;
        my_queue.pop();
    }
}
// Display specific number of songs in the specified mood queue
void SongObject::specific_displayQueue(string& mood, const int& song_amount)  {
    auto my_queue = getQueue(mood); // Copy the queue to display elements
    if (song_amount > my_queue.size()) {
        cout << "Song amount exceeded the size of the queue" << endl;
        return;
    }

    cout << "Songs in " << mood << " queue:" << endl;
    cout << "h" << endl;

    while (my_queue.size() > song_amount) {
        auto song = my_queue.top();
        cout << "Track: " << song.track
                  << ", Artist: " << song.artist
                  << ", Mood Score: " << song.mood_score << endl;
        my_queue.pop();
    }
}

// Mood Logic functions ------------------------------------------------------------------------------------------------

void SongObject::mood_logic(Song &song) {
    cout << "next commit will have logic" << endl;
}
