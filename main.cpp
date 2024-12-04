#include <iostream>
#include "readandmap.h"
#include "song_object.h"
#include<string>
#include<vector>
using namespace std;
#include<sstream>
//int main() {
//    readandmap readMapper;
//
//// Call the ReadFileMap function to load data into the HashTable
//    HashTable<string, vector<string>> songData = readMapper.ReadFileMap("dataset.csv");
//
//// Call AddtoMapHappy to get a subset of the data
//    HashTable<string, vector<string>> happySongs = readMapper.AddtoMapHappy();
//
//// Call AddtoMapSad to get another subset of the data
//    HashTable<string, vector<string>> sadSongs = readMapper.AddtoMapSad();
//
//// Call AddtoMapRelaxed for relaxed songs
//    HashTable<string, vector<string>> relaxedSongs = readMapper.AddtoMapRelaxed();
//
//// Call AddtoMapEnergetic for energetic songs
//    HashTable<string, vector<string>> energeticSongs = readMapper.AddtoMapEnergetic();
//
//// Example of accessing the data
//    vector<string> happySongList;
//
//    if (happySongs.checkifhas("happy") && happySongs.getvec("happy", happySongList)) {
//        cout << "Happy Songs: " << endl;
//        for (const auto &song: happySongList) {
//            cout << song << endl;
//        }
//    } else {
//        cout << "No happy songs found." << endl;
//    }
//
//    return 0;
//}



//using namespace std;
int main() {
    readandmap readMapper;

// Call the ReadFileMap function to load data into the HashTable
    HashTable<string, vector<string>> data1 = readMapper.ReadFileMap("dataset.csv");

    // Call AddtoMapHappy, passing data1 as an argument
    HashTable<string, vector<string>> energeticMap = readMapper.AddtoMapEnergetic(data1);

// Call AddtoMapSad to get another subset of the data
//    HashTable<string, vector<string>> sadSongs = readMapper.AddtoMapSad();
//
//// Call AddtoMapRelaxed for relaxed songs
//    HashTable<string, vector<string>> relaxedSongs = readMapper.AddtoMapRelaxed();

// Call AddtoMapEnergetic for energetic songs
//    HashTable<string, vector<string>> energeticSongs = readMapper.AddtoMapEnergetic();
//
//// Example of accessing the data
//    vector<string> happySongList;
    for (auto& list : energeticMap.getData()) {
        for (auto& pair : list) {
            string tracknum = pair.first;
            vector<string> values = pair.second;
            // Print out the track number and its associated data
            std::cout << "Track Number: " << tracknum << ", Artist and Track: " << values[0] << " - " << values[1] << std::endl;
        }
    }


    return 0;
}



//    readandmap hi;
//    SongObject modify_songs;
//    //stores all song objects
//    vector<SongObject::Song> song_container;
//    hi.ReadFileMap("dataset.csv");
//    hi.ReadFileSet("dataset.csv", song_container);
//
//    modify_songs.mood_logic(song_container);
//    bool moodytune = true;
//
//    cout << "Welcome to MoodyTune! Tell me your mood and I can output a curated playlist depending on that very mood :)" << endl;
//    cout << "Let's start with our first question..." << endl;
//    while (moodytune) {
//        try {
//            string mood;
//            cout << "What mood are you in?" << endl;
//            cout << "\t*Happy" << endl
//                 << "\t*Sad" << endl
//                 << "\t*Relaxed" << endl
//                 << "\t*Energetic" << endl
//                 << "\t*Mysterious" << endl;
//            cin >> mood;
//
//            // For consistency in input
//            ranges::transform(mood, mood.begin(), ::tolower);
//
//            int decision = -1;
//
//            //CHANGE WITH FRONT END IMPLEMENTATION FOR PERSONALZED COMMENTS
//            if (mood == "happy" || mood == "sad" || mood == "relaxed" || mood == "mysterious" || mood == "energetic") {
//                string data_type;
//                //example comment depending on a mood- here would be for the happy mood
//                cout << "Wow you must be having a good day! Do you want all recommended songs or a certain amount?" << endl;
//                cout << "\tType 0 for all, or the number of recommended songs..." << endl;
//
//                cin >> decision;
//
//                // Validate input for decision
//                if (cin.fail() || decision < 0) {
//                    throw invalid_argument("Invalid input for decision. Please enter a non-negative integer.");
//                }
//
//                cout << "Cool! Do you prefer a set or map? Press 's' for set and 'm' for map..." << endl;
//                cin >> data_type;
//
//                // For consistency in input
//                ranges::transform(data_type, data_type.begin(), ::tolower);
//
//                if (data_type != "s" && data_type != "m") {
//                    throw invalid_argument("Invalid input for data type. Please enter 's' or 'm'.");
//                }
//
//                cout << "MoodyTune lOaDiNg ~~~~~~~" << endl;
//
//                if (data_type == "s") {
//                    if (decision == 0) {
//                        modify_songs.displayPlayList(mood);
//                    } else {
//                        modify_songs.specific_displayPlayList(mood, decision);
//                    }
//                } else if (data_type == "m") {
//                    cout << "Maps code for jade..." << endl;
//
//                }
//            } else {
//                throw invalid_argument("Invalid mood input. Please enter a valid mood.");
//            }
//
//            int go_again = 0;
//            cout << "Do you want another playlist? Press 1 if yes..." << endl;
//            cin >> go_again;
//
//            // Validate input for `go_again`
//            if (cin.fail() || (go_again != 1 && go_again != 0)) {
//                throw invalid_argument("Invalid input for go again. Please enter 1 for yes or 0 for no.");
//            }
//
//            moodytune = (go_again == 1);
//
//
//        } catch (const invalid_argument& e) {
//            cout << "Error: " << e.what() << endl;
//
//            // Clear the input buffer in case of an error
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            cout << "Let's try again!" << endl;
//        } catch (const exception& e) {
//            cout << "Unexpected error: " << e.what() << endl;
//            break;
//        }
//    }
//
//    // monique should do the rest and implement frontend logic
//    return 0;
//}