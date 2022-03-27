//
//  MemberDatabase.hpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//

#include <iostream>
#include "RadixTree.h"
#include "provided.h"
#include "PersonProfile.h"
#include <set>
#include "utility.h"
#include <vector>
using namespace std;

#ifndef MemberDatabase_hpp
#define MemberDatabase_hpp

class MemberDatabase{
public:
    MemberDatabase();//{};
    ~MemberDatabase();//{
//        std::vector<PersonProfile*>::iterator it = m_people.begin();
////        for (it = m_people.begin(); it!=m_people.end();it++){
////            delete *(it);
////        }
//        while(it!=m_people.end()){
////            cout << "DELETE" << endl;
//            delete *(it);
//            it++;
//        }
//    };
    
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const; //const; //UNCOMMENT CONST
//    const PersonProfile* GetMemberByEmail(std::string email) const;
    const PersonProfile* GetMemberByEmail(std::string email) const; //UNCOMMENT CONST
    
//    RadixTree<PersonProfile*> GetDatabase(std::string filename) const;
    
private:
    RadixTree<PersonProfile*> m_emailsToMembers; //Need to make pointers to personprofiles or else they get deleted after loadDatabase function. Using pointers give us the freedom to manually delete it afterwards
    RadixTree<std::set<std::string>> m_attvalpairsToEmails;
    std::vector<PersonProfile*> m_people;
    std::set<std::string> m_emails;
};

#endif /* MemberDatabase_hpp */
