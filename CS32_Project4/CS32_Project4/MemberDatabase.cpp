//
//  MemberDatabase.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//

#include "MemberDatabase.h"
#include <fstream>
#include <sstream>

MemberDatabase::MemberDatabase(){};

MemberDatabase::~MemberDatabase(){
    cout << "MDB Destructor called" << endl;
    std::vector<PersonProfile*>::iterator it = m_people.begin();
//        for (it = m_people.begin(); it!=m_people.end();it++){
//            delete *(it);
//        }
    while(it!=m_people.end()){
//            cout << "DELETE" << endl;
        delete *(it);
        it++;
    }
}

bool MemberDatabase::LoadDatabase(std::string filename){

    ifstream file(filename);
    string line;

    if (!file){
        cout << "Could not open file." << "\n";
        return false;
    }
    int count = 0;
    while(getline(file, line)){ //and count < 20){

        string name;
        string email;
        int numOfAttVals;
        
        istringstream iss(line);
        getline(iss,name);
        
        getline(file,line);
        iss = istringstream(line);
        getline(iss,email);

        PersonProfile* personPtr = new PersonProfile(name,email);

        getline(file,line);
        iss=istringstream(line);
        iss>>numOfAttVals; //converts string to integer
        
//        cout << "Name: " << name << endl;
//        cout << "Email: " << email << endl;
//        cout << "NumofAttVals: "<< numOfAttVals <<endl;
        
        for (int i=0; i < numOfAttVals; i++){
            string att;
            string val;
            iss = istringstream(line);
            getline(file,att,',');
            getline(file,val,'\n');
            
            personPtr->AddAttValPair(AttValPair(att,val));
            
//            cout << "Attribute: " << att <<" Value: " << val <<endl;
            
            string key = att+","+val;
            std::set<std::string>* emailMatches = m_attvalpairsToEmails.search(key);
            if (emailMatches == nullptr){
                std::set<std::string> newEmailMatch;
                newEmailMatch.insert(email);
                m_attvalpairsToEmails.insert(key,newEmailMatch);
            }
            else if (emailMatches!=nullptr){
                emailMatches->insert(email);
            }
            
        }
        
//        cout << "INSERTED EMAIL: " << email <<endl;
//        if (email == "CoRoll3@aim.com") cout << "Found this man" << endl;
        m_people.push_back(personPtr);
//        m_emailsToMembers.insert(email, m_people);

        m_emailsToMembers.insert(email, personPtr);
        
        m_emails.insert(email);
        count++;
        if (m_emails.size() != count){
//            delete personPtr;
            return false;}
        
        //Gets rid of white space gap
        string junk;
        getline(file,junk);

//        cout << endl;
        
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {//const{
    std::string key = string(input.attribute + "," + input.value);
    std::set<std::string>* my_emails = m_attvalpairsToEmails.search(key);
    if (my_emails == nullptr){
        return std::vector<std::string>();
    }
    else{
        std::vector<std::string> emails(my_emails->begin(), my_emails->end());
        return emails;
    }
   
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {//const{
    if (m_emailsToMembers.search(email) == nullptr){
//        cout <<"dsfsdfsd"<<endl;
        return nullptr;
    }
    else{
//        PersonProfile* ptr = *(m_emailsToMembers.search(email));
//        return ptr;
//        cout << "EMAIL TO BE SEARCHED: " << email << endl;
        return *(m_emailsToMembers.search(email));
    }
}





//RadixTree<PersonProfile*> MemberDatabase::GetDatabase(std::string filename) const {
//
//    ifstream file(filename);
//    string line;
//
//
//    int count = 0;
//    while(getline(file, line)){ //and count < 20){
//
//        string name;
//        string email;
//        int numOfAttVals;
//        
//        istringstream iss(line);
//        getline(iss,name);
//        
//        getline(file,line);
//        iss = istringstream(line);
//        getline(iss,email);
//
//        PersonProfile* personPtr = new PersonProfile(name,email);
//
//        getline(file,line);
//        iss=istringstream(line);
//        iss>>numOfAttVals; //converts string to integer
//        
////        cout << "Name: " << name << endl;
////        cout << "Email: " << email << endl;
////        cout << "NumofAttVals: "<< numOfAttVals <<endl;
//        
//        for (int i=0; i < numOfAttVals; i++){
//            string att;
//            string val;
//            iss = istringstream(line);
//            getline(file,att,',');
//            getline(file,val,'\n');
//            
//            personPtr->AddAttValPair(AttValPair(att,val));
//            
////            cout << "Attribute: " << att <<" Value: " << val <<endl;
//            
//            string key = string(att+','+val);
//            std::set<std::string>* emailMatches = m_attvalpairsToEmails.search(key);
//            if (emailMatches == nullptr){
//                std::set<std::string> newEmailMatch;
//                newEmailMatch.insert(email);
//                m_attvalpairsToEmails.insert(key,newEmailMatch);
//            }
//            else if (emailMatches!=nullptr){
//                emailMatches->insert(email);
//            }
//            
//        }
//        
////        cout << "INSERTED EMAIL: " << email <<endl;
////        if (email == "CoRoll3@aim.com") cout << "Found this man" << endl;
//        m_emailsToMembers.insert(email, personPtr);
//        m_people.push_back(personPtr);
//        
//        m_emails.insert(email);
//        count++;
//        
//        //Gets rid of white space gap
//        string junk;
//        getline(file,junk);
//
////        cout << endl;
//        
//    }
//    return m_emailsToMembers;
//}


