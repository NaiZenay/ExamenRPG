//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H

#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"

struct Action;

class Player;

class Enemy : public Character {
    int damage = 0;
public:
    Enemy(string, int, int, int, int);

public:
    int getDamage();

public:
    void setDamage(int damage);

    void doAttack(Character *target) override;

    void takeDamage(int damage) override;

    void die() override;

    bool flee(vector<Player *> players);

    Character *getTarget(vector<Player *> teamMembers);

    Action takeAction(vector<Player *> player);
};


#endif //RPG_ENEMY_H
