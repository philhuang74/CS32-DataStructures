//
//  RadixTree.hpp
//  CS32_Project4
//
//  Created by Philip Huang on 3/4/22.
//
#include <iostream>
#include <string>
//#include <map>
//#include <vector>
using namespace std;

#ifndef RadixTree_hpp
#define RadixTree_hpp


template <typename ValueType>
class RadixTree {
public:
    RadixTree(){
        root = new RadixTreeNode("",false,nullptr);
    }
    
    ~RadixTree(){

        cout << "RADIXTREE Destructor called" << endl;
        eraseNode(root);
    }

    void insert(std::string key, const ValueType& value){
//DUMMY IMPLEMENTATION
//        m_map.insert(std::pair <std::string,ValueType> (key,value));
////        m_map[key]=value;

//ACTUAL IMPLEMENTATION
        ValueType* m_value = new ValueType(value);
        insertHelper(key,m_value,root,nullptr);
    }

    
    
   
    ValueType* search(std::string key) const { //const{ //UNCOMMENT CONST
        //DUMMY IMPLEMENTATION
//        if (m_map.find(key) == m_map.end()){
//            return nullptr;
//        }
//        return &(m_map.find(key)->second);
        
        //ACTUAL IMPLEMENTATION
        return searchHelper(key, root, nullptr);
    }

//    void printNodes(){
//        print(root);
//    }
private:
    //DUMMY IMPLEMENTATION
    //    std::map<std::string,ValueType> m_map; //implement fake radix tree
    
    //ACTUAL IMPLEMENTATION
    struct RadixTreeNode{
        string word;
        bool endOfWord;
        RadixTreeNode* children[128] = {nullptr};//{}; //128 ASCII Values //Node *arr[256] = {nullptr};
        ValueType* value = nullptr; //value();
        RadixTreeNode(){
            word = "";
            endOfWord = false;
            value = nullptr;
        }
        RadixTreeNode(string w, bool isEnd, ValueType* v){
            word = w;
            endOfWord = isEnd;
            value = v;
        }
    };
    
    RadixTreeNode* root;
    
       
    void insertHelper(string key, ValueType* value, RadixTreeNode* cur, RadixTreeNode* parent){
            if (cur->word != key){ //and cur->endOfWord == true){
                std::string leftover = "";
                int sameIndex;
                if (cur->word.size() > key.size()){
                    for (int i=0;i<key.size();i++){
                        if (cur->word[i] != key[i]){
                            leftover = cur->word.substr(i);
                            sameIndex = i;
                            break;
                        }
                    }
                    if (leftover == ""){
                        leftover = cur->word.substr(key.size());
                        sameIndex = key.size();
                    }
                    
                    if (key.substr(sameIndex) == ""){
                        parent->children[cur->word[0]] = new RadixTreeNode(cur->word.substr(0,sameIndex),true,value);
                        RadixTreeNode* newParent = parent->children[cur->word[0]];
                        parent->children[cur->word[0]]->children[leftover[0]] = cur;
                        cur->word = leftover;
                        parent = newParent;
                        return;
                    }
                    if (leftover != "" and key.substr(sameIndex)!= ""){
                        parent->children[cur->word[0]] = new RadixTreeNode(cur->word.substr(0,sameIndex),false,nullptr);
                        RadixTreeNode* newParent = parent->children[cur->word[0]];
                        parent->children[cur->word[0]]->children[leftover[0]] = cur;
                        cur->word = leftover;
                        
                        parent = newParent;
                        parent->children[cur->word[0]]->children[key.substr(sameIndex)[0]] = new RadixTreeNode(key.substr(sameIndex),true,value);
                        return;
                    }
               
                    //NEWLY ADDED
                    
                   
                    //CHECK NULLPTR
                
                }
                else if (cur->word.size() == key.size()){
                    for (int i=0;i<key.size();i++){
                        if (cur->word[i] != key[i]){
                            leftover = cur->word.substr(i);
                            sameIndex = i;
                            break;
                        }
                    }
                    if (leftover == ""){
                        return;
                    }

                    parent->children[cur->word[0]] = new RadixTreeNode(cur->word.substr(0,sameIndex),false,nullptr);
                    RadixTreeNode* newParent = parent->children[cur->word[0]];
                    parent->children[cur->word[0]]->children[leftover[0]] = cur;
                    

                    parent->children[cur->word[0]]->children[key.substr(sameIndex)[0]] = new RadixTreeNode(key.substr(sameIndex),true,value);
                    parent = newParent; //Do I even need this
                    cur->word = leftover;
                    return;
                }
                else{ //key.size() > cur->word.size()
                    for (int i=0;i<cur->word.size();i++){
                        if (cur->word[i] != key[i]){
                            leftover = key.substr(i);
                            sameIndex = i;
                            break;
                        }
                   
                    }
                    if (leftover == ""){
                        leftover = key.substr(cur->word.size());
                        sameIndex = cur->word.size();
                    }
                    if (cur->word.substr(sameIndex) != ""){
                        parent->children[cur->word[0]] = new RadixTreeNode(cur->word.substr(0,sameIndex),false,nullptr);
                        

                        parent->children[cur->word[0]]->children[leftover[0]] = new RadixTreeNode(leftover,true,value);
                        parent->children[cur->word[0]]->children[cur->word.substr(sameIndex)[0]] = cur;
                        cur->word = cur->word.substr(sameIndex);
                        return;
                    }
                    if (cur->children[leftover[0]] == nullptr){
                        
                        cur->children[leftover[0]] = new RadixTreeNode(leftover,true,value);
                        return;
                    }
                    
                    else{
                        insertHelper(leftover,value,cur->children[leftover[0]],cur);
                        return;
                    }
                
                }

            
            }
        if (cur->word == key and cur->endOfWord == false){
                cur->endOfWord = true;
                cur->value = value;
                return;
            }
            
        
        if(cur->word == key and cur->endOfWord == true){
            cur->value = value;
            return;
        }
        

    }
    
    ValueType* searchHelper(std::string key, RadixTreeNode* cur, RadixTreeNode* parent) const {
//        cout << "Key: " << key << endl;
//        if (cur == nullptr) return nullptr;
        if (cur->word != key){ //and cur->endOfWord == true){
            
            std::string leftover = "";
            int sameIndex;
            
            if (cur->word.size() > key.size()){
//                cout << "1" << endl;
                return nullptr;
            }
            else if (cur->word.size() == key.size()){
//                cout << "2" << endl;
                return nullptr;
            }
            else{ //key.size() > cur->word.size()
                for (int i=0;i<cur->word.size();i++){
                    if (cur->word[i] != key[i]){
                        leftover = key.substr(i);
                        sameIndex = i;
                        break;
                    }
               
                }
                if (leftover == ""){
                    leftover = key.substr(cur->word.size());
                    sameIndex = cur->word.size();
                }
                if (cur->word.substr(sameIndex) != ""){
//                    cout << "3" << endl;
                    return nullptr;
                }
                if (cur->children[leftover[0]] == nullptr){
//                    cout << "4" << endl;
                    return nullptr;
                }
                return searchHelper(leftover,cur->children[leftover[0]],cur);
//                cout << "52" << endl;
            }
        }
        
        else{ //cur->word == key
            if(cur->endOfWord == true){
//                cout << "63" << endl;
                return cur->value;
            }
            else{
//                cout << "7" << endl;
                return nullptr;
            }
        }
    }
    
    void eraseNode(RadixTreeNode* node){
//        cout << "Helper Called" << endl;
        if (node == nullptr) return;
        for (auto child  : node->children){
            eraseNode(child);
        }
        if (node->value != nullptr) delete node->value;
        delete node;
    }
    
//    void print(RadixTreeNode* node){
//        if (node == nullptr) return;
//        for (auto child  : node->children){
//            print(child);
//        }
////        cout << "deleted node: " << node->word << endl;
//        cout << "Word: " << node->word << endl;
//        if (node->endOfWord){
//            cout << "Value: " << *(node->value) << endl;
//        }
//
//    }

    
};


#endif /* RadixTree_hpp */
