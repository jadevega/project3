#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<chrono>
#include "readandmap.h"
#include "song_object.h"
using namespace std;

int main() {

    //creates two instances of the readandmap class for reading in the data to the hashmap and hashset
    readandmap readMapper;
    readandmap readSet;

    //used to initialize the while loop
    bool moodytune = true;

    // Call the ReadFileMap function to load data into the HashMap
    HashTable<string, vector<string>> data1 = readMapper.ReadFileMap("dataset.csv");
    HashTable<string, vector<string>> songs;

    //call the ReadFileSet function to load data into the HashSet
    HashSet<SongObject::Song> data2 = readSet.ReadFileSet("dataset.csv");
    //creates an instance of the SongObject class and evaluates the mood for each song in the hashset
    SongObject songClassifier;
    songClassifier.mood_logic(data2);

    //prompts the user for the data set type they will be using
    std::string data_type;
    cout << "Welcome to MoodyTune! Tell me your mood and I can output a curated playlist depending on that very mood :)" << endl;
    cout << "Let's start with our first question..." << endl;
    cout << "Will we be working with hashmaps or hashsets today? Type 's' for hashsets and 'm' for hashmaps... "<< endl;
    cin >> data_type;

    // For consistency in input | all lowercase letters
    ranges::transform(data_type, data_type.begin(), ::tolower);

    //while loop for the terminal input/output
    while (moodytune) {
        try {

            //if the data type previously entered is not 's' or 'm' throw an error
            if (data_type != "s" && data_type != "m") {
                throw invalid_argument("Invalid input for data type. Please enter 's' or 'm'.");
            }

            //prompts the user to enter what mood they are in
            string mood;
            cout << "What mood are you in?" << endl;
            cout << "\t♩ Happy" << endl
                 << "\t♩ Sad" << endl
                 << "\t♩ Relaxed" << endl
                 << "\t♩ Energetic" << endl;
            cin >> mood;

            // For consistency in input | makes input all lowercase
            ranges::transform(mood, mood.begin(), ::tolower);

            //this variable determines the number of songs that the playlist will contain based on user input
            int numSongs = -1;

            //if the mood selected is one four available the run the code
            if (mood == "happy" || mood == "sad" || mood == "relaxed" || mood == "energetic") {
                //runs if the user selected happy
                if(mood == "happy"){
                    //personalized message for happy mood gets printed
                    cout << "Wow you must be having a good day! "
                            "\nDo you want all recommended songs or a certain amount?" << endl;
                    cout << "\t* Type 0 for all, or the number of desired songs for your playlist *" << endl;

                    //the num of songs the user selected is read into the variable
                    cin >> numSongs;

                    //add happy songs to hashmap if user chose hashmaps
                    if(data_type == "m"){songs = readMapper.AddtoMapHappy(data1);}

                    //add happy songs to hashset if user chose hashset
                    if(data_type == "s"){
                        if(numSongs == 0){
                            songClassifier.displayPlayList(mood);
                        }
                        else{
                            songClassifier.specific_displayPlayList(mood, numSongs);
                        }
                    }
                }
                    //runs if the user selected energetic
                else if(mood == "energetic"){
                    //personalized message for energetic mood gets printed
                    cout << "Wow, you're full of energy! Let's find some tunes to match your vibe!"
                            "\nDo you want all recommended songs or a certain amount?" << endl;
                    cout << "\t* Type 0 for all, or the number of desired songs for your playlist *" << endl;

                    //the num of songs the user selected is read into the variable
                    cin >> numSongs;

                    //add energetic songs to hashmap if user chose hashmap
                    if(data_type == "m"){songs = readMapper.AddtoMapEnergetic(data1);}
                    //add energetic songs to hashset if user chose hashset
                    if(data_type == "s"){
                        //the proper functions are called depending on the num of songs the user selected for their playlist
                        if(numSongs == 0){
                            songClassifier.displayPlayList(mood);
                        }
                        else{
                            songClassifier.specific_displayPlayList(mood, numSongs);
                        }
                    }
                }
                    //runs if the user selected sad
                else if(mood == "sad"){
                    //personalized message for sad mood gets printed
                    cout << "I'm sorry to hear you're feeling down. "
                            "\nDo you want all recommended songs or a certain amount?" << endl;
                    cout << "\t* Type 0 for all, or the number of desired songs for your playlist *" << endl;

                    //the num of songs the user selected is read into the variable
                    cin >> numSongs;

                    //add sad songs to hashmap if user chose hashmap
                    if(data_type == "m"){songs = readMapper.AddtoMapSad(data1);}
                    //add sad songs to hashset if user chose hashset
                    if(data_type == "s"){
                        //the proper functions are called depending on the num of songs the user selected for their playlist
                        if(numSongs == 0){
                            songClassifier.displayPlayList(mood);
                        }
                        else{
                            songClassifier.specific_displayPlayList(mood, numSongs);
                        }
                    }
                }
                    //runs if the user selected relaxed
                else if(mood == "relaxed"){
                    //personalized message for sad mood gets printed
                    cout << "Sounds like you're in a peaceful state of mind! "
                            "\nDo you want all recommended songs or a certain amount?" << endl;
                    cout << "\t* Type 0 for all, or the number of desired songs for your playlist *" << endl;

                    //the num of songs the user selected is read into the variable
                    cin >> numSongs;

                    //add relaxed songs to hashmap if user chose hashmap
                    if(data_type == "m"){songs = readMapper.AddtoMapRelaxed(data1);}
                    //add relaxed songs to hashset if user chose hashset
                    if(data_type == "s"){
                        //the proper functions are called depending on the num of songs the user selected for their playlist
                        if(numSongs == 0){
                            songClassifier.displayPlayList(mood);
                        }
                        else{
                            songClassifier.specific_displayPlayList(mood, numSongs);
                        }
                    }
                }

                // Validate input for decision
                if (cin.fail() || numSongs < 0) {
                    throw invalid_argument("Invalid input for decision. Please enter a non-negative integer.");
                }

//               if(decision > slay.size()){ //FIXME if user inputs size larger than set available
//                   throw invalid_argument("Requested value exceeds number of songs available for that mood. "
//                                           "Max input: ("+to_string(slay.size())+").");
//                }

                //the folowing code prints the playlist for the hasmap choice

                /*NOTE: the functions set up in the hashset implementation had a backend function that
                 * displays the playlist so if hashset is selected then the previous if else statements
                 * take care of the printing*/

                cout << "MoodyTune lOaDiNg ~~~~~~~" << endl;
                cout << "Displaying playlist for mood: " << mood << endl;

                if(data_type == "m") {
                    //print the entire map of songs (Jades implementation)
                    if(numSongs == 0){
                        //range based for loop to print the whole map
                        for (auto& list : songs.getData()) {
                            for (auto& pair : list) {
                                string tracknum = pair.first;
                                vector<string> values = pair.second;
                                // Print out the track number and its associated data
                                std::cout << "Artist and Track: " << values[0] << " - " << values[1] << std::endl;
                            }
                        }
                    }
                        //prints the specified amount of songs
                    else{
                        //uses a count variable to keep track of the num of loops
                        int count =0;
                        //loops through the hashmap until the count value is <= the num of songs the user selected
                        for (auto& list : songs.getData()) {
                            for (auto& pair : list) {
                                if(count >= numSongs){
                                    break;
                                }
                                string tracknum = pair.first;
                                vector<string> values = pair.second;
                                // Print out the track number and artists
                                std::cout << "Song Name: " << values[1]  << ", "<< "Artist: " << values[0] << std::endl;

                                //increase count
                                count++;
                            }
                            //once the value reaches the desired num of songs break out of loop
                            if(count >= numSongs){
                                break;
                            }
                        }
                    }
                }
            } else { //runs if inproper mood was entered by user
                throw invalid_argument("Invalid mood input. Please enter a valid mood.");
            }

            int go_again = 0;
            cout << "Do you want another playlist? Press 1 if yes..." << endl;
            cin >> go_again;

            // Validate input for `go_again`
            if (cin.fail() || (go_again != 1 && go_again != 0)) {
                throw invalid_argument("Invalid input for go again. Please enter 1 for yes or 0 for no.");
            }

            moodytune = (go_again == 1);


        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;

            // Clear the input buffer in case of an error
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Let's try again!" << endl;
        } catch (const exception& e) {
            cout << "Unexpected error: " << e.what() << endl;
            break;
        }
    }

    return 0;
}
