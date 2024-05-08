//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include "vector"
#include "algorithm"
#include "memory"
#include <cstring>

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(const char * name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    experience = 0;
    level = 1;
}
Player::Player(const char * name, int health, int attack, int defense, int speed,bool isPlayer,int _exp,int _level) : Character(name, health, attack, defense,speed, true) {
    experience = _exp;
    level = _level;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::die() {
    cout << this->getName()<<" die" << endl;
    this->dead = true;
}

void Player::takeDamage(int damage) {
    setDamage(damage);
    cout << getName() << " has taken " << damage << " damage" << endl;

    if (this->getDamage() >= this->getHealth()) {
        die();
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(nullptr));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }

    //Aqui termina el programa
    if (!fleed){
        cout<<"U didnt flee"<<endl;
    }else{
        this->setCoward(fleed);
    }
}

void Player::emote() {
    cout << this->getName()<<" Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    cout << "Choose an action" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Flee" << endl;
    cin >> option;
    Character *target = nullptr;

    Action myAction;
    myAction.speed = this->getSpeed();
    myAction.source = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;

        case 2:
            myAction.action = [this,enemies]() {
                flee(enemies);
            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    return myAction;
}

char *Player::serialize() {
    char* iterator=buffer;
    memcpy(iterator,&name, sizeof name);
    iterator += sizeof name;
    memcpy(iterator, &health, sizeof health);
    iterator += sizeof health;
    memcpy(iterator,&attack, sizeof attack);
    iterator += sizeof attack;
    memcpy(iterator, &defense, sizeof defense);
    iterator += sizeof defense;
    memcpy(iterator,&speed, sizeof speed);
    iterator += sizeof speed;
    memcpy(iterator, &isPlayer, sizeof isPlayer);
    iterator += sizeof isPlayer;
    memcpy(iterator,&dead, sizeof dead);
    iterator += sizeof dead;
    memcpy(iterator, &experience, sizeof experience);
    iterator += sizeof experience;
    memcpy(iterator,&level, sizeof level);
    iterator += sizeof level;

}

Player *Player::unserialize(char *_buffer) {
    char* _iterator =_buffer;
    char _name[20];
    int _health;
    int _attack;
    int _defense;
    int _speed;
    bool _isPlayer;
    bool _dead;
    int _experience;
    int _level;

    memcpy(&_name, _iterator, sizeof _name);
    _iterator += sizeof _name;
    memcpy(&_health, _iterator, sizeof _health);
    _iterator += sizeof _health;
    memcpy(&_attack, _iterator, sizeof _attack);
    _iterator += sizeof _attack;
    memcpy(&_defense, _iterator, sizeof _defense);
    _iterator += sizeof _defense;
    memcpy(&_speed, _iterator, sizeof _speed);
    _iterator += sizeof _speed;
    memcpy(&_isPlayer, _iterator, sizeof _isPlayer);
    _iterator += sizeof _isPlayer;
    memcpy(&_dead, _iterator, sizeof _dead);
    _iterator += sizeof _dead;
    memcpy(&_experience, _iterator, sizeof _experience);
    _iterator += sizeof _experience;
    memcpy(&_level, _iterator, sizeof _level);
    _iterator += sizeof _level;

    return new Player(_name, _health, _defense, _isPlayer, _experience, _level, _experience, _level);
}



