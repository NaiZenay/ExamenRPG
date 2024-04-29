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

public:
    Enemy(const char *, int, int, int, int);

public:

    void doAttack(Character *target) override;

    void takeDamage(int damage) override;

    void die() override;

    void flee(vector<Player *> players);

    Character *getTarget(vector<Player *> teamMembers);

    Action takeAction(vector<Player *> player);
};


#endif //RPG_ENEMY_H
