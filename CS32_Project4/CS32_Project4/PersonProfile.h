//
//  PersonProfile.hpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//

#include <iostream>
#include "provided.h"
#include <vector>
#include "RadixTree.h"
using namespace std;

#ifndef PersonProfile_hpp
#define PersonProfile_hpp

class PersonProfile{
public:
    PersonProfile(std::string name , std::string email);//{
//        m_name = name;
//        m_email = email;
//    }
    ~PersonProfile();//{
//        cout << m_name << " deleted" << endl;
    //};
    std::string GetName() const;//{
//        return m_name;
//    }
    std::string GetEmail() const;//{
//        return m_email;
//    }
    void AddAttValPair(const AttValPair& attval);//{
//        if (m_RadixTree.search(attval.attribute) == nullptr){ //attval does not exist in person's profile
//            m_RadixTree.insert(attval.attribute, attval.value); //insert this new attribute value pair into radix tree
//            m_attValPairs.push_back(attval); //add this new unique attvalpair to our vector
//        }
//        else{ //attval attribute already exists in person's profile
//            //do nothing if the corresponding value exists
//            if (*(m_RadixTree.search(attval.attribute)) == attval.value){}
//            else{ //attval value does not exist
//                m_RadixTree.insert(attval.attribute, attval.value); //insert this new attribute value pair into radix tree
//                m_attValPairs.push_back(attval); //add this new unique attvalpair to our vector
//            }
//        }
//        //Another way to think about it, but since the spec states attribute to values for Radix Tree
//        //Search for attribute, is it in there
//        //if so, insert into set
//        //if not, create a set insert the set into radixtree
//
//
//    } //LETS use a set for this
    
    int GetNumAttValPairs() const;//{
//        return m_attValPairs.size();
//    }

    bool GetAttVal(int attribute_num, AttValPair& attval) const;//{
//        if (0 <= attribute_num and attribute_num < m_attValPairs.size()){
//            attval = m_attValPairs[attribute_num];
//            return true;
//        }
//        else{
//            return false;
//        }
//    }
private:
    std::string m_name;
    std::string m_email;
    std::vector<AttValPair> m_attValPairs;
    RadixTree<std::string> m_RadixTree;

};

//use set
//define comparison operator

#endif /* PersonProfile_hpp */
