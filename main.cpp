#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

//Jugador no huye cuando es mas lento q los enemigos(el programa termina)


int main() {
    Player *player = new Player("Victor", 1, 1, 0, 1);
    Enemy *enemy = new Enemy("Goblin", 20, 5, 0, 7);
    Enemy *enemy2 = new Enemy("Orc", 100, 8, 0, 2);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
