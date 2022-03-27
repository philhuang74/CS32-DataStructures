//
//  MatchMaker.hpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/5/22.
//

#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "provided.h"
#include <vector>
//#include <set>
//#include "utility.h"
#ifndef MatchMaker_hpp
#define MatchMaker_hpp

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);//{ //UNCOMMENT CONST
//        m_mdb = &mdb;
//        m_at = &at;
//        
//    }; //constructor
    ~MatchMaker();//{};
    
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const; //UNCOMMENT CONST
    
//    const MemberDatabase* getMemberDatabase();
private:
    const MemberDatabase* m_mdb;
    const AttributeTranslator* m_at;
//    std::set<AttValPair> m_uniqueCompatibleAttValPairs; //could be defined in IdentifyRankedMatches to reduce space complexity

//    email -> (Member database) personprofiel -> PersonProfile getattval attirbute value pairs -> (AttributeTranslator) compatible attvalpair in a set iterate over this set (MemberDatabase) radixtree attvalpairs to email map number strings emails to ints count set emailcount to vector sorted
};

#endif /* MatchMaker_hpp */
