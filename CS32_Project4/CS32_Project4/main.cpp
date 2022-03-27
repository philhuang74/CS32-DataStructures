//
//  main.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//

#include <iostream>
#include <string>
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "MatchMaker.h"
#include <vector>
#include "provided.h"
using namespace std;
//
void findMemberByEmail(MemberDatabase& md,
 std::string member_email) {
 const PersonProfile* ptr = md.GetMemberByEmail(member_email);
 if (ptr != nullptr)
 std::cout << "Found info for member: " << ptr->GetName() << std::endl;
 else
 std::cout << "No member has address " << member_email << std::endl;
}

void findMatches(MatchMaker& mm,
 const std::string& member_email,
 int threshold) {
 std::vector<EmailCount> results =
 mm.IdentifyRankedMatches(member_email, threshold);
 if (results.empty())
std::cout << "We found no one who was compatible :-(" << std::endl;
 else {
 for (const auto& match: results) {
 std::cout << match.email << " has " << match.count
 << " attribute-value pairs in common with "
 << member_email << std::endl;
 }
 }
}

int main() {
//Test for AttributeTranslator****************
//    AttributeTranslator a;
//    string assetDirectory = "/Users/philipHuang/Documents/CS32/CS32-Project4";
////    std::cout << is_directory(assetDirectory) << std::endl;
//    a.Load("/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/translator.txt");
//
////    Checks if attvalpair does not exist ERROR nullptr access
////    std::vector<AttValPair> results = a.FindCompatibleAttValPairs(AttValPair("favorite_food", "del taco"));
////    if (!results.empty()) {
////        std::cout << "Compatible attributes and values:" << std::endl; for (const auto& p: results)
////        std::cout << p.attribute << " -> " << p.value << std::endl;
////    }
//
////    //Checks if attvalpair does exist. ERROR overwrites non-unique attvalpairs
//    cout<< "----------------------------"<<endl;
//    std::vector<AttValPair> results = a.FindCompatibleAttValPairs(AttValPair("hobby","rock climbing"));
//    if (!results.empty()) {
//        std::cout << "Compatible attributes and values:" << std::endl;
//        for (const auto& p: results)
//        std::cout << p.attribute << " -> " << p.value << std::endl;
//    }
//    cout <<"Size: " << results.size() << endl;
    
    
//    //Test for MemberDatabase**************
//    MemberDatabase d;
//    d.LoadDatabase("/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/members.txt");
////    findMemberByEmail(d,"MHa7@sky.com");
////    findMemberByEmail(d,"joe@sky.com");
//    std::vector<std::string> v = d.FindMatchingMembers(AttValPair("hobby","canyoneering"));
//    std::vector<std::string>::iterator it;
//    for(it = v.begin();it != v.end();it++){
//        cout << *it << endl;
//    }
//    cout << "------------------------" << endl;
    
//    PersonProfile Class Tester*****************
//    PersonProfile p = PersonProfile("Joe","joe@gmail.com");
//    cout << p.GetName() <<endl;
//    cout <<p.GetEmail() << endl;
//    cout << p.GetNumAttValPairs() << endl;
//    p.AddAttValPair(AttValPair("hobby","tennis"));
//    cout << p.GetNumAttValPairs() << endl;
//    AttValPair a;
//    p.GetAttVal(1,a);
//    cout << a.value << endl;
//    p.GetAttVal(0,a);
//    cout << a.value << endl;

//MatchMaker**************
   
    MemberDatabase d;
    d.LoadDatabase("/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/members.txt");
//    AttributeTranslator a;
//    a.Load("/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/translator.txt");
    
//    MemberDatabase d;
//    d.LoadDatabase("members.txt");
//    AttributeTranslator a;
//    a.Load("translator.txt");

//    MatchMaker matchmaker = MatchMaker(d,a);
//    matchmaker.getMemberDatabase()->GetDatabase("/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/members.txt");
//    findMatches(matchmaker, "AbFow2483@charter.net", 4);
    
    //Making sure substr works
//    string hi = "myname";
//    cout << hi.substr(0) <<endl;
//    cout <<hi.substr(0,2) <<endl;
//    cout << "YOL" << endl;
//    RadixTree<std::string> rd;
//    rd.insert("hi", "1");
//    rd.insert("hit","2");
//    rd.insert("holy","3");
//    rd.insert("poo", "4");
//
//    rd.insert("roman", "5");
//    rd.insert("romanian", "6");
//
//    rd.insert("card", "7");
//    rd.insert("car", "8");
//
//    rd.insert("card", "9");
//    rd.insert("cart", "10");
//    rd.insert("car", "11");
//
//    rd.insert("cat", "12");
//    rd.insert("cad", "13");
//
//    rd.insert("cst", "14");
//    rd.insert("cad", "15");
//
//    rd.insert("water","16");
//
//    rd.insert("slow", "17");
//    rd.insert("slower", "18");
//
//    rd.insert("tester", "19");
//    rd.insert("test", "20");
//
//    rd.insert("test", "21");
//    rd.insert("team", "22");
//
//    rd.insert("test", "23");
//    rd.insert("team", "24");
//    rd.insert("toast","25");
//    rd.insert("teste","26");
//    rd.insert("tester","27");
//
//    std::string* ptr = rd.search("toast");
//    rd.printNodes();
//    if (ptr == nullptr){
//        cout << "ERROR" <<endl;
//    }
}


//main.cpp

//#include "PersonProfile.h"
//#include "AttributeTranslator.h"
//#include "MemberDatabase.h"
//#include "MatchMaker.h"
//#include "provided.h"
//#include <iostream>
//#include <string>
//#include <vector>

//const std::string MEMBERS_FILE    = "/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/members.txt";
//const std::string TRANSLATOR_FILE = "/Users/laetitiahuang/Desktop/Personal/Projects/Data_Structures/CS32_Project4/CS32_Project4/translator.txt";
//
//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);
//
//int main() {
//    MemberDatabase mdb;
//    if (!mdb.LoadDatabase(MEMBERS_FILE))
//    {
//        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//        return 1;
//    }
//    AttributeTranslator at;
//    if (!at.Load(TRANSLATOR_FILE))
//    {
//        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
//        return 1;
//    }
//
//    while (findMatches(mdb, at))
//        ;
//
//    std::cout << "Happy dating!" << std::endl;
//        RadixTree<std::string> rd;
//        rd.insert("C", "Poe");
//        rd.insert("CoRoll3@aim.com", "Joe");
//        rd.insert("CoRoll4@aim.com", "Joe");
//        rd.insert("Corolla", "Joe");
//        rd.insert("CoRoll3@aim.com", "Poe");
//        rd.insert("C", "Poe");
//        rd.insert("Corosive", "Poe");
    
//    rd.insert("Corosive", "Poe");
//    rd.insert("C", "Poe");
//    rd.insert("Cardano","toe");
//    rd.insert("Corolla", "Joe");
//    rd.insert("CoRoll3@aim.com", "Poe");
//    rd.insert("CoRoll3@aim.com", "Joe");
//    rd.insert("CoRoll4@aim.com", "Joe");
//    rd.insert("Cojoyman","toe");
//    rd.insert("Co", "poe");
//
//    //    rd.insert("hit","Joe");
//    //    rd.insert("holy","joe");
//    //    rd.insert("poo", "poo");
//
//        string* ptr = rd.search("Corolla");
//        rd.printNodes();
//        if (ptr == nullptr){
//            cout << "ERROR" <<endl;
//        }
//}

//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
//{
//      // Prompt for email
//    std::string email;
//    const PersonProfile* pp;
//    for (;;) {
//        std::cout << "Enter the member's email for whom you want to find matches: ";
//        std::getline(std::cin, email);
//        if (email.empty())
//            return false;
//        pp = mdb.GetMemberByEmail(email);
//        if (pp != nullptr)
//            break;
//        std::cout << "That email is not in the member database." << std::endl;
//    }
//
//      // Show member's attribute-value pairs
//    std::cout << "The member has the following attributes:" << std::endl;
//    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
//        AttValPair av;
//        pp->GetAttVal(k, av);
//        std::cout << av.attribute << " --> " << av.value << std::endl;
//    }
//
//      // Prompt user for threshold
//    int threshold;
//    std::cout << "How many shared attributes must matches have? ";
//    std::cin >> threshold;
//    std::cin.ignore(10000, '\n');
//
//      // Print matches and the number of matching translated attributes
//    MatchMaker mm(mdb, at);
//    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
//    if (emails.empty())
//        std::cout << "No member was a good enough match." << std::endl;
//    else {
//        std::cout << "The following members were good matches:" << std::endl;;
//        for (const auto& emailCount : emails) {
//            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
////            cout << emailCount.email << endl;
////            cout << "------------------" << endl;
////            if (pp == nullptr) cout << "ERROR" <<endl;
//            std::cout << pp->GetName() << " at " << emailCount.email << " with "
//                      << emailCount.count << " matches!" << std::endl;
//        }
//    }
//    std::cout << std::endl;
//    return true;
//}
