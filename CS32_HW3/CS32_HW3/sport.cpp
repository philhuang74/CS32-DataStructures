//
//  main.cpp
//  CS32_HW3
//
//  Created by Philip Huang on 2/4/22.
//

#include <iostream>
#include <string>
using namespace std;

//We need to declare isOutdoor() and icon() in Sport because we don't know if the derived classes of Sport will have those functions, so its better to declare it in the base class.
//Any attempt to declare a new Sport or Sport s will lead to compilation error, we don't want to follow Shape's virtual table, it has nullptr. Anything that is a shape and nothing more can't exist, but a Snowboarding Object that has a Sport object embedded inside can exist. Pointers and References to Sport objects are still allowed, because it can be Snowboarding, Biathlon, etc. Sport is an abstract base class. (Abstract v. Concrete) Dog, Cat, Monkey is a concrete type. Mammal is a abstract type. Can you buy a mammal? No. Because sport has at least one pure virtual function, it is an abstract class. If you forget to implement isOutdoor() which is a pure virtual function of the base class Sport in derived class like Snowboarding. It will treat Snowboarding as an abstract class. Compiler will complain when you type new Snowboarding because Snowboarding will inherit from Sport's isOutdoor(), which is a pure virtual function.
//Polymorphism means you can have different types for an object based on the inherticance hierachy the object belongs to (Dog, Mammal, Animal), and that a virtual function can have different implementataions depending on the type of object it is.
//NEVER ATTEMPT TO OVERIDE A NON-VIRTUAL FUNCTION, need virtual in base class if we want dynamic binding. Derived classes don't need the virtual keywork, but it helps with readibility of code
class Sport{
public:
    Sport(string event): m_event(event){};
    virtual ~Sport(){} //This is the destructor that compiler will write for Sport, because theres nothing to delete since data members a builtin types. However, the compiler generated destructor will not be virtual, so we must declare Sport destructor to be virtual so that when we delete Sport objects, it knows how to delete Snowboarding, Biathlon, etc and call their destructors. If Snowboarding had a data member Node head* that points to a linked list. Deleting the Sport object will cause a memory leak. We must implement Sport destructor, hence the {} because when Snobarding object is deleted. It goes through three steps. 1. Execute the body of destructor, 2. Destroy the data members, 3. DESTROY THE BASE PART, which is Sport. For construction, it is the opposite. 1. Construct the base part, 2. Construct the data members, 3. Execute the body of constructor
    string name() const{return m_event;}; //C++ default is static binding, which works for this function. Compiler will just call Sport's name function. No matter what sport we have, I expect its name will be the event name, so we want static binding.
    virtual bool isOutdoor() const{return true;}; //We want dynamic binding, want compiler to call the right isOutdoor, so we use virtual, Ignore: don't want pure virtual according to spec. (I want nullptr because I don't want to implement this function for Sport, does not make sense for Sport to be either indoor or outdoor, so set = 0 means it will be nullptr in virtual table. In languages like Java, C#, we would declare this as abstract function. In C++, we call this a pure virtual function.)
    virtual string icon() const = 0; //want dynamic binding, want compiler to call the right icon, so we use virtual. What is icon of sport, does not make sense. Lets make it = 0.
    private:
    string m_event;
};


class Snowboarding: public Sport{
    public:
    Snowboarding(string event): Sport(event){} //Have to declare Sport(event), not m_event(event) because m_event is private member of Sport. I can't touch my liver (a private member of Human), so you can't call private member of Sport.
    virtual ~Snowboarding(){ cout << "Destroying the Snowboarding object named " << this->name() << "." << "\n";}; //This will call the name() function of Sport.
//    virtual bool isOutdoor() const {return true;};
    virtual string icon() const {return "a descending snowboarder";};
    private:
    
};

class Biathlon: public Sport{
    public:
    Biathlon(string event,double distance): Sport(event), m_distance(distance){}
    virtual ~Biathlon() {cout << "Destroying the Biathlon object named " + this->name() + ", distance " << m_distance << " km." << "\n";}
//    virtual bool isOutdoor() const {return true;};
    virtual string icon() const {return "a skier with a rifle";};
    private:
    double m_distance;
};

class FigureSkating: public Sport{
    public:
    FigureSkating(string event): Sport(event){}
    virtual ~FigureSkating(){cout << "Destroying the FigureSkating object named " << this->name() << "." << "\n"; };
    virtual bool isOutdoor() const {return false;};
    virtual string icon() const {return "a skater in the Biellmann position";};
    private:
};

void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
      // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

      // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];

//    Sport s; // Makes sure that Sport is abstract class and we can't call it, it has at least one pure virtual function and that makes it abstract.
}

//Here are the sports.
//Women's halfpipe is an outdoor sport with an icon showing a descending snowboarder.
//Men's pursuit is an outdoor sport with an icon showing a skier with a rifle.
//Women's sprint is an outdoor sport with an icon showing a skier with a rifle.
//Pair skating free is an indoor sport with an icon showing a skater in the Biellmann position.
//Cleaning up.
//Destroying the Snowboarding object named Women's halfpipe.
//Destroying the Biathlon object named Men's pursuit, distance 12.5 km.
//Destroying the Biathlon object named Women's sprint, distance 7.5 km.
//Destroying the FigureSkating object named Pair skating free.
