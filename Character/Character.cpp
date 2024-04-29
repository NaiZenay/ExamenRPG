//
// Created by Victor Navarro on 13/02/24.
//
#include "Character.h"
#include <cstring>

Character::Character(const char *_name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    strncpy(this->name,_name,15);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

void Character::setName(const char * _name) {
    strncpy(this->name,_name,15);
}
 const char * Character::getName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    return "Name: " + (string)name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " +
           to_string(defense) + "\nSpeed: " + to_string(speed)+"\n=========================";
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::isDead() {
    return dead;
}

bool Character::isCoward() {
    return coward;
}

void Character::setDead(bool dead) {
    this->dead = dead;
}

void Character::setCoward(bool _coward) {
    this->coward = _coward;
}

int Character::getDamage() {
    return this->damage;
}

void Character::setDamage(int damage) {
    this->damage += damage;
}
