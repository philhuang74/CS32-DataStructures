//
//  AttributeTranslator.hpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/3/22.
//
#include <iostream>
#include "provided.h"
#include "RadixTree.h"
#include <vector>

#ifndef AttributeTranslator_hpp
#define AttributeTranslator_hpp

class AttributeTranslator{
public:
    AttributeTranslator();//{};
    ~AttributeTranslator();//{};
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const; //USE SET INSIDE TO REDUCE REDUNDANCY //UNCOMMENT CONST
private:
    RadixTree<std::vector<AttValPair>> m_RadixTree;
};

#endif /* AttributeTranslator_hpp */
