//
//  MatchMaker.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/5/22.
//

#include "MatchMaker.h"
#include "PersonProfile.h"
#include <set>
#include "utility.h"
#include <map>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){ //UNCOMMENT CONST
    m_mdb = &mdb;
    m_at = &at;
    
}; //constructor

//const MemberDatabase* MatchMaker::getMemberDatabase(){
//    return m_mdb;
//}


MatchMaker::~MatchMaker(){
    cout << "Matchmaker Destructor called" << endl;
};


//    email -> (Member database) personprofiel -> PersonProfile getattval attirbute value pairs -> (AttributeTranslator) compatible attvalpair in a set iterate over this set (MemberDatabase) radixtree attvalpairs to email map number strings emails to ints count set emailcount to vector sorted
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{//const{ //UNCOMMENT CONST
    
    //Get the person by email
    const PersonProfile* person = m_mdb->GetMemberByEmail(email);
    std::vector<AttValPair> m_sourceAttValPairs;
    std::vector<AttValPair> m_compatibleAttValPairs;
    if (person!=nullptr){
        for (int i = 0; i < person->GetNumAttValPairs(); i++){
            AttValPair attval;
            person->GetAttVal(i, attval);
            m_sourceAttValPairs.push_back(attval);
        }
        
        //loop through the source AttValPairs and pushback all the compatible pairs
        std::vector<AttValPair>::iterator source_it;
        for (source_it = m_sourceAttValPairs.begin(); source_it != m_sourceAttValPairs.end();source_it++){
            std::vector<AttValPair> compatible = m_at->FindCompatibleAttValPairs(*source_it);
            std::vector<AttValPair>::iterator compatible_it;
            for (compatible_it = compatible.begin(); compatible_it!=compatible.end();compatible_it++){
                m_compatibleAttValPairs.push_back(*compatible_it);
            }
        }
        
        //get the unique compatible pairs and loop through it to find matching members
        std::vector<std::string> m_matches;
         std::set<AttValPair> m_uniqueCompatibleAttValPairs(m_compatibleAttValPairs.begin(),m_compatibleAttValPairs.end());
        std::set<AttValPair>::iterator set_it;
        for (set_it = m_uniqueCompatibleAttValPairs.begin();set_it!=m_uniqueCompatibleAttValPairs.end();set_it++){
//        std::vector<AttValPair>::iterator set_it;
//        for (set_it = m_compatibleAttValPairs.begin();set_it!=m_compatibleAttValPairs.end();set_it++){
            std::vector<std::string> matching_members = m_mdb->FindMatchingMembers(*set_it); //gets the Emails
            std::vector<std::string>::iterator member_it;
            for (member_it = matching_members.begin(); member_it != matching_members.end(); member_it++){
//                if (*member_it == email){}
//                else{
//                    m_matches.push_back(*member_it);
//                }
                m_matches.push_back(*member_it);
            }
        }
        
        //Now we look at emailcounts of all the matches.
        std::map<std::string,int> m_emailCounts;
        std::vector<std::string>::iterator email_it;
        for (email_it = m_matches.begin(); email_it != m_matches.end();email_it++){
            if (m_emailCounts.find(*email_it) == m_emailCounts.end()){
                m_emailCounts.insert(std::pair <std::string,int> (*email_it,1));
            }
            else{
                m_emailCounts.find(*email_it)->second++;
            }
        }
        
        //Now we look at the uniqueMatches from all our matches
        std::set<std::string> m_uniqueMatches(m_matches.begin(),m_matches.end());
        std::set<std::string>::iterator uniqueMatches_it;
//        std::vector<std::string> m_uniqueMatches(m_matches.begin(),m_matches.end());
//        std::vector<std::string>::iterator uniqueMatches_it;

        std::vector<EmailCount> result;
        
        //if greater than threshold add it to result
        for (uniqueMatches_it = m_uniqueMatches.begin(); uniqueMatches_it != m_uniqueMatches.end(); uniqueMatches_it++){
            
//        for (uniqueMatches_it = m_matches.begin(); uniqueMatches_it != m_matches.end(); uniqueMatches_it++){
            if (m_emailCounts.find(*uniqueMatches_it)->second >= threshold){
                result.push_back(EmailCount(*uniqueMatches_it,m_emailCounts.find(*uniqueMatches_it)->second));
            }
        }
        
        //we create the sorted result by converting vector into a set which sorts it
        std::set<EmailCount> sorted_result(result.begin(),result.end());
        //we then turn it back into a vector and return it
        std::vector<EmailCount> sorted_vector(sorted_result.begin(),sorted_result.end());
        return sorted_vector;
    
    }
    else{
        return vector<EmailCount>();
    }
    

//    for loop
//        std::vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source)
//        add to a set of AttValPair
//    for everyithing in set
//        std::vector<std::string> FindMatchingMembers(const AttValPair& input)
//        add to vector of emails
//    const PersonProfile* GetMemberByEmail(std::string email);

}
