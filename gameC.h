#ifndef GAME_H
#define GAME_H

// #include "nonClassFunctions.h"
#include "equipmentC.h"
#include "potionsC.h"
#include "entityC.h"
#include "mapC.h"

class Game
{
private:
    vector<Entity> _players;
    vector<Entity> _enemies;
    vector<Potions> _allPotions;
    vector<Equipment> _allEquip;

public:
    vector<string> riddlesQ;
    vector<string> riddlesA;

public:
    // getters and setters
    int getPlayerSize();
    int getEnemySize();
    int getPotionsSize();
    Entity getPlayer(int playerIndexNumber);
    Entity getEnemy(int enemyIndexNumber);
    Potions getPotion(int potionIndexNumber);
    Equipment getEquipmentViaName(string equipmentName); // return index of item location based on name
    Potions getPotionViaName(string potionName);         // return index of item location based on name
    void eraseEnemy(int index);
    // Entity getEnemyViaName(string enemyName); // return index of the enemy location based on name

    // loading
    void loadPlayers(string filename);
    void loadEntities(string filename);
    void loadPotions(string filename);
    void loadEquipment(string filename);
    void loadRiddles(string filename);
    void loadPlayerStartingGear(Entity& player);
    void loadEnemyStartingGear(Entity& enemy);

    // combat
    void combat(Entity& player, Entity& player2, char type, Game& game);
    double attackerDamagesDefender(double defenderDef, int attackerDmg, char defenderElementalWeakness, char attackerWeaponElement);
    bool islandFightEndConditions(Entity enemy, Entity player);
    bool epicFightEndConditions(Entity enemy, Entity player, Entity player2);
    bool ult(Entity& player, Entity& player2, Entity& enemy, Game& game, double& playerDMGmult, double& enemyDMGmult);

    // shop functions
    void generateShop(Entity& player);
    string displayDmgOrDefString(Equipment equipment);
    double displayDmgOrDefNum(Equipment equipment);
    string shopEquipBuyChoiceVal(string input, int ind1, int ind2, int ind3);
    string shopPotionBuyChoiceVal(string input, int ind1, int ind2, int ind3);
    void shuffleEquip(vector<Equipment> equip);
    void shufflePotion(vector<Potions> potions);

    // players
    int playerOptionMenu(Entity& player);
    void tileAction(int tileType, Entity& player, Entity& player2, Map& map, Game& game, int playerTurn);
};

#endif