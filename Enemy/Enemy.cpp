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

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
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

