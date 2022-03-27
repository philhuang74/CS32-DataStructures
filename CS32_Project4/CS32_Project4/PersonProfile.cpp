//
//  PersonProfile.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
#include <iostream>
#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name , std::string email){
    m_name = name;
    m_email = email;
}

PersonProfile::~PersonProfile(){
    cout << "PP Destructor called" << endl;
//        cout << m_name << " deleted" << endl;
};

std::string PersonProfile::GetName() const{
    return m_name;
}
std::string PersonProfile::GetEmail() const{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval){
    if (m_RadixTree.search(attval.attribute) == nullptr){ //attval does not exist in person's profile
        m_RadixTree.insert(attval.attribute, attval.value); //insert this new attribute value pair into radix tree
        m_attValPairs.push_back(attval); //add this new unique attvalpair to our vector
    }
    else{ //attval attribute already exists in person's profile
        //do nothing if the corresponding value exists
        if (*(m_RadixTree.search(attval.attribute)) == attval.value){}
        else{ //attval value does not exist
            m_RadixTree.insert(attval.attribute, attval.value); //insert this new attribute value pair into radix tree
            m_attValPairs.push_back(attval); //add this new unique attvalpair to our vector
        }
    }
}

int PersonProfile::GetNumAttValPairs() const{
    return m_attValPairs.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if (0 <= attribute_num and attribute_num < m_attValPairs.size()){
        attval = m_attValPairs[attribute_num];
        return true;
    }
    else{
        return false;
    }
}
