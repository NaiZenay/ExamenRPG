//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"

struct Action;

class Enemy;

class Player : public Character {
protected:
    int experience;
    int level;

public:
    Player(const char *_name, int _health, int _attack, int _defense, int _speed);
    Player(const char *_name, int _health, int _attack, int _defense, int _speed,bool _isPlayer,int _exp, int _level);

    void doAttack(Character *target) override;

    void takeDamage(int damage) override;

    void die() override;

    Character *getTarget(vector<Enemy *> enemies);

    char *serialize();
    static Player* unserialize(char* buffer);
    static const unsigned int BUFFER_SIZE =sizeof name + sizeof health + sizeof attack + sizeof defense + sizeof speed + sizeof isPlayer +
                                           sizeof dead + sizeof experience + sizeof level;

    void flee(vector<Enemy *> enemies);

    void emote();

    void levelUp();

    void gainExperience(int);

    Action takeAction(vector<Enemy *> enemies);
private:
    char buffer[BUFFER_SIZE];

};


#endif //RPG_PLAYER_H
