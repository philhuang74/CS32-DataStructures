//PART II
// Possible interfaces for actors.  You may use all, some, or none
// of this, as you wish.

// One of the goals of this design was to reduce the coupling between
// StudentWorld.h and Actor.h as much as possible.  Notice that in fact,
// Actor.h does not need to include StudentWorld.h at all.  (Of course,
// Actor.cpp does.)

#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include "GraphObject.h"
class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int x, int y, int dir = right, int depth = 0): GraphObject(imageID, x,y,dir,depth), m_world(sw), m_dead(false){};
    
    // Action to perform for each tick.
    void doSomething()
    {
        if (!isDead())
            doSomethingAux();
    }

      // Bonk this actor.  Parameter says whether bonker is Peach with invincibiity.
    virtual void getBonked(bool bonkerIsInvinciblePeach){};

      // Do what the spec says happens when damage is inflicted on this actor.
    virtual void sufferDamageIfDamageable(){};

      // Fall the indicated distance if not blocked.
    void fallIfPossible(int dist);
        
      // Reverse the direction this actor is facing.
    void reverseDirection();
    
      // Mark this actor as dead.
    void setDead();

    
      // Is this actor dead?
    bool isDead() const;


      // Does this actor block movement?
    virtual bool blocksMovement() const;

      // Get this actor's world
    StudentWorld* world() const;

    
      // Set destx and desty to the coordinates dist pixels away in direction
      // dir from this actor's position.
    void convertDirectionAndDistanceToXY(int dir, int dist, int& destx, int& desty) const;

private:
    virtual void doSomethingAux() = 0;
    bool m_dead;
    StudentWorld* m_world;
};

class Peach : public Actor
{
public:
    Peach(StudentWorld* w, int x, int y):Actor(w,IID_PEACH,SPRITE_WIDTH*x,SPRITE_HEIGHT*y,right,0),m_health_point(0),m_invincible(false),m_shoot_power(false),m_jump_power(false),m_ticks(0),m_recharge_tick(0),m_jump_distance(0),m_initiated_jump(false),m_temporary_invincible(false),m_temporary_ticks(0){};
    
    void goTo(int x, int y);
    
    virtual void getBonked(bool bonkerIsInvinciblePeach);
    
    virtual void sufferDamageIfDamageable();
        
      // Set Peach's hit points.
    void setHP(int hp);
    
      // Grant Peach invincibility for this number of ticks.
    void gainInvincibility(int ticks);
    
      // Grant Peach Shoot Power.
    void gainShootPower();
    
      // Grant Peach Jump Power.
    void gainJumpPower();
    
      // Is Peach invincible?
    bool isInvincible() const;
    
      // Does Peach have Shoot Power?
    bool hasShootPower() const;

      // Does Peach have Jump Power?
    bool hasJumpPower() const;
    
private:
    virtual void doSomethingAux();
    int m_health_point;
    bool m_invincible;
    bool m_shoot_power;
    bool m_jump_power;
    bool m_initiated_jump;
    int m_ticks;
    int m_recharge_tick;
    int m_jump_distance;
    bool m_temporary_invincible;
    int m_temporary_ticks;
};

// (Further private sections won't be shown.)

class Obstacle : public Actor
{
public:
    Obstacle(StudentWorld* w, int imageID, int x, int y):Actor(w,imageID,SPRITE_WIDTH*x,SPRITE_HEIGHT*y,right,2){};
    virtual void getBonked(bool bonkerIsInvinciblePeach);
    virtual bool blocksMovement() const;
    
private:
    virtual void getBonkedSub(bool bonkerIsInvinciblePeach) = 0;
    virtual void doSomethingAux(){return;};
};

class Block : public Obstacle
{
public:
    enum GoodieType { none, flower, mushroom, star };
    Block(StudentWorld* w, int x, int y, GoodieType g = none):Obstacle(w,IID_BLOCK,x,y),m_goodie(g){};
private:
//    virtual void doSomethingAux(){return;};
    virtual void getBonkedSub(bool bonkerIsInvinciblePeach);
    GoodieType m_goodie;
};



class Pipe : public Obstacle
{
public:
    Pipe(StudentWorld* w, int x, int y):Obstacle(w,IID_PIPE,x,y){};
private:
    virtual void getBonkedSub(bool bonkerIsInvinciblePeach);
};

class LevelEnder : public Actor
{
public:
    LevelEnder(StudentWorld* w, int imageID, int x, int y, bool isGameEnder):Actor(w,imageID,SPRITE_WIDTH*x,SPRITE_HEIGHT*y,0,1),m_isGameEnder(isGameEnder){};
    bool isGameEnder() const{
        return m_isGameEnder;
    }
    virtual void doSomethingAux();
private:
//    virtual void doSomethingAux() = 0;
    virtual void doSomethingAuxSub() = 0;
    virtual LevelEnder* levelPointer() = 0;
    bool m_isGameEnder;
};

class Flag : public LevelEnder
{
public:
    Flag(StudentWorld* w, int x, int y):LevelEnder(w,IID_FLAG,x,y,false){};
private:
//    virtual void doSomethingAux();
    virtual void doSomethingAuxSub();
    virtual LevelEnder* levelPointer();
};

class Mario : public LevelEnder
{
public:
    Mario(StudentWorld* w, int x, int y):LevelEnder(w,IID_MARIO,x,y,true){};
private:
//    virtual void doSomethingAux();
    virtual void doSomethingAuxSub();
    virtual LevelEnder* levelPointer();

};

class Goodie : public Actor
{
public:
    Goodie(StudentWorld* w, int imageID, int x, int y):Actor(w,imageID,SPRITE_WIDTH*x,SPRITE_HEIGHT*y,0,1){};
    virtual void doSomethingAux();
private:
    virtual void doSomethingAuxSub() = 0;
};

class Flower : public Goodie
{
public:
    Flower(StudentWorld* w, int x, int y):Goodie(w,IID_FLOWER,x,y){};
private:
    virtual void doSomethingAuxSub();
};

class Mushroom : public Goodie
{
public:
    Mushroom(StudentWorld* w, int x, int y):Goodie(w,IID_MUSHROOM,x,y){};
private:
    virtual void doSomethingAuxSub();
};

class Star : public Goodie
{
public:
    Star(StudentWorld* w, int x, int y):Goodie(w,IID_STAR,x,y){};
private:
    virtual void doSomethingAuxSub();
};

class Projectile : public Actor
{
public:
    Projectile(StudentWorld* w, int imageID, int x, int y, int dir):Actor(w,imageID,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,dir,1){};
    virtual void doSomethingAux();
private:
    virtual bool doSomethingAuxSub() = 0;
};

class PiranhaFireball : public Projectile
{
public:
    PiranhaFireball(StudentWorld* w, int x, int y, int dir):Projectile(w,IID_PIRANHA_FIRE,x,y,dir){};
private:
    virtual bool doSomethingAuxSub();
};

class PeachFireball : public Projectile
{
public:
    PeachFireball(StudentWorld* w, int x, int y, int dir):Projectile(w,IID_PEACH_FIRE,x,y,dir){};
private:
    virtual bool doSomethingAuxSub();
};

class Shell : public Projectile
{
public:
    Shell(StudentWorld* w, int x, int y, int dir):Projectile(w,IID_SHELL,x,y,dir){};
private:
    virtual bool doSomethingAuxSub();
};

class Enemy : public Actor
{
public:
    Enemy(StudentWorld* w, int imageID, int x, int y):Actor(w,imageID,SPRITE_WIDTH*x,SPRITE_HEIGHT*y,right,0){};
    virtual void getBonked(bool bonkerIsInvinciblePeach);
    
    virtual void sufferDamageIfDamageable();

private:
    virtual void doSomethingAux();
    
};

class Goomba : public Enemy
{
public:
    Goomba(StudentWorld* w, int x, int y):Enemy(w,IID_GOOMBA,x,y){};
};

class Koopa : public Enemy
{
public:
    Koopa(StudentWorld* w, int x, int y):Enemy(w,IID_KOOPA,x,y){};
    virtual void sufferDamageIfDamageable();
//    virtual bool blocksMovement() const;
private:
//    virtual void doSomeethingAux();
};

class Piranha : public Enemy
{
public:
    Piranha(StudentWorld* w, int x, int y):Enemy(w,IID_PIRANHA,x,y),m_fire_delay(0){};
private:
    int m_fire_delay;
    virtual void doSomethingAux();
};

#endif // ACTOR_INCLUDED
