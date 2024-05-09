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
    Enemy(const char *unnamed, int unnamed1, int unnamed2, int unnamed3, int unnamed4, bool unnamed5);

public:
    void powerUp(int powerUpHealth, int powerUpattack , int powerUpDefese, int powerUpSpeed);
    void doAttack(Character *target) override;

    void takeDamage(int damage) override;

    void die() override;

    void levelUp() override;

    void flee(vector<Player *> players);

    Character *getTarget(vector<Player *> teamMembers);

    Action takeAction(vector<Player *> player);
};


#endif //RPG_ENEMY_H
