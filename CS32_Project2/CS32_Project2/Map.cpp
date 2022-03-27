//Final Submission, FINAL
//
//  Map.cpp
//  CS32_Project2
//
//  Created by Philip Huang on 1/22/22.
//

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map(){
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}
// Create an empty map (i.e., one with no key/value pairs)

Map::~Map(){
    if (!this->empty()){ // can be a one or more element list
        Node* cur = head;
        Node* nxt;
        while (cur != nullptr){
            nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    //if Map is empty, nothing to delete
}
//Destructor
//When a Map is destroyed, the nodes in the linked list must be deallocated.

Map::Map(const Map& other){
    if (other.empty()){ //if other is empty, we want this map to be empty as well
        m_size = 0;
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    //other is one or more element list
    //reset the map
    m_size = 0;
    head = nullptr; //set this->head = nullptr;
    tail = nullptr; //set this->tail = nullptr;

    Node* cur = other.head; //oth
    while (cur != nullptr){
        this->insert(cur->m_key,cur->m_value);
        cur = cur->next;
    }
}
//copy constructor
//When a brand new Map is created as a copy of an existing Map, enough new nodes must be allocated to hold a duplicate of the original list.
Map& Map::operator=(const Map& rhs){
    if (this != &rhs) //checks that this and rhs aren't the same Map
    {
        Map temp(rhs); //create a copy of rhs
        this->swap(temp); //swap rhs with this Map
    } //temp goes away as Map destructor is called
    return *this; //return the contents of this, which is a Map
}
//assignment operator
//When an existing Map (the left-hand side) is assigned the value of another Map (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).

bool Map::empty() const{
    if (head == nullptr && tail == nullptr && m_size == 0){
        return true;
    }
    return false;
}
// Return true if the map is empty, otherwise false.

int Map::size() const{
    return m_size;
}
// Return the number of key/value pairs in the map.

bool Map::insert(const KeyType& key, const ValueType& value){
    if (this->empty()){ //if list is empty, add the node with key value
        //dynamicallly allocate new Node
        Node* newNode = new Node;
        
        //Set node values
        newNode->m_key = key;
        newNode->m_value = value;
        
        //Set the next and previous element of newNode to nullptr
        newNode->next = nullptr;
        newNode->prev = nullptr;
        
        //The head and tail pointers will point to this newNode
        head = newNode;
        tail = newNode;
        
        //the size of list just grew by one
        m_size++;
        
        return true;
    }
    else{ //list is not empty, list contains >= 1 element, cases could be one element, or multiple elements
        Node* cur = head;
        while (cur->next != nullptr){ //gets cur to point to the last node in before list
            if (cur->m_key == key){
                return false; // if key already exists, do nothing
            }
            cur = cur->next;
        }
        //if one element list, cur will be pointing to head
        //if multi-element list, cur will be pointing to last existing node in list
        
        //if cur is last node in list, but key is equal, we will return false
        if (cur->m_key == key){
            return false;
        }
        
        //key does not exist in list, we should add it
        Node* newNode = new Node; //dynamically allocate a new Node
        
        newNode->m_key = key;
        newNode->m_value = value; //set values of Node
        
//        cur->next = newNode; //want the last node to point at the newNode address
//        newNode->prev = cur; //set the newNode to cur, which is last node in before list
//        newNode->next = nullptr; //set the newNode next pointer to point to nullptr to signify end
//        tail = cur->next; //tail will point to newNode, could also do tail = newNode
//
//        m_size++; //the size of linked list increased by one
//        return true;
//        //THIS INSERTS ELEMENTS NOT BY SORTED KEY ORDER, will take O(N^2) laster on for get(i,key,value) function
//
        //If we want list to be SORTED, new node might not be inserted at the end of doubly linked list
        //we have cur pointed at last element in list, will need this to set tail
        Node* check = head;
        while(check != nullptr){
            if (newNode->m_key < check->m_key){
                break;
            }
            check = check->next;
        }
        //check is now pointing to the key that is greater than newNodes key, we want to insert newNode before check's key
        if(check == nullptr){ //if check falls off, that means we can insert newNode at the end of list
            cur->next = newNode;
            newNode->prev = cur;
            newNode->next = nullptr;
            tail = cur->next; //tail = newNode
            m_size++;
            return true;
        }
        if(check == cur){ // if check is the same as cur, we want newNode to be before cur==check
            if (m_size == 1){
                head = newNode;
                tail = cur;
                newNode->prev = nullptr;
                newNode->next = cur;
                cur->prev = head;
                m_size++;
                return true;
            }
            check->prev->next = newNode;
            newNode->prev = cur->prev;
            newNode->next = cur;
            cur->prev = newNode;
            tail = cur;
            m_size++;
            return true;
        }
        //NEED TO CHECK FOR ONE ELEMENT LIST OR IF NODE IS INSERTED IN FRONT END
        
        //check is before cur, the last node in list
        if(check == head){ //if we want to insert at front of list
            newNode->prev = nullptr;
            newNode->next = check;
            check->prev = newNode;
            tail = cur; // unnecessary
            head = newNode;
            m_size++;
            return true;
        }
        
        Node* prev = check->prev;
        prev->next = newNode;
        newNode->prev = prev;
        newNode->next = check;
        check->prev = newNode;
        tail = cur; //unnecessary
        m_size++;
        return true;
    }
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full.

bool Map::update(const KeyType& key, const ValueType& value){
    if (this->empty()){ //if list is empty
        return false;
    }
    Node* cur = head;
    while(cur!=nullptr){
        if (cur->m_key == key){
            cur->m_value = value;
            return true;
        }
        cur = cur->next;
    }
    return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if (this->empty()){ //if list is empty, we want to insert node
        return insert(key,value);
    }
    if (update(key,value)){
        return true;
    }
    //Now way key is in Map since update returned false
    //insert node at the end, NOT ANYMORE <- insert node by sorted key value
    return insert(key,value);
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).

bool Map::erase(const KeyType& key){
    Node* cur = head;
    while(cur != nullptr){
        if (cur->m_key == key){
            if (m_size == 1){ //works for size 1 list
                m_size = 0;
                delete cur;
                head = nullptr;
                tail = nullptr;
                return true;
            }
            if (cur == head){ //size >= 2, there will be a node after cur
                cur->next->prev = nullptr;
                head = cur->next;
                delete cur;
                m_size--;
                return true;
            }
            if (cur == tail){ //size >= 2, there will be a node before cur
                cur->prev->next = nullptr;
                tail = cur->prev;
                delete tail;
                m_size--;
                return true;
            }
            //if the cur element is not the first or last node in list, it must be in the middle
            //then we don't have to worry about following a null pointer
            Node* nxt = cur->next; //works for if element is not first or last element in list
            cur->prev->next = nxt;
            nxt->prev = cur->prev;
            delete cur;
            m_size--;
            return true;
        }
        cur = cur->next;
    }
    return false; //for empty list, head will be nullptr, so it will not run inside while loop
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const{
    Node* cur = head;
    while(cur != nullptr){
        if (cur->m_key == key){
            return true;
        }
        cur = cur->next;
    }
    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const{
    if (this->contains(key)){
        Node* cur = head;
        while (cur != nullptr){
            if (cur->m_key == key){
                value = cur->m_value;
                return true;
            }
            cur = cur->next;
        }
    }
    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if (i >= m_size || i < 0){
        return false;
    }
//    if (i==0){
//        key = head->m_key;
//        value = head->m_value;
//        return true;
//    }
    int count = i; //could just use i, but count is more readable
    Node* cur = head;
    while(count>0){
        cur=cur->next;
        count--;
    }
    key = cur->m_key;
    value = cur->m_value;
    return true;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.

void Map::swap(Map& other){
    // Swap sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
    
    // Swap the head tail pointers to doubly linked lists.
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;

    Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
    

}

void Map::dump() const{
    cerr << "\n";
    Node* cur = this->head;
    int count = 1;
    //should replace i here with ptr for clarity
    for(Node* i = cur; i != nullptr; i=i->next){
        cerr << count << " Key: " << i->m_key << " " << "Value: " << i->m_value;
        cerr << " Address of Key: " << &i->m_key << "  Address of Value: " << &i->m_value;
        cerr << "\n";
        count++;
    }
    cerr << "------------------------------";
    cerr << "\n";
}

bool merge(const Map& m1, const Map& m2, Map& result){
    //Can't assume result is a empty map, got to make it one
    //First check if result is the same as m1 or m2
    if (&result == &m1 || &result == &m2){
        Map temp = Map();
        bool isTrue = true;
        for (int i=0; i<m1.size(); i++){
            KeyType key;
            ValueType value;
            m1.get(i,key,value);
            if (!m2.contains(key)){
                temp.insert(key,value);
            }
            else if (m2.contains(key)){
                ValueType valueToCheck;
                m2.get(key, valueToCheck);
                if (value == valueToCheck){
                    temp.insert(key,value);
                    continue;
                }
                isTrue = false;
            }
        }
        
        for (int j=0; j<m2.size(); j++){
            KeyType key;
            ValueType value;
            m2.get(j,key,value);
            if (!m1.contains(key)){
                temp.insert(key,value);
            }
            else if (m1.contains(key) && !temp.contains(key)){
                ValueType valueToCheck;
                m1.get(key, valueToCheck);
                if (value == valueToCheck){
                    temp.insert(key,value);
                    continue;
                }
                isTrue = false;
            }
        }
        result = temp;
        return isTrue;
    }
    
    //result is not the same as m1 or m2, we can clear it
    result = Map();
    bool isTrue = true;
    for (int i=0; i<m1.size(); i++){
        KeyType key;
        ValueType value;
        m1.get(i,key,value);
        if (!m2.contains(key)){
            result.insert(key,value);
        }
        else if (m2.contains(key)){
            ValueType valueToCheck;
            m2.get(key, valueToCheck);
            if (value == valueToCheck){
                result.insert(key,value);
                continue;
            }
            isTrue = false;
        }
    }
    
    for (int j=0; j<m2.size(); j++){
        KeyType key;
        ValueType value;
        m2.get(j,key,value);
        if (!m1.contains(key)){
            result.insert(key,value);
        }
        else if (m1.contains(key) && !result.contains(key)){
            ValueType valueToCheck;
            m1.get(key, valueToCheck);
            if (value == valueToCheck){
                result.insert(key,value);
                continue;
            }
            isTrue = false;
        }
    }
    return isTrue;
        
    
}

void reassign(const Map& m, Map& result){
    if(&m == &result){ //if m is the same as result in memory (aliasing), then we want to create a new key value pair map and point result to that new map;
        if (m.size() == 1){ //if M has one element, no reassigning
            Map temp(m);
            result = temp;
            return;
        }
        if (m.empty()){ //if M is empty, no reassigning
            Map temp = Map();
            result = temp;
            return;
        }
        Map temp = Map();
        int prevIndex = 0;
        for (int curIndex=1; curIndex<m.size(); curIndex++){
            KeyType prevKey;
            ValueType prevValue;
            KeyType curKey;
            ValueType curValue;
            m.get(prevIndex,prevKey,prevValue);
            m.get(curIndex,curKey,curValue);
            temp.insertOrUpdate(curKey, prevValue);
            prevIndex++;
        }
        KeyType lastKey;
        ValueType lastValue;
        KeyType firstKey;
        ValueType firstValue;
        m.get(m.size()-1,lastKey,lastValue);
        m.get(0,firstKey,firstValue);
        temp.insertOrUpdate(firstKey,lastValue);
        
        result = temp;
        return;
    }
    //&m != &result
    if (m.size() == 1){ //if M has one element, no reassigning
        Map temp(m);
        result = temp;
        return;
    }
    if (m.empty()){ //if M is empty, no reassigning
        result = Map();
        return;
    }
    result = Map();
    int prevIndex = 0;
    for (int curIndex=1; curIndex<m.size(); curIndex++){
        KeyType prevKey;
        ValueType prevValue;
        KeyType curKey;
        ValueType curValue;
        m.get(prevIndex,prevKey,prevValue);
        m.get(curIndex,curKey,curValue);
        result.insertOrUpdate(curKey, prevValue);
        prevIndex++;
    }
    KeyType lastKey;
    ValueType lastValue;
    KeyType firstKey;
    ValueType firstValue;
    m.get(m.size()-1,lastKey,lastValue);
    m.get(0,firstKey,firstValue);
    result.insertOrUpdate(firstKey,lastValue);
    
}
