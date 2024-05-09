//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H

#include<string>
#include "../Combat/Action.h"
#include "memory"
#include "vector"

using namespace std;

class Character {
protected:
    char name[20];
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool dead;
    bool coward=false;
    int damage=0;
    int level;
public:
    Character(const char *, int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;

    virtual void takeDamage(int damage) = 0;

    virtual void die() = 0;

    virtual void levelUp()=0;

    int getLevel() const;

    void setLevel(int level);

    void setName(const char *);

    const char * getName();

    void setHealth(int);

    int getHealth();

    void setAttack(int);

    int getAttack();

    void setDefense(int);

    int getDefense();

    void setSpeed(int);

    int getSpeed();

    string toString();

    bool getIsPlayer();

    bool isDead();

    bool isCoward();

    void setDead(bool dead);

    void setCoward(bool _coward);

    int getDamage();

    void setDamage(int damage);

};


#endif //RPG_CHARACTER_H
