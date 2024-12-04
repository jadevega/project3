#include <map>
using namespace std;
#include<iomanip>
#include <string>
#include<vector>
#include <iostream>
#include "song_object.h"
#include <list>

using namespace std;

#ifndef UNTITLED1_READANDMAP_H
#define UNTITLED1_READANDMAP_H

template<typename K, typename V>
class HashTable {
private:
    static const int INI_TABLE_SIZE = 150;
    vector<list<pair<K, V>>> data;
    int indexFunction(K key);
    void rehashtab();
    int TABLE_SIZE;
    float loadmax;
    int num = 0;

public:
    HashTable(int initial = INI_TABLE_SIZE, float loadmax = .8)
            : TABLE_SIZE(initial), loadmax(loadmax), num(0) {
        data.resize(TABLE_SIZE);
    }
    int getTable() const;
    const vector<list<pair<K, V>>>getData() const;
    void insert(K key, V value);
    bool getvec(K key, V& value);
    bool checkifhas(K key);
    int size() const;
    float ldf() const;
};


template<typename K, typename V>
int HashTable<K, V>::indexFunction(K key) {
    int index = 0;
    int prime = 31;
    for (char c : key) {
        index = index * prime + c;
    }
    return index % TABLE_SIZE;
}

template<typename K, typename V>
void HashTable<K, V>::insert(K key, V value) {

    if (ldf() > loadmax) {
        rehashtab();
    } else {
        int index = indexFunction(key);
        for (auto& pair : data[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        data[index].emplace_back(key, value);
        num++;
    }
}

template<typename K, typename V>
bool HashTable<K, V>::getvec(K key, V& value) {
    int index = indexFunction(key);
    for (const auto& pair : data[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::checkifhas(K key) {
    int index = indexFunction(key);
    for (const auto& pair : data[index]) {
        if (pair.first == key) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
int HashTable<K, V>::size() const {
    return num;
}


template<typename K, typename V>
float HashTable<K, V>::ldf() const {
    return static_cast<float>(num) / TABLE_SIZE;
    }

template<typename K, typename V>
const vector<list<pair<K, V>>>HashTable<K,V>::getData() const{
    return data;
}

template<typename K, typename V>
int HashTable<K,V>::getTable() const {
    return TABLE_SIZE;
}



template<typename K, typename V>
void HashTable<K,V>::rehashtab(){
    int newtab = TABLE_SIZE * 2;
    TABLE_SIZE = newtab;
    vector<list<pair<K,V>>> newData(newtab);

    for(auto elem : data){
        for(auto pair: elem){
            int newIndex = indexFunction(pair.first) % newtab;
            newData[newIndex].push_back(pair);
        }
    }
    data = std::move(newData);

}


class readandmap {

private:
    HashTable<string,vector<string>>data1;


public:
    //map
    HashTable<string, vector<string>> ReadFileMap(const string& filename);
    HashTable<string,vector<string>>AddtoMapHappy(const HashTable<string, vector<string>>&data1);
    HashTable<string,vector<string>>AddtoMapSad(const HashTable<string, vector<string>>&data1);
    HashTable<string,vector<string>>AddtoMapEnergetic(const HashTable<string, vector<string>>&data1);
    HashTable<string,vector<string>>AddtoMapRelaxed(const HashTable<string, vector<string>>&data1);
    string readCSVField(stringstream &ss);

    //set
    void ReadFileSet(const string& filename, vector<SongObject::Song>& songs);

};


#endif //UNTITLED1_READANDMAP_H
