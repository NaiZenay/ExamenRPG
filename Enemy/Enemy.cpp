//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>
#include "vector"
#include "algorithm"
#include "climits"

using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(const char * name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                      speed, false) {
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::die() {
    cout << this->getName()<<" die" << endl;
    this->dead = true;
}

void Enemy::takeDamage(int damage) {
    this->setDamage(damage);
    cout << getName() << " has taken " << damage << " damage" << endl;

    if (this->getDamage() >= this->getHealth()) {
        die();
    }

}

Character *Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for (int i = 0; i < teamMembers.size(); i++) {
        if (teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    Character *target = getTarget(player);
    myAction.source = this;
    myAction.target = target;

    if (this->getHealth() - this->getDamage() <= this->getHealth() * 0.15) {
        myAction.action = [this, player]() {
            flee(player);
        };
    } else {
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }
    return myAction;
}

static bool compareSpeed(Player *a, Player *b) {
    return a->getSpeed() > b->getSpeed();
}


void Enemy::flee(vector<Player *> players) {
    std::sort(players.begin(), players.end(), compareSpeed);
    Player *fastestPlayer = players[0];
    bool fleed = false;
    if (this->getSpeed() > fastestPlayer->getSpeed()) {
        cout << "Enemy flee" << endl;
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }
    this->setCoward(fleed);
}


Enemy::Enemy(const char *unnamed, int unnamed1, int unnamed2, int unnamed3, int unnamed4, bool unnamed5)
        : Character(unnamed, unnamed1, unnamed2, unnamed3, unnamed4, unnamed5) {

}

void Enemy::checkPlayerLevel(vector<Player *> teamMembers) {
    switch (teamMembers[0]->getLevel()) {
        case 1:
            levelUp();
            break;
        case 2:
            levelUp();
            break;
        case 3:
            levelUp();
            break;
        case 4:
            levelUp();
            break;
        case 5:
            levelUp();
            break;
        case 6:
            levelUp();
            break;
        case 7:
            levelUp();
            break;
        case 8:
            levelUp();
            break;
        case 9:
            levelUp();
            break;
        case 10:
            levelUp();
            break;
        default:
            cout<<"fk u alex"<<endl;
            break;
    }
}

void Enemy::levelUp() {
    this->health+=15;
    this->attack+=5;
    this->defense+=3;
    this->speed+=1;
    cout<<"Enemy Stats\nhealth: "<<health<<" atk: "<<attack<< " defense: "<<defense<<" speed :"<< speed<<endl;
}


