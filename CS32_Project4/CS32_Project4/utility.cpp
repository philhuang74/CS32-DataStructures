//
//  utility.cpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/10/22.
//

#include "utility.h"

bool operator<(const AttValPair& lhs, const AttValPair& rhs){
    if ((lhs.attribute + "," + lhs.value) < (rhs.attribute + "," + rhs.value)) return true;
//    if(lhs.value < rhs.value) return true;
//    if(lhs.attribute < rhs.attribute) return true;
    else return false;
}

bool operator<(const EmailCount& lhs, const EmailCount& rhs){
    if (lhs.count > rhs.count) return true;
    if (lhs.count == rhs.count){
        if (lhs.email < rhs.email){return true;}
        else return false;
    }
    else return false;
}
