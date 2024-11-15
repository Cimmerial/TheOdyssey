#ifndef ENTITY_H
#define ENTITY_H

#include "helperC.h"
#include "potionsC.h"
#include "equipmentC.h"

class Entity
{
private:
    string _name;
    char _type;
    double _hp;
    double _stam;
    double _def;
    char _condition;
    bool advantage;
    char elemental_weakness;
    int gold;
    vector<string> _tempGear; // temporarily stores gear until it can be turned into Equipment instance
    vector<Potions> _potions;
    vector<Equipment> _equipped; // {weapon first, then shield}
    vector<Equipment> _inventory;
    int _itemCount[2]; // {potion amount, total equipment amount}
    int _maxHP;
    int _maxStam;
    bool skipPlayer;
    int calamityChance;
    double totalGoldgained;
    double totalDamageDealt;
    double totalDamageTaken;
    int totalMisses;
    double bonusDamage;
    string ult;
    int ultCharge;

    // not added to entity initialization yet
    // ultimate
public:
    // getters and setters
    string getName();
    char getType();
    double getHp();
    double getStam();
    double getDef();
    char getCondition();
    bool getAdvantage();
    char getElementalWeakness();
    int getGold();
    int getMaxHp();
    int getMaxStam();
    double getBonusDamage();
    bool getSkip();
    void setSkip(bool skip);
    int getCalamityChance();
    void changeCalamityChance(int calamity);
    void changeTotalDamageDealt(double damage);
    void addMiss();
    void getTotals();
    double getTotalGold();
    double getTotalDamage();
    double getTotalDamageTaken();
    string getTempGear(int index);
    int getMisses();
    Equipment getEquipped(int equippedIndex);
    Potions getPotions(int potionIndex);
    Equipment getInventory(int inventoryIndex);
    int getEquippedSize();
    int getPotionsSize();
    int getInventoySize();
    int getPotionCount();
    void changeHp(double hp);
    void changeStam(double stam);
    void changeDef(double def);
    void setCondition(char condition);
    void setAdvantage(bool adv);
    void setElementalWeakness(char eleWeak);
    void changeGold(int gold_);
    void changeMaxStam(int maxStam);
    void changeMaxHp(int maxHp);
    void addBonusDamage(int bonus);
    Potions getPotionFromEntity(int potionIndex);
    Equipment getEquippedEquipmentFromEntity(int equipmentIndex);
    Equipment getInventoryEquipmentFromEntity(int equipmentIndex);
    void eraseEquipment(int index);
    void erasePotions(int index);
    void setUltCharge(bool charge);
    int getUltCharge();
    void changeUltCharge(int change);
    string getUlt();

    // initialization
    Entity(string entityLine);
    Entity();
    void initializePlayer(string playerLine);
    void initializeIslandEnemy(string islandEnemyLine);
    void initializeEpicEnemy(string epicEnemyLine);

    // item modulation
    int swap();
    int drop();
    int usePotion();
    void updateEquipment(Equipment equipment);
    void updatePotion(Potions potion);

    // menus
    void entityStatsmenu();

    // player
    void poisonOrDeseaseTick();
};

#endif