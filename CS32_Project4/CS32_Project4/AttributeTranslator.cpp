//
//  AttributeTranslator.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//

#include "AttributeTranslator.h"
#include <fstream>
#include <sstream>
#include <set>
#include "utility.h"

using namespace std;

AttributeTranslator::AttributeTranslator(){};
AttributeTranslator::~AttributeTranslator(){
    cout << "AT Destructor called" << endl;
};

bool AttributeTranslator::Load(std::string filename){
    
    ifstream file(filename);
    string line;

    if (!file){
        cout << "Could not open file." << "\n";
        return false;
    }
    while(getline(file, line)){
        
//        cout << line << endl;
        istringstream iss(line);
        string source_a;
        string source_v;
        string compatible_a;
        string compatible_v;
        getline(iss,source_a,',');
        getline(iss,source_v,',');
        getline(iss,compatible_a,',');
        getline(iss,compatible_v,',');
//        cout << "Source a: "<< source_a <<endl;
//        cout << "Source v: "<< source_v << endl;
//        cout << "Compatible a: "<< compatible_a << endl;
//        cout << "Compatible v: "<< compatible_v <<endl;
        string key = source_a+","+source_v;
        AttValPair value = AttValPair(compatible_a,compatible_v);
        
//        if ((*(m_RadixTree.search(key))).size() != 0){
        if (m_RadixTree.search(key) != nullptr){
            m_RadixTree.search(key)->push_back(value);
        }
        else{
            std::vector<AttValPair> avec = std::vector<AttValPair>();
            avec.push_back(value);
            m_RadixTree.insert(key,avec);
        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{ //const {//UNCOMMENT CONST
    std::string key = source.attribute + "," + source.value;
    if (m_RadixTree.search(key)!=nullptr){ //if attvalpair already exists
        std::set<AttValPair> m_set(m_RadixTree.search(key)->begin(),m_RadixTree.search(key)->end());
        std::vector<AttValPair> m_vector(m_set.begin(),m_set.end());
        return m_vector;
//        std::vector<AttValPair> m_vector(m_RadixTree.search(key)->begin(),m_RadixTree.search(key)->end());
//        return m_vector;
    }
    else{
        return vector<AttValPair>();
    }
}
