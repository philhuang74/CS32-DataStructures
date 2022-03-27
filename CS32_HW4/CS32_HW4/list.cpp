//
//  list.cpp
//  CS32_HW4
//
//  Created by Philip Huang on 3/1/22.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Class
{
  public:
    Class(string nm) : m_name(nm) {}
    string name() const { return m_name; }
    const vector<Class*>& subclasses() const { return m_subclasses; }
    void add(Class* d) { m_subclasses.push_back(d); }
    ~Class();
  private:
    string m_name;
    vector<Class*> m_subclasses;
};

Class::~Class()
{
    for (size_t k = 0; k < m_subclasses.size(); k++)
        delete m_subclasses[k];
}

void listAll(string path, const Class* c)  // two-parameter overload
{
    if (c==nullptr) return; //BASE CASE, if c is a nullptr, return
    
    if (c->name() != ""){ //BASE CASE, if there is a name for class, print it
        cout << path << c->name() << endl;
    }
    if (c->subclasses().size() == 0) return; //If the class does not have any subclasses, return
    
    path += c->name() + "=>"; //Otherwise, there is more subclasses, update the path with =>
    
    vector<Class*>::const_iterator it = c->subclasses().begin(); //set iterator
    for (it = c->subclasses().begin(); it != c->subclasses().end(); it++){
        listAll(path,*it); //recursively call all other subclasses with this path more base class =>
    }
    
// Could also use range based for loop C++11
//    for (Class* classPtr:(c->subclasses())){
//        listAll(path,classPtr);
//    }

}


void listAll(const Class* c)  // one-parameter overload
{
    if (c != nullptr)
        listAll("", c);
}

int main()
{
    Class* d1 = new Class("Koopa");
    listAll(d1);
    cout << "====" << endl;

    d1->add(new Class("SoopaKoopa"));
    Class* d2 = new Class("Enemy");
    d2->add(new Class("Piranha"));
    d2->add(d1);
    Class* d3 = new Class("Goodie");
    d3->add(new Class("Flower"));
    d3->add(new Class("Mushroom"));
    d3->add(new Class("Star"));
    listAll(d3);
    cout << "====" << endl;

    Class* d4 = new Class("Actor");
    d4->add(d2);
    d4->add(new Class("Peach"));
    d4->add(d3);
    listAll(d4);
    delete d4;
}
//This main routine should produce the following output (the first line written is Koopa, not an empty line):
//
//Koopa
//====
//Goodie
//Goodie=>Flower
//Goodie=>Mushroom
//Goodie=>Star
//====
//Actor
//Actor=>Enemy
//Actor=>Enemy=>Piranha
//Actor=>Enemy=>Koopa
//Actor=>Enemy=>Koopa=>SoopaKoopa
//Actor=>Peach
//Actor=>Goodie
//Actor=>Goodie=>Flower
//Actor=>Goodie=>Mushroom
//Actor=>Goodie=>Star
