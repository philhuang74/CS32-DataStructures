#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>
#include <sstream>

//StudentWorld methods should never return a vector, list, or iterator to StudentWorld's private game objects or pointers to those objects.

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath){
    m_peach = nullptr; //prevents nullptr bad access if player presses Q before playing
    m_level_completed = false;
    m_actors.clear();
    m_last_level = false;
}

void StudentWorld::cleanUp()
{
    
    vector<Actor*>::iterator it;
    int count = 1;
    for (it = m_actors.begin(); it != m_actors.end(); it++){
        cerr <<"Actor Deleted!" << "\n";
        count++;
        delete *it;
    }
    
    m_actors.clear();
    
    if(m_peach != nullptr){
        cerr << "Peach Deleted!" << "\n";
        delete m_peach;
        m_peach = nullptr;
    }
    
    cerr << count << endl;
}

StudentWorld::~StudentWorld(){
    cleanUp(); //calls StudentWorld's cleanup method
}



int StudentWorld::init()
{
    m_level_completed=false;
    
    Level lev(assetPath()); //assetPath() is inherited from Gameworld
    
    string level_file = "level0" + to_string(getLevel()) + ".txt"; //getLevel() is inherrited from Gameworld
    Level::LoadResult result = lev.loadLevel(level_file);
    if(result == Level::load_fail_file_not_found){
        cerr << "Could not find  " << level_file << " data file" << "\n";
    }
    else if (result == Level::load_fail_bad_format){
        cerr << level_file << " is improperly formatted" << "\n";
    }
    else if (result == Level::load_success){
        cerr << "Successfully loaded level" << "\n";
        
        for (int x = 0; x < 32; x++){
            for(int y = 0; y < 32; y++){ //a level game is a 32 by 32 grid
                Level::GridEntry ge;
                ge = lev.getContentsOf(x,y);
                switch(ge){
                    case Level::empty:
                        cout << "Location " << x << "," << y << " is empty" << "\n";
                        break;
                    case Level::koopa:
                        cout << "Location " << x << "," << y << " starts with a koopa" << "\n";
                        m_actors.push_back(new Koopa(this,x,y));
                        break;
                    case Level::goomba:
                        cout << "Location " << x << "," << y << " starts with a goomba" << "\n";
                        m_actors.push_back(new Goomba(this,x,y));
                        break;
                    case Level::piranha:
                        cout << "Location " << x << "," << y << " starts with a pirahna" << "\n";
                        m_actors.push_back(new Piranha(this,x,y));
                        break;
                    case Level::peach:
                        m_peach = new Peach(this,x,y);
                        cout << "Location " << x << "," << y << " is where Peach starts" << "\n";
                        break;
                    case Level::flag:
                        cout << "Location " << x << "," << y << " is where a flag is" << "\n";
                        m_actors.push_back(new Flag(this,x,y));
                        break;
                    case Level::mario:
                        cout << "Location " << x << "," << y << " is where Mario is";
                        m_actors.push_back(new Mario(this,x,y));
                        break;
                    case Level::pipe:
                        m_actors.push_back(new Pipe(this,x,y));
                        cout << "Location " << x << "," << y << "has a pipe" << "\n";
                        break;
                    case Level::block:
                        m_actors.push_back(new Block(this,x,y));
                        cout << "Location " << x << "," << y << " holds a regular block" << "\n";
                        break;
                    case Level::star_goodie_block:
                        m_actors.push_back(new Block(this,x,y,Block::star));
                        cout << "Location " << x << "," << y << " has a star goodie block" << "\n";
                        break;
                    case Level::mushroom_goodie_block:
                        m_actors.push_back(new Block(this,x,y,Block::mushroom));
                        cout << "Location " << x << "," << y << " has a mushroom goodie block" << "\n";
                        break;
                    case Level::flower_goodie_block:
                        m_actors.push_back(new Block(this,x,y,Block::flower));
                        cout << "Location " << x << "," << y << " has a flower goodie block" << "\n";
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
    if (m_peach!=nullptr and !m_peach->isDead()){
        m_peach->doSomething(); //get Peach to do something
    }
    else{ //Peach is dead
        decLives();
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    
    if(m_last_level){
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    
    if (m_level_completed){
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    //push_back() is not called, dynamic array won't grow, so iterator is valid
    vector<Actor*>::iterator it = m_actors.begin();
    for (it = m_actors.begin(); it != m_actors.end();it++){
        if  ((*it)!=nullptr and !(*it)->isDead()){
            (*it)->doSomething(); //get Actors to do something
        }
//        if (m_level_completed){
//            playSound(SOUND_FINISHED_LEVEL);
//            return GWSTATUS_FINISHED_LEVEL;
//        }
    }
    
    
    for (it = m_actors.begin(); it != m_actors.end();++it){
        if ((*it)!=nullptr and (*it)->isDead()){
            delete *it;
            m_actors.erase(it);
            it=m_actors.begin();
            it--;
        }
    }
    
    ostringstream oss;
    
    oss.fill('0');

    oss << "Lives: ";
    oss << setw(2) << getLives() << "  ";
    
    oss << "Level: ";
    oss << setw(2) << getLevel() << "  ";
    
    oss << "Points: ";
    oss << setw(6) << getScore() << " ";
    
    if(m_peach->hasJumpPower()){
        oss << "JumpPower!" << " ";
    }
    
    if(m_peach->isInvincible()){
        oss << "StarPower!" << " ";
    }
    
    if(m_peach->hasShootPower()){
        oss << "ShootPower!" << " ";
    }
    setGameStatText(oss.str());


    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addActor(Actor* a){
    m_actors.push_back(a);
}

void StudentWorld::endLevel(bool isGameWon){
    if (isGameWon){
        //DO SOMETHING
        m_last_level = true;
    }
    m_level_completed = true;
}

bool StudentWorld::moveOrBonk(Actor *actor, int destx, int desty){
    if (moveIfPossible(actor,destx,desty)){
        return true;
    }
    else{
        for (auto a:m_actors){
            if (overlapping(a->getX(),a->getY(),destx,desty)){
                a->getBonked(m_peach->isInvincible());
            }
        }
        return false;
    }
}

bool StudentWorld::moveIfPossible(Actor* actor, int destx, int desty){
    for (auto a: m_actors)
        if (a!=actor)
            if ((!a->isDead()) and a->blocksMovement() and overlapping(destx,desty,a->getX(),a->getY())){
                return false;
            }
    actor->moveTo(destx,desty);
    return true;
}

bool StudentWorld::isMovePossible(Actor* actor, int destx, int desty){
    //C++11 provides a new way to iterate without using iterators. (HW4 Spec)
    for (auto a: m_actors)
        if (a!=actor)
            if ((!a->isDead()) and a->blocksMovement() and overlapping(destx,desty,a->getX(),a->getY())){
                return false;
            }
    return true;
}

bool StudentWorld::overlapping(double x1, double y1, double x2, double y2){
//    if ((x1-SPRITE_WIDTH+1 < x2+SPRITE_WIDTH-1 and x1+SPRITE_WIDTH-1 > x2 - SPRITE_WIDTH +1) and (y1-SPRITE_HEIGHT+1 < y2+SPRITE_HEIGHT-1 and y1+SPRITE_HEIGHT-1 > y2 - SPRITE_HEIGHT+1)) return true;
    if ((x1 > x2-SPRITE_WIDTH+1) and (x1 < x2+SPRITE_WIDTH-1) and ((y1 > y2-SPRITE_HEIGHT+1) and (y1 < y2+SPRITE_HEIGHT-1 ))) return true;
    return false;
}

bool StudentWorld::bonkOverlappingPeach(Actor* bonker) const{
//    if ((m_peach->getX()-SPRITE_WIDTH+1 < bonker->getX()+SPRITE_WIDTH-1 and m_peach->getX()+SPRITE_WIDTH-1 > bonker->getX()-SPRITE_WIDTH+1) and (m_peach->getY()-SPRITE_HEIGHT+1 < bonker->getY()+SPRITE_HEIGHT-1 and m_peach->getY()+SPRITE_HEIGHT-1 > bonker->getY()-SPRITE_HEIGHT+1)){
//        m_peach->getBonked(true);
//        return true;
//    }
    if ((m_peach->getX() > bonker->getX()-SPRITE_WIDTH+1) and (m_peach->getX() < bonker->getX()+SPRITE_WIDTH-1) and ((m_peach->getY() > bonker->getY()-SPRITE_HEIGHT+1) and (m_peach->getY() < bonker->getY()+SPRITE_HEIGHT-1 ))){
        m_peach->getBonked(m_peach->isInvincible());
        return true;
    }
    else{
        return false;
    }
}

bool StudentWorld::bonkOverlappingActor(Actor* bonker) const{
    for (auto a: m_actors){
//        if ((a->getX()-SPRITE_WIDTH+1 < bonker->getX()+SPRITE_WIDTH+1 and a->getX()+SPRITE_WIDTH-1 > bonker->getX()-SPRITE_WIDTH+1) and (a->getY()-SPRITE_HEIGHT+1 < bonker->getY()+SPRITE_HEIGHT-1 and a->getY()+SPRITE_HEIGHT-1 > bonker->getY()-SPRITE_HEIGHT+1)){
//            a->getBonked(true);
//            return true;
//        }
//        if (a->blocksMovement() and ((bonker->getY()-SPRITE_HEIGHT+1+5 > a->getY()))){
//            a->getBonked(m_peach->isInvincible());
//            return true;
//        }
        if((a->blocksMovement()) and (bonker->getX() > a->getX()-SPRITE_WIDTH+1) and (bonker->getX() < a->getX()+SPRITE_WIDTH-1) and (bonker->getY() == a ->getY()-SPRITE_HEIGHT) ){
            a->getBonked(m_peach->isInvincible());
            return true;
//            break;
        }
//        if((a->blocksMovement()) and (((bonker->getX() >= a->getX()-SPRITE_WIDTH+1) and (bonker->getX() <= a->getX()+SPRITE_WIDTH-1)) or ((bonker->getX() <= a->getX()-SPRITE_WIDTH+1) and (bonker->getX() <= a->getX()+SPRITE_WIDTH-1))) and (bonker->getY()+SPRITE_HEIGHT+SPRITE_HEIGHT-1 == a ->getY()) ){
//            a->getBonked(m_peach->isInvincible());
//            return true;
//            break;
//        }

        if ((bonker->getX() > a->getX()-SPRITE_WIDTH+1) and (bonker->getX() < a->getX()+SPRITE_WIDTH-1) and ((bonker->getY() > a->getY()-SPRITE_HEIGHT+1) and (bonker->getY() < a->getY()+SPRITE_HEIGHT-1 )))
        {
            a->getBonked(m_peach->isInvincible());
            return true;
//            break;
        }
    }
    return false;
}

bool StudentWorld::damageOverlappingPeach(Actor* damager) const{
//    if ((m_peach->getX()-SPRITE_WIDTH+1 < damager->getX()+SPRITE_WIDTH+1 and m_peach->getX()+SPRITE_WIDTH-1 > damager->getX()-SPRITE_WIDTH+1) and (m_peach->getY()-SPRITE_HEIGHT+1 < damager->getY()+SPRITE_HEIGHT-1 and m_peach->getY()+SPRITE_HEIGHT-1 > damager->getY()-SPRITE_HEIGHT+1)){
//        m_peach->sufferDamageIfDamageable();
//        return true;
//    }
    if ((m_peach->getX() > damager->getX()-SPRITE_WIDTH+1) and (m_peach->getX() < damager->getX()+SPRITE_WIDTH-1) and ((m_peach->getY() > damager->getY()-SPRITE_HEIGHT+1) and (m_peach->getY() < damager->getY()+SPRITE_HEIGHT-1 ))){
        m_peach->sufferDamageIfDamageable();
        return true;
    }
    else{
        return false;
    }
}

//FAULTY
bool StudentWorld::damageOverlappingActor(Actor* damager) const{
    for (auto a: m_actors){
//        if ((a->getX()-SPRITE_WIDTH+1 < damager->getX()+SPRITE_WIDTH+1 and a->getX()+SPRITE_WIDTH-1 > damager->getX()-SPRITE_WIDTH+1) and (a->getY()-SPRITE_HEIGHT+1 < damager->getY()+SPRITE_HEIGHT-1 and a->getY()+SPRITE_HEIGHT-1 > damager->getY()-SPRITE_HEIGHT+1)){
//            a->sufferDamageIfDamageable();
//            return true;
//        }
//        if (!a->blocksMovement() and (damager->getX() > a->getX()-SPRITE_WIDTH+1) and (damager->getX() < a->getX()+SPRITE_WIDTH-1) and ((damager->getY() > a->getY()-SPRITE_HEIGHT+1) and (damager->getY() < a->getY()+SPRITE_HEIGHT-1 ))){
        if ((!a->blocksMovement()) and (((a->getX() > damager->getX()-SPRITE_WIDTH+1) and (a->getX() < damager->getX()+SPRITE_WIDTH-1)) and ((a->getY() > damager->getY()-SPRITE_HEIGHT+1) and (a->getY() < damager->getY()+SPRITE_HEIGHT-1 )))){
            a->sufferDamageIfDamageable();}
        else if ((a->blocksMovement()) and (((a->getX() > damager->getX()-SPRITE_WIDTH+1) and (a->getX() < damager->getX()+SPRITE_WIDTH-1)) and ((a->getY() > damager->getY()-SPRITE_HEIGHT+1) and (a->getY() < damager->getY()+SPRITE_HEIGHT-1 )))){
            a->sufferDamageIfDamageable();
            return true;
        }
    }
    return false;
    
}

bool StudentWorld::overlapsPeach(Actor* a) const{
//    if (((a->getX()-SPRITE_WIDTH+1 < m_peach->getX()+SPRITE_WIDTH-1) and (a->getX()+SPRITE_WIDTH > m_peach->getX()-SPRITE_WIDTH+1)) and ((a->getY()-SPRITE_HEIGHT < m_peach->getY()+SPRITE_HEIGHT-1) and (a->getY()+SPRITE_HEIGHT > m_peach->getY()-SPRITE_HEIGHT+1))) return true;
    if ((m_peach->getX() > a->getX()-SPRITE_WIDTH+1) and (m_peach->getX() < a->getX()+SPRITE_WIDTH-1) and ((m_peach->getY() > a->getY()-SPRITE_HEIGHT+1) and (m_peach->getY() < a->getY()+SPRITE_HEIGHT-1 ))) return true;
    else{
        return false;
    }
}

bool StudentWorld::getPeachTargetingInfo(Actor* a, int yDeltaLimit, int& xDeltaFromActor) const{
//    if (a->getY() - m_peach->getY() <= yDeltaLimit || a->getY() - m_peach->getY() <= -yDeltaLimit) return false;
    if (abs(a->getY() - m_peach->getY()) >= yDeltaLimit) return false;
    xDeltaFromActor = m_peach->getX() - a->getX();
    return true;
}

void StudentWorld::setPeachHP(int hp) const{
    m_peach->setHP(hp);
}

void StudentWorld::grantInvincibility(int ticks) const{
    m_peach->gainInvincibility(ticks);
}

void StudentWorld::grantShootPower() const{
    m_peach->gainShootPower();
}

void StudentWorld::grantJumpPower() const{
    m_peach->gainJumpPower();
}


