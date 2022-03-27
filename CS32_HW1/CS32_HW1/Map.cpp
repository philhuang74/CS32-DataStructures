//
//  Map.cpp
//  CS32_HW1
//
//  Created by Philip Huang on 1/14/22.
//

#include "Map.h"
#include <iostream>

Map::Map(){
    m_size = 0;

}

bool Map::empty() const{
    if (m_size == 0){
        return true;
    }
    else{
        return false;
    }
}  // Return true if the map is empty, otherwise false.

int Map::size() const {
    return m_size;
}    // Return the number of key/value pairs in the map.

bool Map::insert(const KeyType& key, const ValueType& value){ //###Should we use setKeyValue to be pass by copy?
    if (m_size >= DEFAULT_MAX_ITEMS){
        return false;
    }
    for (int i = 0; i < m_size; i++){
        if (m_keyValuePairs[i].getKey() == key){
            return false;
        }
    }
    m_keyValuePairs[m_size].setKeyValue(key,value);
    m_size++;
    return true;
}
  // If key is not equal to any key currently in the map, and if the
  // key/value pair can be added to the map, then do so and return true.
  // Otherwise, make no change to the map and return false (indicating
  // that either the key is already in the map, or the map has a fixed
  // capacity and is full).

bool Map::update(const KeyType& key, const ValueType& value){
    for (int i=0; i < m_size; i++){
        if (m_keyValuePairs[i].getKey() == key){
            m_keyValuePairs[i].setKeyValue(key,value);
            return true;
        }
    }
    return false;
}
  // If key is equal to a key currently in the map, then make that key no
  // longer map to the value that it currently maps to, but instead map to
  // the value of the second parameter; return true in this case.
  // Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if (this->update(key,value)){
        return true;
    }
    if (this->insert(key,value)){
        return true;
    }
    else{
        return false;
    }
}
  // If key is equal to a key currently in the map, then make that key no
  // longer map to the value that it currently maps to, but instead map to
  // the value of the second parameter; return true in this case.
  // If key is not equal to any key currently in the map and if the
  // key/value pair can be added to the map, then do so and return true.
  // Otherwise, make no change to the map and return false (indicating
  // that the key is not already in the map and the map has a fixed
  // capacity and is full).

bool Map::erase(const KeyType& key){
    int keyLocation = -1;
    for (int i=0; i < m_size; i++){
        if (m_keyValuePairs[i].getKey() == key){
            keyLocation = i;
            break;
        }
    }
    if (keyLocation != -1){
        for(int i = keyLocation; i<m_size-1;i++){
            m_keyValuePairs[i] = m_keyValuePairs[i+1];
        }
        m_size--;
        return true;
    }
    else{
        return false;
    }
}
  // If key is equal to a key currently in the map, remove the key/value
  // pair with that key from the map and return true.  Otherwise, make
  // no change to the map and return false.

bool Map::contains(const KeyType& key) const{
    for (int i = 0; i < m_size; i++){
        if (m_keyValuePairs[i].getKey() == key){
            return true;
        }
    }
    return false;
}
  // Return true if key is equal to a key currently in the map, otherwise
  // false.

//bool Map::get(const KeyType& key, ValueType& value){
//    if (this->contains(key)){
//        this->update(key,value);
//        return true;
//    }
//    return false;
//}
//  // If key is equal to a key currently in the map, set value to the
//  // value in the map which that key maps to, and return true.  Otherwise,
//  // make no change to the value parameter of this function and return
//  // false.

bool Map::get(const KeyType& key, ValueType& value) const{
    if (this->contains(key)){
        for (int i = 0; i < m_size; i++){
            if (m_keyValuePairs[i].getKey() == key){
                value = m_keyValuePairs[i].getValue();
            }
        }
        return true;
    }
    return false;
}

// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if (0 <= i && i <m_size){
        int count = 0;
        int currItem = 0;
        while (currItem < m_size){
            for (int i=0; i<m_size;i++){
                if (m_keyValuePairs[currItem].getKey() > m_keyValuePairs[i].getKey()){
                    count++;
                }
            }
            if (count == 0 && i == 0){
                key = m_keyValuePairs[currItem].getKey();
                value = m_keyValuePairs[currItem].getValue();
                return true;
            }
            if (count == i){
                key = m_keyValuePairs[currItem].getKey();
                value = m_keyValuePairs[currItem].getValue();
                return true;
            }
            count = 0;
            currItem ++;
        }
//        if (count == 0){
//            key = m_keyValuePairs[currItem].getKey();
//            value = m_keyValuePairs[currItem].getValue();
//            return true;
//        }
        return false;
    }
    return false;
}
  // If 0 <= i < size(), copy into the key and value parameters the
  // key and value of the key/value pair in the map whose key is strictly
  // greater than exactly i keys in the map and return true.  Otherwise,
  // leave the key and value parameters unchanged and return false.

void Map::swap(Map& other){
    Map temp = *this;
    *this = other;
    other = temp;
}
  // Exchange the contents of this map with the other one.

void Map::dump() const{
    cerr << "\n";
    for(int i = 0; i < m_size; i++){
        cerr << i << " Key: " << m_keyValuePairs[i].getKey() << " " << m_keyValuePairs[i].getValue();
        cerr << "\n";
    }
    cerr << "------------------------------";
    cerr << "\n";
}

KeyType Map::KeyValuePair::getKey() const {
        return m_Key;
};
ValueType Map::KeyValuePair::getValue() const{
    return m_Value;
};
void Map::KeyValuePair::setKeyValue(const KeyType& key, const ValueType& value) {
    m_Key = key;
    m_Value = value;
};


