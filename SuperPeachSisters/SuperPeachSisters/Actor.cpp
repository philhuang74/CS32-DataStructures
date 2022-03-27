//PART II
#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//ACTOR SECTION
StudentWorld* Actor::world() const{
    return m_world;
}

bool Actor::blocksMovement() const{
    return false;
}
void Actor::fallIfPossible(int dist){
    if (world()->isMovePossible(this, this->getX(), this->getY()-dist))
        moveTo(getX(),getY()-dist);
}

void Actor::reverseDirection(){
//        static const int right = 0;
//        static const int left = 180;
//        static const int up = 90;
//        static const int down = 270;
    int dir = this->getDirection();
    if (dir < 180){
        int newdir = dir+180;
        this->setDirection(newdir);
    }
    else{ //dir is > 180
        int newdir = dir-180;
        this->setDirection(newdir);
    }
}

void Actor::setDead(){
    m_dead = true;
}

bool Actor::isDead() const{
    return m_dead;
}


void Actor::convertDirectionAndDistanceToXY(int dir, int dist, int& destx, int& desty) const {
    if (dir == left){
        destx = getX()-dist;
        desty = getY();
    }
    else if (dir == right){
        destx = getX()+dist;
        desty = getY();
    }
    else if (dir == down){
        destx = getX();
        desty = getY()-dist;
    }
    else if (dir == up){
        destx = getX();
        desty = getY()+dist;
    }
}

//ACTOR SECTION
//STILL TO DO: getbonked, sufferDamage?

//PEACH SECTION

void Peach::doSomethingAux(){
    if (this->isDead()){
        return;
    }
    
    if (m_invincible){
        m_ticks--;
        if(m_ticks == 0){
            m_invincible = false;
        }
    }
//    else if ((m_jump_power or m_shoot_power) and world()->bonkOverlappingActor(this) and m_ticks==0){
////        world()->playSound(SOUND_PLAYER_HURT);
//        m_health_point--;
//        m_ticks = 10;
//        if(m_health_point==0){
//            m_jump_power = false;
//            m_shoot_power = false;
//            this->setDead();
//        }
//    }
    if (m_temporary_invincible){
        m_temporary_ticks--;
        if(m_temporary_ticks == 0){
            m_temporary_invincible = false;
        }
    }
    if (m_recharge_tick > 0) m_recharge_tick--;
    
    if(world()->bonkOverlappingActor(this)){}
    
    if (m_initiated_jump and m_jump_distance>0){
        if(!world()->isMovePossible(this,getX(),getY()+4)){ //blocks movement
            world()->bonkOverlappingActor(this);
            m_jump_distance = 0;
        }
        else{
            goTo(getX(),getY()+4);
            m_jump_distance--;
        }
    }
    else{ //m_jump_distance == 0
        if(world()->isMovePossible(this,getX(),getY()-3)){
            goTo(getX(),getY()-4);
        }
        else{m_initiated_jump = false;}
//        m_initiated_jump = false;
    }
    
    
    int ch;
    if (world()->getKey(ch)){
        switch(ch){
            case KEY_PRESS_LEFT:
                setDirection(left);
                if (world()->moveOrBonk(this,getX()-4,getY())){
                }
                break;
//                goTo(getX()-4,getY());
//                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if (world()->moveOrBonk(this,getX()+4,getY())){
                }
                break;
//                else{
//                    goTo(getX()+4,getY());
//                    break;
//                }
    
            case KEY_PRESS_UP:
//                goTo(getX(),getY()+4);
                
                if (m_initiated_jump){}
                else if (!m_initiated_jump and world()->isMovePossible(this, getX(),getY()-1)){
                    if(!m_jump_power){
                        m_jump_distance = 8;
                        m_initiated_jump = true;
                        world()->playSound(SOUND_PLAYER_JUMP);
                    }
                    else{
                        m_jump_distance = 12;
                        m_initiated_jump = true;
                        world()->playSound(SOUND_PLAYER_JUMP);
                    }
                }
                break;
            case KEY_PRESS_DOWN:
                goTo(getX(),getY()-4);
                break;
            case KEY_PRESS_SPACE:
                if(!m_shoot_power){}
                else if(m_recharge_tick > 0){}
                
                else if (m_recharge_tick == 0){
                    world()->playSound(SOUND_PLAYER_FIRE);
                    m_recharge_tick = 8;
                    
//                    world()->addActor(new PiranhaFireball(world(),getX(),getY(),right));
                
                    
                    if (this->getDirection()==right){
                        world()->addActor(new PeachFireball(world(),(getX()/SPRITE_WIDTH),getY()/SPRITE_HEIGHT,right));
//                        cout << getY() << endl;
//                        cout << SPRITE_HEIGHT << endl;
                    }
                    else if (this->getDirection()==left){
                        world()->addActor(new PeachFireball(world(),(getX()/SPRITE_WIDTH),getY()/SPRITE_HEIGHT,left));
                    }
                }
                break;
            default:
                break;
        }
    }
    return;
}

void Peach::goTo(int x, int y){
    if(world()->moveIfPossible(this,x,y)){
    }

}

void Peach::getBonked(bool bonkerIsInvinciblePeach){
    if (m_invincible or m_temporary_invincible){
    }
    else{ //Peach is not invincible
        if (m_health_point == 0){
            this->setDead();
            return;
        }
        m_health_point--;
        m_temporary_ticks = 10;
        m_temporary_invincible = true;
        if (m_shoot_power){
            m_shoot_power = false;
        }
        if (m_jump_power){
            m_jump_power = false;
        }
        if (m_health_point >= 1){
            world()->playSound(SOUND_PLAYER_HURT);
        }
    }
}

void Peach::sufferDamageIfDamageable(){
    getBonked(m_invincible);
}

void Peach::setHP(int hp){
    m_health_point=hp;
}

void Peach::gainInvincibility(int ticks){
    m_ticks = ticks;
    if (m_ticks > 0){
        m_invincible = true;
    }
}

void Peach::gainShootPower(){
    m_temporary_invincible = true;
    m_temporary_ticks = 10;
    m_shoot_power = true;
}

void Peach::gainJumpPower(){
    m_temporary_invincible = true;
    m_temporary_ticks = 10;
    m_jump_power = true;
}

bool Peach::isInvincible() const{
    return m_invincible;
}

bool Peach::hasShootPower() const{
    return m_shoot_power;
}

bool Peach::hasJumpPower() const{
    return m_jump_power;
}
//PEACH SECTION

//OBSTACLE SECTION
bool Obstacle::blocksMovement() const{
    return true;
}

void Obstacle::getBonked(bool bonkerIsInvinciblePeach){
    getBonkedSub(bonkerIsInvinciblePeach);
}
//OBSTACLE SECTION

//BLOCK SECTION
void Block::getBonkedSub(bool bonkerIsInvinciblePeach){
    if(m_goodie == Block::none){
        world()->playSound(SOUND_PLAYER_BONK);
    }
    else{ //block holds goodie and block has not been bonked
        world()->playSound(SOUND_POWERUP_APPEARS);

//        if (m_goodie == Block::flower) {world()->addActor(new Goodie(world(),IID_FLOWER,this->getX(),this->getY()+SPRITE_HEIGHT));}
        if (m_goodie == Block::flower) {world()->addActor(new Flower(world(),getX()/SPRITE_WIDTH,(getY()/SPRITE_HEIGHT)+1));}
//        cout << getY() << endl;
        if (m_goodie == mushroom) {world()->addActor(new Mushroom(world(),getX()/SPRITE_WIDTH,(getY()/SPRITE_HEIGHT)+1));}
        if (m_goodie == star) {world()->addActor(new Star(world(),getX()/SPRITE_WIDTH,(getY()/SPRITE_HEIGHT)+1));}
        m_goodie=none;
    }
}
//BLOCK SECTION

void Pipe::getBonkedSub(bool bonkerIsInvinciblePeach){
    world()->playSound(SOUND_PLAYER_BONK);
}

void LevelEnder::doSomethingAux(){
    if (world()->overlapsPeach(levelPointer())){
        world()->increaseScore(1000);
        setDead();
        doSomethingAuxSub();
    }
}

//void Mario::doSomethingAux(){
//    if (world()->overlapsPeach(levelPointer())){
//        world()->increaseScore(1000);
//        setDead();
//    }
//}
//
//void Flag::doSomethingAux(){
//    if (world()->overlapsPeach(levelPointer())){
//        world()->increaseScore(1000);
//        setDead();
//    }
//}

//FLAG SECTION
void Flag::doSomethingAuxSub(){
    world()->endLevel(false);
}

LevelEnder* Flag::levelPointer(){
    return this;
}
//FLAG SECTION

//MARIO SECTION
LevelEnder* Mario::levelPointer(){
    return this;
}

void Mario::doSomethingAuxSub(){
    world()->endLevel(true);
}
//MARIO SECTION

//GOODIE SECTION
void Goodie::doSomethingAux(){
    if(world()->overlapsPeach(this)){
//        world()->increaseScore(50);
//        world()->grantJumpPower();
        doSomethingAuxSub();
        world()->setPeachHP(2);
        this->setDead();
        world()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(world()->isMovePossible(this, this->getX(), this->getY()-2)){
        fallIfPossible(2);
    }
    else{
        if(this->getDirection() == right){
            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
                moveTo(this->getX()+2,this->getY());
            }
            else{
//                this->reverseDirection();
                this->setDirection(left);
                return;
            }
        }
        else if (this->getDirection() == left){
            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
                moveTo(this->getX()-2,this->getY());
            }
            else{
//                this->reverseDirection();
                this->setDirection(right);
                return;
            }
        }
    }
}
//GOODIE SECTION

//FLOWER SECTION
void Flower::doSomethingAuxSub(){
    world()->increaseScore(50);
    world()->grantShootPower();
//    if(world()->overlapsPeach(this)){
//        world()->increaseScore(50);
//        world()->grantShootPower();
//        world()->setPeachHP(2);
//        this->setDead();
//        world()->playSound(SOUND_PLAYER_POWERUP);
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//    }
}
//FLOWER SECTION

//MUSHROOM SECTION
void Mushroom::doSomethingAuxSub(){
    world()->increaseScore(75);
    world()->grantJumpPower();
//    if(world()->overlapsPeach(this)){
//        world()->increaseScore(75);
//        world()->grantJumpPower();
//        world()->setPeachHP(2);
//        this->setDead();
//        world()->playSound(SOUND_PLAYER_POWERUP);
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//    }
}
//MUSHROOM SECTION

//STAR SECTION
void Star::doSomethingAuxSub(){
    world()->increaseScore(100);
    world()->grantInvincibility(150);
//    if(world()->overlapsPeach(this)){
//        world()->increaseScore(100);
//        world()->grantInvincibility(150);
//        this->setDead();
//        world()->playSound(SOUND_PLAYER_POWERUP);
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->reverseDirection();
//                return;
//            }
//        }
//    }
}
//STAR SECTION

void Projectile::doSomethingAux(){
    if (doSomethingAuxSub()){
        this->setDead();
        return;
    }
    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
        fallIfPossible(2);
    else{
        if(this->getDirection() == right){
            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
                moveTo(this->getX()+2,this->getY());
            }
            else{
                this->setDead();
                return;
            }
        }
        else if (this->getDirection() == left){
            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
                moveTo(this->getX()-2,this->getY());
            }
            else{
                this->setDead();
                return;
            }

        }

    }
}

bool PiranhaFireball::doSomethingAuxSub(){
    return world()->damageOverlappingPeach(this);
}

////PIRANHAFIREBALL SECTION
//void PiranhaFireball::doSomethingAux(){
//    if (world()->damageOverlappingPeach(this)){
//        this->setDead();
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//
//        }
//
//    }
//}
//PIRANHAFIREBALL SECTION

bool PeachFireball::doSomethingAuxSub(){
    return world()->damageOverlappingActor(this);
}
//PEACHFIREBALL SECTION
//void PeachFireball::doSomethingAux(){
//    if (world()->damageOverlappingActor(this)){
////        this->setDead();
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//
//        }
//
//    }
//}
//PEACHFIREBALL SECTION

bool Shell::doSomethingAuxSub(){
    return world()->damageOverlappingActor(this);
}
//SHELL SECTION
//void Shell::doSomethingAux(){
//    if (world()->damageOverlappingActor(this)){
//        this->setDead();
//        return;
//    }
//    if(world()->isMovePossible(this, this->getX(), this->getY()-2))
//        fallIfPossible(2);
//    else{
//        if(this->getDirection() == right){
//            if(world()->isMovePossible(this,this->getX()+2,this->getY())){
//                moveTo(this->getX()+2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//        }
//        else if (this->getDirection() == left){
//            if(world()->isMovePossible(this,this->getX()-2,this->getY())){
//                moveTo(this->getX()-2,this->getY());
//            }
//            else{
//                this->setDead();
//                return;
//            }
//
//        }
//
//    }
//}
//SHELL SECTION

//ENEMY SECTION
void Enemy::getBonked(bool bonkerIsInvinciblePeach){
    if (!world()->bonkOverlappingPeach(this)){
        
    }
    else{ //bonker is Peach
        if (bonkerIsInvinciblePeach){
            world()->playSound(SOUND_PLAYER_KICK);
            world()->increaseScore(100);
            this->setDead();
            return;
        }
    }
}

void Enemy::sufferDamageIfDamageable(){
    world()->increaseScore(100);
    this->setDead();
}

void Enemy::doSomethingAux(){
    if (world()->overlapsPeach(this)){
        if(world()->bonkOverlappingPeach(this)){}
        return;
    }
    if (this->getDirection() == right){
        if (world()->isMovePossible(this, this->getX()+1, this->getY())){
            if (world()->isMovePossible(this, this->getX()+SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT)){
                this->setDirection(left);
            }
            else{
                moveTo(this->getX()+1,this->getY());
            }
        }
        else {
            this->setDirection(left);
        }
    }
    else if (this->getDirection() == left){
        if (world()->isMovePossible(this, this->getX()-1, this->getY())){
            if (world()->isMovePossible(this, this->getX()-SPRITE_WIDTH, this->getY()-SPRITE_HEIGHT)){
                this->setDirection(right);
            }
            else{
                moveTo(this->getX()-1,this->getY());
            }
        }
        else {
            this->setDirection(right);
        }
    }
}
//ENEMY SECTION

//PIRANHA SECTION
void Piranha::doSomethingAux(){
//    int currentX = this->getX();
//    int currentY = this->getY();
    this->increaseAnimationNumber();

    if (world()->overlapsPeach(this)){
        if(world()->bonkOverlappingPeach(this)){}
        return;
    }
    int xDeltaFromActor;
    int fireball_dir;
    if (world()->getPeachTargetingInfo(this, 1.5*SPRITE_HEIGHT, xDeltaFromActor)){
//            (positive means Peach is to the right of a)
        if (xDeltaFromActor > 0){
            this->setDirection(right);
            fireball_dir = right;
            xDeltaFromActor = xDeltaFromActor + SPRITE_WIDTH - 1;
        }
        else{
            this->setDirection(left);
            fireball_dir = left;
            xDeltaFromActor = xDeltaFromActor - SPRITE_WIDTH + 1;
        }
        if (m_fire_delay>0){
            m_fire_delay--;
            return;
        }
        else{ //no fire_delay
            if(abs(xDeltaFromActor)<8*SPRITE_WIDTH){
//                if (fireball_dir == right){
//                    world()->addActor(new PiranhaFireball(this->world(),this->getX()+SPRITE_WIDTH-1+10,this->getY(),fireball_dir));
//                    world()->playSound(SOUND_PIRANHA_FIRE);
//                    m_fire_delay = 40;
//                }
                world()->addActor(new PiranhaFireball(this->world(),getX()/SPRITE_WIDTH,getY()/SPRITE_HEIGHT,fireball_dir));
                world()->playSound(SOUND_PIRANHA_FIRE);
                m_fire_delay = 40;
            }
        }
    }
    else{
        return;
    }

}
//PIRANHA SECTION

void Koopa::sufferDamageIfDamageable(){
    world()->increaseScore(100);
    
    if (this->getDirection()==right){
        this->setDead();
        world()->addActor(new Shell(world(),(getX()/8)+1,getY()/8,right));
    //                        cout << SPRITE_HEIGHT << endl;
    }
    else if (this->getDirection()==left){
        this->setDead();
        world()->addActor(new Shell(world(),(getX()/8)-1,getY()/8,left));
    }
//                        cout << getY() << endl;
//                        cout << SPRITE_HEIGHT << endl;
    
//    cout << getX() << endl;
//    cout << getY() << endl;
//    this->setDead();

}

//bool Koopa::blocksMovement() const{
//    return true;
//}

//void Koopa::doSomeethingAux(){
//    if (this->getDirection()==right){
//        world()->addActor(new Shell(world(),20,20,right));
//    //                        cout << getY() << endl;
//    //                        cout << SPRITE_HEIGHT << endl;
//    }
//    else if (this->getDirection()==left){
//        world()->addActor(new Shell(world(),(getX()/SPRITE_WIDTH)-1,getY()/SPRITE_HEIGHT,left));
//    }
//}

