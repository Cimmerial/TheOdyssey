#include "gameC.h"

// getters and setters
int Game::getPlayerSize()
{
    return _players.size();
}
int Game::getEnemySize()
{
    return _enemies.size();
}
int Game::getPotionsSize()
{
    return _allPotions.size();
}
Entity Game::getPlayer(int playerIndexNumber)
{
    return _players[playerIndexNumber];
}
Entity Game::getEnemy(int enemyIndexNumber)
{
    return _enemies[enemyIndexNumber];
}
Potions Game::getPotion(int potionIndexNumber)
{
    return _allPotions[potionIndexNumber];
}
Equipment Game::getEquipmentViaName(string equipmentName) // return index of item location based on name
{
    for (size_t i = 0; i < _allEquip.size(); i++)
    {
        if (_allEquip[i].getName() == equipmentName) // using getname, check index over name
        {
            return _allEquip[i];
        }
    }
    return _allEquip[_allEquip.size() - 1];
}
Potions Game::getPotionViaName(string potionName) // return index of item location based on name
{
    for (size_t i = 0; i < _allPotions.size(); i++)
    {
        if (_allPotions[i].getName() == potionName) // using getname, check index over name
        {
            return _allPotions[i];
        }
    }
    return _allPotions[_allPotions.size() + 1];
}
void Game::eraseEnemy(int index)
{
    vector<Entity> dummyEnemyVect;
    for (size_t i = 0; i < _enemies.size(); i++)
    {
        if (i != index)
        {
            dummyEnemyVect.push_back(_enemies[i]);
        }
    }
    _enemies = dummyEnemyVect;
    // _enemies.erase(_enemies.begin() + index);
}
// Entity Game::getEnemyViaName(string enemyName) // return index of the enemy location based on name
// {
//     for (size_t i = 0; i < _enemies.size(); i++)
//     {
//         if (_enemies[i].getName() == enemyName) // using getname, check index over name
//         {
//             return _enemies[i];
//         }
//     }
//     return _enemies[_enemies.size() + 1];
// }

// loading
void Game::loadPlayers(string filename)
{
    ifstream file_in(filename);
    if (file_in.fail())
    {
        cout << "Player load failed"
             << "|";
    }
    else
    {
        cout << "Players loaded"
             << "|";
    }
    string tempLine;
    while (getline(file_in, tempLine))
    {
        Entity player(tempLine);
        _players.push_back(player); // stores each "player" within the _players vector
    }
}
void Game::loadEntities(string filename)
{
    ifstream file_in(filename);
    if (file_in.fail())
    {
        cout << "Entity load failed!"
             << " ";
    }
    else
    {
        cout << "Entities loaded"
             << "|";
    }
    string tempLine;

    while (getline(file_in, tempLine))
    {
        Entity enemy(tempLine);
        _enemies.push_back(enemy); // stores each "enemies" within the _enemies vector
    }
}
void Game::loadPotions(string filename)
{
    ifstream file_in(filename);
    if (file_in.fail())
    {
        cout << "Potion load failed!"
             << "|";
    }
    else
    {
        cout << "Potions loaded"
             << "|";
    }
    string tempLine;
    while (getline(file_in, tempLine))
    {
        Potions potion(tempLine);
        _allPotions.push_back(potion); // stores each "potion" within the _allPotions vector
    }
}
void Game::loadEquipment(string filename)
{
    ifstream file_in(filename);
    if (file_in.fail())
    {
        cout << "Equipment load failed!"
             << "|";
    }
    else
    {
        cout << "Equipment loaded"
             << "|";
    }
    string tempLine;
    while (getline(file_in, tempLine))
    {
        Equipment equipment(tempLine);
        _allEquip.push_back(equipment); // stores each "equipment" within the allEquipment vector
    }
}
void Game::loadRiddles(string filename)
{
    ifstream file_in(filename);
    if (file_in.fail())
    {
        cout << "Riddle load failed!"
             << "|";
    }
    else
    {
        cout << "Riddles loaded" << endl
             << endl;
    }
    string tempLine;
    string tempArr[2];
    while (getline(file_in, tempLine))
    {
        split(tempLine, '|', tempArr, 2);
        riddlesQ.push_back(tempArr[0]);
        riddlesA.push_back(tempArr[1]);
        tempArr[0] = "", tempArr[1] = "";
    }
}
void Game::loadPlayerStartingGear(Entity &player)
{
    // cout << "loadstartinggear start" << endl;
    player.updatePotion(getPotionViaName(player.getTempGear(0)));
    cout << "potions size and name";
    cout << player.getPotionsSize() << endl;
    cout << player.getPotions(1).getName() << endl;
    // cout << player.getName() << endl;
    player.updateEquipment(getEquipmentViaName(player.getTempGear(1)));
    // cout << player.getEquipped(0).getName() << endl;
    // cout << getPlayer(0).getEquippedSize() << endl;
    // cout << "loadstartingGear end" << endl;
}
void Game::loadEnemyStartingGear(Entity &enemy)
{
    enemy.updatePotion(getPotionViaName(enemy.getTempGear(0)));
    enemy.updateEquipment(getEquipmentViaName(enemy.getTempGear(1))); // stores equip in both equipment slots
    enemy.updateEquipment(getEquipmentViaName(enemy.getTempGear(1)));
}

// combat
void Game::combat(Entity &player, Entity &player2, char type, Game &game)
{
    int enemyIndex = rand() % _enemies.size();
    if (type == 'I')
    {
        double enemyDMGmult = 1;
        double playerDMGmult = 1;
        bool circesDominion = false;
        bool playerTurnOver = false;
        cout << "You crash into another island" << endl;
        while (game._enemies[enemyIndex].getType() != 'I') // only allows an island enemy to get chosen
        {
            enemyIndex = rand() % _enemies.size();
        }
        _enemies.push_back(_enemies[enemyIndex]);       // duplicates and stores enemy on end of array
        int duplicatedEnemyIndex = _enemies.size() - 1; // new index for duplicated enemy
        bool enemyGoesFirst = false;
        if (player.getAdvantage() == false && _enemies[duplicatedEnemyIndex].getAdvantage() == true)
        {
            enemyGoesFirst = true;
            cout << _enemies[duplicatedEnemyIndex].getName() << " starts!" << endl;
        }
        else if (player.getAdvantage() == true && _enemies[duplicatedEnemyIndex].getAdvantage() == false)
        {
            cout << player.getName() << " starts!" << endl;
        }
        else
        {
            if (0 == dieRollingTwoPlayers(_enemies[duplicatedEnemyIndex].getName(), player.getName()))
            {
                enemyGoesFirst = true;
                cout << _enemies[duplicatedEnemyIndex].getName() << " starts!" << endl;
            }
            else
            {
                cout << player.getName() << " starts!" << endl;
            }
        }
        if (enemyGoesFirst)
        {
            if (1 == fiveSidedDie()) // roll for hit
            {
                cout << _enemies[duplicatedEnemyIndex].getName() << " missed their attack!" << endl;
            }
            else
            {
                double def = 0;
                int attack = 0;
                if (player.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                {
                    def = player.getDef() + player.getEquipped(1).getDefense();
                }
                else
                {
                    def = player.getDef();
                }
                if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() == 0) // if weapon is defensive, enemy deals half the defense in damage
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() / 2 * enemyDMGmult;
                }
                else
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() * enemyDMGmult;
                }
                double damageDealt = attackerDamagesDefender(def, attack, player.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << player.getName() << "!" << endl;
                player.changeHp(damageDealt * -2.5);
                cout << player.getName() << " has " << player.getHp() << " health remaining" << endl;
            }
        }
        bool fightEnd = false;
        bool ran = false;
        while (true)
        {
            playerTurnOver = false;
            fightEnd = islandFightEndConditions(_enemies[duplicatedEnemyIndex], player);
            if (fightEnd) // checks to see if enemy and player both have > 0 hp
            {
                break;
            }
            // player turn
            cout << endl;
            player.entityStatsmenu();
            cout << "Make an Action!: (choose a number)" << endl;
            cout << "(1) Attack!" << endl;
            cout << "(2) Use Potion" << endl;
            cout << "(3) Swap Weapon" << endl;
            cout << "(4) Use Ultimate" << endl;
            cout << "(5) Retreat!" << endl;
            string combatChoice;
            getline(cin, combatChoice);
            combatChoice = islandCombatChoiceMenuVal(combatChoice);
            if (combatChoice == "1") // player attack sequence
            {
                if (1 == fiveSidedDie()) // roll for hit
                {
                    player.addMiss();
                    cout << player.getName() << " missed their attack!" << endl;
                }
                else
                {
                    double def = 0;
                    int attack = 0;
                    if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() != 0)
                    {
                        def = _enemies[duplicatedEnemyIndex].getDef() + getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense();
                    }
                    else
                    {
                        def = _enemies[duplicatedEnemyIndex].getDef();
                    }
                    attack = (player.getEquipped(0).getDamage() + player.getBonusDamage()) * playerDMGmult;
                    double damageDealt = 10 * attackerDamagesDefender(def, attack, _enemies[duplicatedEnemyIndex].getElementalWeakness(), player.getEquipped(0).getElement());
                    player.changeTotalDamageDealt(damageDealt);
                    if (player.getEquipped(0).getPoison())
                    {
                        cout << _enemies[duplicatedEnemyIndex].getName() << " is poisoned by " << player.getName() << "'s blade!" << endl;
                        _enemies[duplicatedEnemyIndex].setCondition('P');
                    }
                    cout << player.getName() << " deals " << damageDealt << " damage to " << _enemies[duplicatedEnemyIndex].getName() << "!" << endl;
                    _enemies[duplicatedEnemyIndex].changeHp(damageDealt * -3.5);
                    cout << _enemies[duplicatedEnemyIndex].getName() << " has " << _enemies[duplicatedEnemyIndex].getHp() << " health remaining" << endl;
                }
                playerTurnOver = true;
            }
            else if (combatChoice == "2")
            {
                int tempPotion = player.usePotion();
                if (tempPotion != 9)
                {
                    playerTurnOver = true;
                }
            }
            else if (combatChoice == "3")
            {
                int tempSwap = player.swap();
                if (tempSwap != 9)
                {
                    playerTurnOver = true;
                }
            }
            else if (combatChoice == "4")
            {
                if (player.getUltCharge() == 0)
                {
                    cout << "You have already expended your ultimate ability" << endl;
                }
                else
                {
                    playerTurnOver = true;
                    circesDominion = ult(player, player2, _enemies[duplicatedEnemyIndex], game, playerDMGmult, enemyDMGmult);
                }
            }
            else // retreat attempt
            {
                if (1 != fiveSidedDie())
                {
                    player.changeStam(-15);
                    cout << "Although " << player.getName() << " successfully ran, they lost 15 stamina!" << endl;
                    ran = true;
                    int runningHit = fiveSidedDie();
                    if (runningHit == 1 || runningHit == 2) // "Where Do You Think You're Going?"
                    {
                        cout << "Just before " << player.getName() << " escapes, " << _enemies[duplicatedEnemyIndex].getName() << " manages to hit them one last time..." << endl;
                        if (1 == fiveSidedDie()) // roll for hit
                        {
                            cout << _enemies[duplicatedEnemyIndex].getName() << " missed their attack!" << endl;
                        }
                        else
                        {
                            double def = 0;
                            int attack = 0;
                            if (player.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                            {
                                def = player.getDef() + player.getEquipped(1).getDefense();
                            }
                            else
                            {
                                def = player.getDef();
                            }
                            if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() == 0) // if weapon is defensive, enemy deals half the defense in damage
                            {
                                attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() / 2 * enemyDMGmult;
                            }
                            else
                            {
                                attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() * enemyDMGmult;
                            }
                            double damageDealt = attackerDamagesDefender(def, attack, player.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                            cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << player.getName() << "!" << endl;
                            player.changeHp(damageDealt * -2.5);
                            cout << player.getName() << " has " << player.getHp() << " health remaining" << endl;
                        }
                    }
                    break;
                }
                else
                {
                    player.changeStam(-10);
                    cout << player.getName() << " lost 10 stamina but still could not escape!" << endl;
                }
            }
            cout << endl;
            //---------------------------------------------------------------------------------------------
            fightEnd = islandFightEndConditions(_enemies[duplicatedEnemyIndex], player);
            if (fightEnd) // checks to see if enemy and player both have > 0 hp
            {
                break;
            }
            //---------------------------------------------------------------------------------------------
            if (playerTurnOver)
            {
                cout << endl;
                cout << "Current enemy stats:" << endl;
                _enemies[duplicatedEnemyIndex].entityStatsmenu();
                cout << endl;
                _enemies[duplicatedEnemyIndex].poisonOrDeseaseTick();
                if (1 == fiveSidedDie() && !circesDominion) // roll for hit
                {
                    cout << _enemies[duplicatedEnemyIndex].getName() << " missed their attack!" << endl;
                }
                else
                {
                    double def = 0;
                    int attack = 0;
                    if (player.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                    {
                        def = player.getDef() + player.getEquipped(1).getDefense();
                    }
                    else
                    {
                        def = player.getDef();
                    }
                    if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() == 0) // if weapon is defensive, enemy deals half the defense in damage
                    {
                        attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() / 2 * enemyDMGmult;
                    }
                    else
                    {
                        attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() * enemyDMGmult;
                    }
                    double damageDealt = attackerDamagesDefender(def, attack, player.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                    if (circesDominion)
                    {
                        cout << "This is Circe's dominion now." << endl;
                        cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << _enemies[duplicatedEnemyIndex].getName() << "!" << endl;
                        _enemies[duplicatedEnemyIndex].changeHp(damageDealt * -2.5);
                        cout << _enemies[duplicatedEnemyIndex].getName() << " has " << _enemies[duplicatedEnemyIndex].getHp() << " health remaining" << endl;
                        circesDominion = false;
                    }
                    else
                    {
                        cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << player.getName() << "!" << endl;
                        player.changeHp(damageDealt * -2.5);
                        cout << player.getName() << " has " << player.getHp() << " health remaining" << endl;
                    }
                }
            }
        }
        if (player.getHp() > 0 && !ran)
        {
            if (player.getStam() > 0)
            {
                player.updateEquipment(getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1))); // adds potion and equipment to player inv
                player.updatePotion(getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)));
                player.changeGold(_enemies[duplicatedEnemyIndex].getGold()); // adds gold to player
                cout << player.getName() << " collects " << _enemies[duplicatedEnemyIndex].getGold() << " gold, the " << getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getName() << " and one " << getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)).getName() << "!" << endl;
            }
            cout << endl;
            cout << "Would you like to visit the shop? (Y/N)" << endl;
            string shopOrNot;
            getline(cin, shopOrNot);
            shopOrNot = shopVisitQuestionVal(shopOrNot);
            if (shopOrNot == "Y" || shopOrNot == "y")
            {
                generateShop(player);
            }
            else
            {
                cout << "Happy sailing!" << endl;
            }
            eraseEnemy(duplicatedEnemyIndex);
            // _enemies.erase(_enemies.begin() + duplicatedEnemyIndex); // erases damaged or dead enemy from game class
        }
    }
    if (type == 'E')
    {
        double enemyDMGmult = 1;
        double playerDMGmult = 1;
        double player2DMGmult = 1;
        bool circesDominion = false;
        cout << "Epic encounter!" << endl;
        cout << "test" << endl;
        while (game._enemies[enemyIndex].getType() != 'E') // only allows an epic enemy to get chosen
        {
            cout << "test1" << endl;
            cout << game._enemies[enemyIndex].getName() << endl;
            enemyIndex = rand() % _enemies.size();
        }
        _enemies.push_back(_enemies[enemyIndex]);       // duplicates and stores enemy on end of array
        int duplicatedEnemyIndex = _enemies.size() - 1; // new index for duplicated enemy
        bool enemyGoesFirst = false;
        if (player.getAdvantage() == false && player2.getAdvantage() == false && _enemies[duplicatedEnemyIndex].getAdvantage() == true)
        {
            enemyGoesFirst = true;
            cout << _enemies[duplicatedEnemyIndex].getName() << " starts!" << endl;
        }
        else if ((player2.getAdvantage() == true && _enemies[duplicatedEnemyIndex].getAdvantage() == true) || (player.getAdvantage() == true && _enemies[duplicatedEnemyIndex].getAdvantage() == true))
        {
            if (0 == dieRollingTwoPlayers(_enemies[duplicatedEnemyIndex].getName(), "The Heroes"))
            {
                enemyGoesFirst = true;
                cout << _enemies[duplicatedEnemyIndex].getName() << " starts!" << endl;
            }
            else
            {
                cout << player.getName() << " and " << player2.getName() << " start!" << endl;
            }
        }
        if (enemyGoesFirst)
        {
            if (1 == fiveSidedDie()) // roll for hit
            {
                cout << _enemies[duplicatedEnemyIndex].getName() << " missed their attack!" << endl;
            }
            else
            {
                double def = 0;
                int attack = 0;
                double def2 = 0;
                int attack2 = 0;
                if (player.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                {
                    def = player.getDef() + player.getEquipped(1).getDefense();
                }
                else
                {
                    def = player.getDef();
                }
                if (player2.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                {
                    def2 = player2.getDef() + player2.getEquipped(1).getDefense();
                }
                else
                {
                    def2 = player.getDef();
                }
                if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() == 0) // if weapon is defensive, enemy deals half the defense in damage
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() / 2 * enemyDMGmult;
                    attack2 = attack;
                }
                else
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() * enemyDMGmult;
                    attack2 = attack;
                }
                double damageDealt = attackerDamagesDefender(def, attack, player.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << player.getName() << "!" << endl;
                double damageDealt2 = attackerDamagesDefender(def2, attack2, player2.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt2 << " damage to " << player2.getName() << "!" << endl;
                player.changeHp(damageDealt * -2.5);
                cout << player.getName() << " has " << player.getHp() << " health remaining" << endl;
                player2.changeHp(damageDealt2 * -2.5);
                cout << player2.getName() << " has " << player2.getHp() << " health remaining" << endl;
            }
        }
        bool fightEnd = false;
        while (true)
        {
            fightEnd = epicFightEndConditions(_enemies[duplicatedEnemyIndex], player, player2);
            if (fightEnd) // checks to see if enemy and both player both have > 0 hp
            {
                break;
            }
            // player turn
            if (player.getHp() > 0)
            {
                cout << endl;
                player.entityStatsmenu();
                cout << "Make an Action!: (choose a number)" << endl;
                cout << "(1) Attack!" << endl;
                cout << "(2) Use Potion" << endl;
                cout << "(3) Swap Weapon" << endl;
                cout << "(4) Use Ultimate" << endl;
                string combatChoice;
                getline(cin, combatChoice);
                combatChoice = epicCombatChoiceMenuVal(combatChoice);
                if (combatChoice == "1") // player attack sequence
                {
                    if (1 == fiveSidedDie()) // roll for hit
                    {
                        player.addMiss();
                        cout << player.getName() << " missed their attack!" << endl;
                    }
                    else
                    {
                        double def = 0;
                        int attack = 0;
                        if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() == 0)
                        {
                            def = _enemies[duplicatedEnemyIndex].getDef();
                        }
                        else
                        {
                            def = _enemies[duplicatedEnemyIndex].getDef() + getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense();
                        }
                        attack = (player.getEquipped(0).getDamage() + player.getBonusDamage()) * playerDMGmult;
                        double damageDealt = 10 * attackerDamagesDefender(def, attack, _enemies[duplicatedEnemyIndex].getElementalWeakness(), player.getEquipped(0).getElement());
                        player.changeTotalDamageDealt(damageDealt);
                        if (player.getEquipped(0).getPoison())
                        {
                            cout << _enemies[duplicatedEnemyIndex].getName() << " is poisoned by " << player.getName() << "'s blade!" << endl;
                            _enemies[duplicatedEnemyIndex].setCondition('P');
                        }
                        cout << player.getName() << " deals " << damageDealt << " damage to " << _enemies[duplicatedEnemyIndex].getName() << "!" << endl;
                        _enemies[duplicatedEnemyIndex].changeHp(damageDealt * -3.5);
                        cout << _enemies[duplicatedEnemyIndex].getName() << " has " << _enemies[duplicatedEnemyIndex].getHp() << " health remaining" << endl;
                    }
                }
                else if (combatChoice == "2")
                {
                    player.usePotion();
                }
                else if (combatChoice == "3")
                {
                    player.swap();
                }
                else
                {
                    if (player.getUltCharge() == 0)
                    {
                        cout << "You have already expended your ultimate ability" << endl;
                    }
                    else
                    {
                        circesDominion = ult(player, player2, _enemies[duplicatedEnemyIndex], game, playerDMGmult, enemyDMGmult);
                    }
                }
            }
            fightEnd = epicFightEndConditions(_enemies[duplicatedEnemyIndex], player, player2);
            if (fightEnd) // checks to see if enemy and both player both have > 0 hp
            {
                break;
            }
            //------------------------------------------------------------------------------------------------------
            // player2 turn
            if (player2.getHp() > 0)
            {
                if (player2.getHp() > 0)
                {
                    cout << endl;
                    player2.entityStatsmenu();
                    cout << "Make an Action!: (choose a number)" << endl;
                    cout << "(1) Attack!" << endl;
                    cout << "(2) Use Potion" << endl;
                    cout << "(3) Swap Weapon" << endl;
                    cout << "(4) Use Ultimate" << endl;
                    string combatChoice;
                    getline(cin, combatChoice);
                    epicCombatChoiceMenuVal(combatChoice);
                    if (combatChoice == "1") // player2 attack sequence
                    {
                        if (1 == fiveSidedDie()) // roll for hit
                        {
                            player2.addMiss();
                            cout << player2.getName() << " missed their attack!" << endl;
                        }
                        else
                        {
                            double def = 0;
                            int attack = 0;
                            if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() == 0)
                            {
                                def = _enemies[duplicatedEnemyIndex].getDef();
                            }
                            else
                            {
                                def = _enemies[duplicatedEnemyIndex].getDef() + getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense();
                            }
                            attack = (player2.getEquipped(0).getDamage() + player2.getBonusDamage()) * player2DMGmult;
                            double damageDealt = 10 * attackerDamagesDefender(def, attack, _enemies[duplicatedEnemyIndex].getElementalWeakness(), player2.getEquipped(0).getElement());
                            player2.changeTotalDamageDealt(damageDealt);
                            if (player2.getEquipped(0).getPoison())
                            {
                                cout << _enemies[duplicatedEnemyIndex].getName() << " is poisoned by " << player2.getName() << "'s blade!" << endl;
                                _enemies[duplicatedEnemyIndex].setCondition('P');
                            }
                            cout << player2.getName() << " deals " << damageDealt << " damage to " << _enemies[duplicatedEnemyIndex].getName() << "!" << endl;
                            _enemies[duplicatedEnemyIndex].changeHp(damageDealt * -3.5);
                            cout << _enemies[duplicatedEnemyIndex].getName() << " has " << _enemies[duplicatedEnemyIndex].getHp() << " health remaining" << endl;
                        }
                    }
                    else if (combatChoice == "2")
                    {
                        player2.usePotion();
                    }
                    else if (combatChoice == "3")
                    {
                        player2.swap();
                    }
                    else
                    {
                        if (player2.getUltCharge() == 0)
                        {
                            cout << "You have already expended your ultimate ability" << endl;
                        }
                        else
                        {
                            circesDominion = ult(player2, player, _enemies[duplicatedEnemyIndex], game, player2DMGmult, enemyDMGmult);
                        }
                    }
                }
            }
            fightEnd = epicFightEndConditions(_enemies[duplicatedEnemyIndex], player, player2);
            if (fightEnd) // checks to see if enemy and both player both have > 0 hp
            {
                break;
            }
            //------------------------------------------------------------------------------------------------------
            cout << endl;
            cout << "Current enemy stats:" << endl;
            _enemies[duplicatedEnemyIndex].entityStatsmenu();
            cout << endl;
            _enemies[duplicatedEnemyIndex].poisonOrDeseaseTick();
            if (1 == fiveSidedDie() && !circesDominion) // roll for enemy hit
            {
                cout << _enemies[duplicatedEnemyIndex].getName() << " missed their attack!" << endl;
            }
            else
            {
                double def = 0;
                int attack = 0;
                double def2 = 0;
                int attack2 = 0;
                if (player.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                {
                    def = player.getDef() + player.getEquipped(1).getDefense();
                }
                else
                {
                    def = player.getDef();
                }
                if (player2.getEquippedSize() == 2) // if the equipped vector is 2 long, add shield def to total def
                {
                    def2 = player2.getDef() + player2.getEquipped(1).getDefense();
                }
                else
                {
                    def2 = player.getDef();
                }
                if (getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() == 0) // if weapon is defensive, enemy deals half the defense in damage
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDefense() / 2 * enemyDMGmult;
                    attack2 = attack;
                }
                else
                {
                    attack = getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getDamage() * enemyDMGmult;
                    attack2 = attack;
                }
                double damageDealt = attackerDamagesDefender(def, attack, player.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                double damageDealt2 = attackerDamagesDefender(def2, attack2, player2.getElementalWeakness(), getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getElement());
                if (circesDominion)
                {
                    cout << "This is Circe's dominion now." << endl;
                    cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt + damageDealt2 << " damage to " << _enemies[duplicatedEnemyIndex].getName() << "!" << endl;
                    player.changeHp((damageDealt + damageDealt2) * -2.5);
                    cout << _enemies[duplicatedEnemyIndex].getName() << " has " << _enemies[duplicatedEnemyIndex].getHp() << " health remaining" << endl;
                    circesDominion = false;
                }
                else
                {
                    cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt << " damage to " << player.getName() << "!" << endl;
                    cout << _enemies[duplicatedEnemyIndex].getName() << " deals " << damageDealt2 << " damage to " << player2.getName() << "!" << endl;
                    player.changeHp(damageDealt * -2.5);
                    cout << player.getName() << " has " << player.getHp() << " health remaining" << endl;
                    player2.changeHp(damageDealt2 * -2.5);
                    cout << player2.getName() << " has " << player2.getHp() << " health remaining" << endl;
                }
            }
        }
        if (player.getHp() > 0 && player2.getHp() > 0) // let players loot if they both survive
        {
            cout << player.getName() << " and " << player2.getName() << " survived!" << endl;
            player.updateEquipment(getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1))); // adds potion and equipment to player inv
            player.updatePotion(getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)));
            player.changeGold(_enemies[duplicatedEnemyIndex].getGold()); // adds gold to player
            cout << player.getName() << " collects " << _enemies[duplicatedEnemyIndex].getGold() << " gold, the " << getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getName() << " and one " << getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)).getName() << "!" << endl;
            player2.updateEquipment(getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1))); // adds potion and equipment to player inv
            player2.updatePotion(getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)));
            player2.changeGold(_enemies[duplicatedEnemyIndex].getGold()); // adds gold to player
            cout << player2.getName() << " collects " << _enemies[duplicatedEnemyIndex].getGold() << " gold, the " << getEquipmentViaName(_enemies[duplicatedEnemyIndex].getTempGear(1)).getName() << " and one " << getPotionViaName(_enemies[duplicatedEnemyIndex].getTempGear(0)).getName() << "!" << endl;
        }
        eraseEnemy(duplicatedEnemyIndex);
    }
}
double Game::attackerDamagesDefender(double defenderDef, int attackerDmg, char defenderElementalWeakness, char attackerWeaponElement)
{
    double damage = 0;
    double attackerDmgMin = attackerDmg * .1;
    double acutalAttack = rand() % attackerDmg + attackerDmgMin;
    damage = acutalAttack * 1.5 - defenderDef;
    if (defenderElementalWeakness == 'F' && attackerWeaponElement == 'F') // accounts for elemental interactions
    {
        damage *= 2;
    }
    else if (defenderElementalWeakness == 'W' && attackerWeaponElement == 'W')
    {
        damage *= 2;
    }
    else if (defenderElementalWeakness == 'E' && attackerWeaponElement == 'E')
    {
        damage *= 2;
    }
    else if (defenderElementalWeakness == 'A' && attackerWeaponElement == 'A')
    {
        damage *= 2;
    }
    else if (defenderElementalWeakness == 'W' && attackerWeaponElement == 'F') // accounts for elemental interactions
    {
        damage /= 2;
    }
    else if (defenderElementalWeakness == 'F' && attackerWeaponElement == 'W')
    {
        damage /= 2;
    }
    else if (defenderElementalWeakness == 'A' && attackerWeaponElement == 'E')
    {
        damage /= 2;
    }
    else if (defenderElementalWeakness == 'A' && attackerWeaponElement == 'E')
    {
        damage /= 2;
    }
    if (damage <= 0)
    {
        damage = 1;
    }
    return damage * .7f;
}
bool Game::islandFightEndConditions(Entity enemy, Entity player)
{
    if (enemy.getHp() <= 0 && player.getStam() <= 0)
    {
        cout << "The " << enemy.getName() << " has been defeated!" << endl;
        cout << "But " << player.getName() << " is too tired to collect the spoils..." << endl;
        return true;
    }
    else if (player.getHp() <= 0)
    {
        cout << "The " << player.getName() << " has been defeated!" << endl;
        return true;
    }
    else if (enemy.getHp() <= 0)
    {
        cout << "The " << enemy.getName() << " has been defeated!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}
bool Game::epicFightEndConditions(Entity enemy, Entity player, Entity player2)
{
    if (enemy.getHp() <= 0)
    {
        cout << "The " << enemy.getName() << " has been defeated!" << endl;
        if (player.getHp() <= 0)
        {
            cout << "But " << player.getName() << " is too dead to collect the spoils..." << endl;
        }
        else if (player.getStam() <= 0)
        {
            cout << "But " << player.getName() << " is too tired to collect the spoils..." << endl;
        }
        if (player2.getHp() <= 0)
        {
            cout << "But " << player2.getName() << " is too dead to collect the spoils..." << endl;
        }
        else if (player2.getStam() <= 0)
        {
            cout << "But " << player2.getName() << " is too tired to collect the spoils..." << endl;
        }
        return true;
    }
    else if (player.getHp() <= 0 && player2.getHp() <= 0)
    {
        cout << player.getName() << " and " << player2.getName() << " have been defeated!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}
bool Game::ult(Entity &player, Entity &player2, Entity &enemy, Game &game, double &playerDMGmult, double &enemyDMGmult)
{
    string ultName = player.getUlt();
    if (ultName == "Odyssey's End")
    {
        player.changeUltCharge(-1);
        cout << "Deliver a fatal blow to an opponent, a testament to your resilience and determination to overcome all obstacles standing in your path." << endl;
        enemy.changeHp(-50);
        double max = enemy.getMaxHp();
        cout << "Deal 50 raw damage to " << enemy.getName() << endl;
        if (enemy.getHp() <= 0)
        {
            // do nothing
        }
        else if (enemy.getHp() <= max * .05)
        {
            string legitimatelyADummyVariable;
            cout << "Execute " << enemy.getName() << ". (input any key)" << endl;
            getline(cin, legitimatelyADummyVariable);
            cout << endl;
            enemy.changeHp(-4815162342);
            cout << "Executed." << endl;
        }
    }
    else if (ultName == "Loyal Companionship")
    {
        player.changeUltCharge(-1);
        cout << "Through the trials of battle, our bond remains unbroken, our loyalty unwavering." << endl;
        double defBonus = player2.getDef() * .05;
        double damBonus = player2.getEquipped(0).getDamage() * .05;
        cout << player.getEquipped(0).getName() << " is permanently boosted by the defense and damage of " << player2.getName() << " to gain " << defBonus + damBonus << " damage" << endl;
        player.getEquipped(0).changeDamage(damBonus + defBonus);
    }
    else if (ultName == "Circe's Dominion")
    {
        player.changeUltCharge(-1);
        cout << "Bend the will of your enemy and make them damage themselves." << endl;
        return 1;
    }
    else if (ultName == "Trickster's Gambit")
    {
        player.changeUltCharge(-1);
        cout << "Create an illusion of yourself, confusing your opponents." << endl;
        enemyDMGmult = 0.5;
    }
    else // if (ultName == "Godly Strength")
    {
        player.changeUltCharge(-1);
        cout << "You hear the call of the gods, and are inspired" << endl;
        playerDMGmult = 2;
    }
    return 0;
}

// shop functions
void Game::generateShop(Entity &player)
{
    string shopOptionChoice;
    bool choice1done = false;
    bool choice2done = false;
    bool choice3done = false;
    int equipSale1, equipSale2, equipSale3;
    int potionSale1, potionSale2, potionSale3;
    // next 25 lines stock the show with valid items
    shuffleEquip(_allEquip);
    shufflePotion(_allPotions);
    equipSale1 = rand() % _allEquip.size();
    equipSale2 = rand() % _allEquip.size();
    equipSale3 = rand() % _allEquip.size();
    while (_allEquip[equipSale1].getName() == "Hades' Crown" || _allEquip[equipSale1].getName() == "Zeus' Bolt" || _allEquip[equipSale1].getName() == "King's Blade" || _allEquip[equipSale1].getName() == "Medusa's Head" || _allEquip[equipSale1].getName() == "Fangs of Scylla" || _allEquip[equipSale1].getName() == "Cyclops Gaze")
    {
        equipSale1 = rand() % _allEquip.size();
    }
    while (_allEquip[equipSale2].getName() == "Hades' Crown" || _allEquip[equipSale2].getName() == "Zeus' Bolt" || _allEquip[equipSale2].getName() == "King's Blade" || _allEquip[equipSale2].getName() == "Medusa's Head" || _allEquip[equipSale2].getName() == "Fangs of Scylla" || _allEquip[equipSale2].getName() == "Cyclops Gaze" || equipSale1 == equipSale2)
    {
        equipSale2 = rand() % _allEquip.size();
    }
    while (_allEquip[equipSale3].getName() == "Hades' Crown" || _allEquip[equipSale3].getName() == "Zeus' Bolt" || _allEquip[equipSale3].getName() == "King's Blade" || _allEquip[equipSale3].getName() == "Medusa's Head" || _allEquip[equipSale3].getName() == "Fangs of Scylla" || _allEquip[equipSale3].getName() == "Cyclops Gaze" || equipSale1 == equipSale3 || equipSale3 == equipSale2)
    {
        equipSale3 = rand() % _allEquip.size();
    }
    potionSale1 = rand() % _allPotions.size();
    potionSale2 = rand() % _allPotions.size();
    potionSale3 = rand() % _allPotions.size();
    while (potionSale1 == potionSale2)
    {
        potionSale2 = rand() % _allPotions.size();
    }
    while (potionSale1 == potionSale3 || potionSale3 == potionSale2)
    {
        potionSale3 = rand() % _allPotions.size();
    }
    while (shopOptionChoice != "4")
    {
        cout << "Welcome to the shop " << player.getName() << "! What would you like to do?" << endl;
        cout << "(1) Buy Equipment" << endl;
        cout << "(2) Buy Potion" << endl;
        cout << "(3) Sell Equipment" << endl;
        cout << "(4) Leave Shop" << endl;
        getline(cin, shopOptionChoice);
        shopOptionChoice = shopOptionChoiceVal(shopOptionChoice);
        if (shopOptionChoice == "1")
        {
            if (choice1done == true)
            {
                cout << "Only one Equipment purchase per visit" << endl;
            }
            else
            {
                cout << "What would you like to buy with your " << player.getGold() << " gold?" << endl;
                cout << "(1) " << _allEquip[equipSale1].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[equipSale1]) << displayDmgOrDefNum(_allEquip[equipSale1]) << "  Price in gold: " << _allEquip[equipSale1].getPrice() << endl;
                cout << "(2) " << _allEquip[equipSale2].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[equipSale2]) << displayDmgOrDefNum(_allEquip[equipSale2]) << "  Price in gold: " << _allEquip[equipSale2].getPrice() << endl;
                cout << "(3) " << _allEquip[equipSale3].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[equipSale3]) << displayDmgOrDefNum(_allEquip[equipSale3]) << "  Price in gold: " << _allEquip[equipSale3].getPrice() << endl;
                cout << "(4) Nothing" << endl;
                string shopEquipBuyChoice; // displays options till valid input, if chosen, subtraces price from player gold
                getline(cin, shopEquipBuyChoice);
                shopEquipBuyChoice = shopEquipBuyChoiceVal(shopEquipBuyChoice, equipSale1, equipSale2, equipSale3);
                if (shopEquipBuyChoice == "1")
                {
                    if (player.getGold() >= _allEquip[equipSale1].getPrice())
                    {
                        choice1done = true;
                        player.changeGold(-(_allEquip[equipSale1].getPrice()));
                        player.updateEquipment(_allEquip[equipSale1]);
                        cout << "Successfully bought " << _allEquip[equipSale1].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else if (shopEquipBuyChoice == "2")
                {
                    if (player.getGold() >= _allEquip[equipSale2].getPrice())
                    {
                        choice1done = true;
                        player.changeGold(-(_allEquip[equipSale2].getPrice()));
                        player.updateEquipment(_allEquip[equipSale2]);
                        cout << "Successfully bought " << _allEquip[equipSale2].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else if (shopEquipBuyChoice == "3")
                {
                    if (player.getGold() >= _allEquip[equipSale3].getPrice())
                    {
                        choice1done = true;
                        player.changeGold(-(_allEquip[equipSale3].getPrice()));
                        player.updateEquipment(_allEquip[equipSale3]);
                        cout << "Successfully bought " << _allEquip[equipSale3].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else
                {
                    // do nothing
                }
            }
        }
        else if (shopOptionChoice == "2")
        {
            if (choice2done == true)
            {
                cout << "Only one Potion purchase per visit" << endl;
            }
            else
            {
                cout << "What would you like to buy with your " << player.getGold() << " gold?" << endl;
                cout << "(1) " << _allPotions[potionSale1].getName() << "  Price in gold: " << _allPotions[potionSale1].getPrice() << endl;
                cout << "(2) " << _allPotions[potionSale2].getName() << "  Price in gold: " << _allPotions[potionSale2].getPrice() << endl;
                cout << "(3) " << _allPotions[potionSale3].getName() << "  Price in gold: " << _allPotions[potionSale3].getPrice() << endl;
                cout << "(4) Nothing" << endl;
                string shopPotionBuyChoice; // displays options till valid input, if chosen, subtracts price from player gold
                getline(cin, shopPotionBuyChoice);
                shopPotionBuyChoice = shopPotionBuyChoiceVal(shopPotionBuyChoice, potionSale1, potionSale2, potionSale3);
                if (shopPotionBuyChoice == "1")
                {
                    if (player.getGold() >= _allPotions[potionSale1].getPrice())
                    {
                        choice2done = true;
                        player.changeGold(-(_allPotions[potionSale1].getPrice()));
                        player.updatePotion(_allPotions[potionSale1]);
                        cout << "Successfully bought " << _allPotions[potionSale1].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else if (shopPotionBuyChoice == "2")
                {
                    if (player.getGold() >= _allPotions[potionSale2].getPrice())
                    {
                        choice2done = true;
                        player.changeGold(-(_allPotions[potionSale2].getPrice()));
                        player.updatePotion(_allPotions[potionSale2]);
                        cout << "Successfully bought " << _allPotions[potionSale2].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else if (shopPotionBuyChoice == "3")
                {
                    if (player.getGold() >= _allPotions[potionSale3].getPrice())
                    {
                        choice2done = true;                                        // cannot choose potion shop again
                        player.changeGold(-(_allPotions[potionSale3].getPrice())); // subtract gold
                        player.updatePotion(_allPotions[potionSale3]);             // add potion
                        cout << "Successfully bought " << _allPotions[potionSale3].getName() << ", you now have " << player.getGold() << " gold remaining" << endl;
                    }
                    else
                    {
                        cout << "You lack the funding for that..." << endl;
                    }
                }
                else
                {
                    // do nothing
                }
            }
        }
        else if (shopOptionChoice == "3")
        {
            string sellEquipmentChoice;
            if (choice3done == true)
            {
                cout << "You may only sell one piece of equipment per visit" << endl;
            }
            else
            {
                if (player.getInventoySize() == 0)
                {
                    cout << "You have nothing to sell!" << endl;
                }
                else
                {
                    cout << "Which piece of equipment would you like to sell? (half-price)" << endl;
                    cout << "(1) Nevermind" << endl;
                    for (size_t i = 1; i <= player.getInventoySize(); i++)
                    {
                        cout << "(" << i + 1 << ") " << player.getInventory(i - 1).getName() << " (" << player.getInventory(i - 1).getPrice() / 2 << ")" << endl;
                    }
                    getline(cin, sellEquipmentChoice);
                    bool valid = false;
                    bool numb = true;
                    while (!valid)
                    {
                        int val = 0;
                        for (int i = 0; i < sellEquipmentChoice.length(); i++)
                        {
                            if (!isdigit(sellEquipmentChoice[i]))
                            {
                                numb = false;
                            }
                            else
                            {
                                val++;
                            }
                        }
                        if (val == sellEquipmentChoice.length())
                        {
                            numb = true;
                        }
                        else
                        {
                            val = 0;
                        }
                        if (numb)
                        {
                            if (stoi(sellEquipmentChoice) >= 1 && stoi(sellEquipmentChoice) <= player.getInventoySize() + 1)
                            { // ^ input validation
                                valid = true;
                            }
                            else
                            {
                                cout << "Invalid choice" << endl;
                                cout << "Which piece of equipment would you like to sell?:" << endl;
                                cout << "(1) Nevermind" << endl;
                                for (size_t i = 1; i <= player.getInventoySize(); i++) // prints options
                                {
                                    cout << "(" << i + 1 << ") " << player.getInventory(i - 1).getName() << " (" << player.getInventory(i - 1).getPrice() / 2 << ")" << endl;
                                }
                                getline(cin, sellEquipmentChoice);
                            }
                        }
                        else
                        {
                            cout << "Invalid choice" << endl;
                            cout << "Which piece of equipment would you like to sell?:" << endl;
                            cout << "(1) Nevermind" << endl;
                            for (size_t i = 1; i <= player.getInventoySize(); i++) // prints options
                            {
                                cout << "(" << i + 1 << ") " << player.getInventory(i - 1).getName() << " (" << player.getInventory(i - 1).getPrice() / 2 << ")" << endl;
                            }
                            getline(cin, sellEquipmentChoice);
                        }
                    }
                    if (sellEquipmentChoice == "1")
                    {
                        // do nothing
                    }
                    else
                    {
                        choice3done = true;
                        cout << "Successfully sold the " << player.getInventory(stoi(sellEquipmentChoice) - 2).getName() << " for " << player.getInventory(stoi(sellEquipmentChoice) - 2).getPrice() / 2 << " gold!" << endl;
                        player.changeGold(player.getInventory(stoi(sellEquipmentChoice) - 2).getPrice() / 2);
                        player.eraseEquipment(stoi(sellEquipmentChoice) - 2); // erases choice - 1 from vector list
                    }
                }
            }
        }
        if (choice1done == true && choice2done == true && choice3done == true)
        {
            break;
        }
    }
    cout << "Thank you for visiting!" << endl;
}
string Game::displayDmgOrDefString(Equipment equipment)
{
    if (equipment.getType() == 'S')
    {
        return " DEF: ";
    }
    else
    {
        return " DMG: ";
    }
}
double Game::displayDmgOrDefNum(Equipment equipment)
{
    if (equipment.getType() == 'S')
    {
        double def = equipment.getDefense();
        return def;
    }
    else
    {
        double dmg = equipment.getDamage();
        return dmg;
    }
}
string Game::shopEquipBuyChoiceVal(string input, int ind1, int ind2, int ind3)
{
    while (input != "1" && input != "2" && input != "3" && input != "4")
    {
        cout << "Invalid choice" << endl;
        cout << "What would you like to buy?" << endl;
        cout << "(1) " << _allEquip[ind1].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[ind1]) << displayDmgOrDefNum(_allEquip[ind1]) << " Price in gold: " << _allEquip[ind1].getPrice() << endl;
        cout << "(2) " << _allEquip[ind2].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[ind2]) << displayDmgOrDefNum(_allEquip[ind2]) << " Price in gold: " << _allEquip[ind2].getPrice() << endl;
        cout << "(3) " << _allEquip[ind3].getName() << fixed << setprecision(0) << displayDmgOrDefString(_allEquip[ind3]) << displayDmgOrDefNum(_allEquip[ind3]) << " Price in gold: " << _allEquip[ind3].getPrice() << endl;
        cout << "(4) Nothing" << endl;
        getline(cin, input);
    }
    return input;
}
string Game::shopPotionBuyChoiceVal(string input, int ind1, int ind2, int ind3)
{
    while (input != "1" && input != "2" && input != "3" && input != "4")
    {
        cout << "Invalid choice" << endl;
        cout << "What would you like to buy?" << endl;
        cout << "(1) " << _allPotions[ind1].getName() << " Price in gold: " << _allPotions[ind1].getPrice() << endl;
        cout << "(2) " << _allPotions[ind2].getName() << " Price in gold: " << _allPotions[ind2].getPrice() << endl;
        cout << "(3) " << _allPotions[ind3].getName() << " Price in gold: " << _allPotions[ind3].getPrice() << endl;
        cout << "(4) Nothing" << endl;
        getline(cin, input);
    }
    return input;
}
void Game::shuffleEquip(vector<Equipment> equip)
{
    Equipment tempy;
    int randomIndex;
    for (int j = 0; j < equip.size(); j++)
    {
        randomIndex = rand() % equip.size(); // Shuffle within the row
        tempy = equip[j];
        equip[j] = equip[randomIndex];
        equip[randomIndex] = tempy;
    }
}
void Game::shufflePotion(vector<Potions> potions)
{
    Potions tempy;
    int randomIndex;
    for (int j = 0; j < potions.size(); j++)
    {
        randomIndex = rand() % potions.size(); // Shuffle within the row
        tempy = potions[j];
        potions[j] = potions[randomIndex];
        potions[randomIndex] = tempy;
    }
}

// players
int Game::playerOptionMenu(Entity &player)
{
    cout << "What would you like to do?" << endl;
    cout << "(1) Move" << endl;
    cout << "(2) Swap/Drop Weapon" << endl;
    cout << "(3) Use Potion" << endl;
    cout << "(4) Print Player Stats" << endl;
    cout << "(5) Quit" << endl;
    string menuChoice;
    getline(cin, menuChoice);
    menuChoice = menuChoiceVal(menuChoice);
    if (menuChoice == "1") // 1 - 6
    {
        int move = sixSidedDie();
        player.changeStam(-3);
        return move;
    }
    else if (menuChoice == "2") // swap or drop
    {
        cout << "Would you like to swap or drop your equipment? (choose a number)" << endl;
        cout << "(1) Swap" << endl;
        cout << "(2) Drop" << endl;
        string swapOrDrop;
        getline(cin, swapOrDrop);
        swapOrDrop = swapOrDropVal(swapOrDrop);
        if (swapOrDrop == "1")
        {
            int swap_ = player.swap();
            return swap_;
        }
        else // swapOrDrop == "2"
        {
            int drop_ = player.drop();
            return drop_;
        }
        return 7;
    }
    else if (menuChoice == "3") // use potion
    {
        int usepotion_ = player.usePotion();
        return usepotion_;
    }
    else if (menuChoice == "4") // print stats
    {
        cout << endl;
        player.entityStatsmenu();
        return 9;
    }
    else // exit game (quit)
    {
        return 0;
    }
}
void Game::tileAction(int tileType, Entity &player, Entity &player2, Map &map, Game &game, int playerTurn)
{
    if (tileType == 1) // water
    {
        int calamityRoll = hundredSidedDie();
        if (calamityRoll <= player.getCalamityChance() && calamityRoll >= 1)
        {
            cout << "Calamity inbound!" << endl;
            int calamitySelectionOdds = hundredSidedDie();
            if (calamitySelectionOdds >= 1 && calamitySelectionOdds <= 45)
            {
                cout << "With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon." << endl;
                int stormPushBack = threeSidedDie();
                map.setMapPos(playerTurn, map.getMapPos(playerTurn) - stormPushBack, map.getMapPos(playerTurn));
                cout << player.getName() << " is pushed back " << stormPushBack << " spaces" << endl;
                if (map.epicCombatMoment())
                {
                    cout << "Unlucky!" << endl;
                    combat(player, player2, 'E', game);
                }
            }
            else if (calamitySelectionOdds > 45 && calamitySelectionOdds <= 80)
            {
                cout << "The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality." << endl;
                player.setCondition('D');
                cout << player.getName() << " contracts a disease " << endl;
            }
            else // if (calamitySelectionOdds > 80 && calamitySelectionOdds <= 100)
            {
                cout << "Much to your dismay, it seems you are not the only one on your ship." << endl;
                player.setCondition('P');
                cout << player.getName() << " is poisoned " << endl;
            }
        }
        else
        {
            cout << "~~Smooth Sailing~~" << endl;
        }
    }
    else if (tileType == 2) // island
    {
        game.combat(player, player2, 'I', game);
    }
    else if (tileType == 3) // special
    {
        int specialType = hundredSidedDie();
        if (specialType >= 0 && specialType <= 40) // random
        {
            int specialSpecialType = fourSidedDie();
            if (specialSpecialType == 1) // Shortcut Tile:
            {
                map.move(playerTurn, 4, map.playerBoardTemplate);
                cout << "Your spirits soar as you're propelled four tiles ahead. Ithaca isn't far." << endl;
            }
            else if (specialSpecialType == 2) // Siren's Song Tile:
            {
                player.setSkip(true);
                cout << "As the Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen. You stop in your tracks. You are paralyzed on your next turn only." << endl;
            }
            else if (specialSpecialType == 3) // Helios' Beacon Tile:
            {
                player.changeCalamityChance(-5);
                cout << "As you stand in the brilliance of Helios' Beacon, you feel the warmth of the sun god's favor shining upon you. You feel luckier." << endl;
                cout << "Your calamity chance decreases by 5%" << endl;
            }
            else // if (specialSpecialType == 4) // Nymph's Spring Tile:
            {
                int stam_change = player.getMaxStam() - player.getStam();
                player.changeStam(200);
                cout << "In the embrace of the Nymph's Spring, you feel the embrace of nature itself. Your stamina is replenished." << endl;
                cout << player.getName() << "'s stamina increases by " << stam_change << "!" << endl;
            }
        }
        else if (specialType > 40 && specialType <= 75) // treasure
        {
            cout << "You found treasure!" << endl;
            int treasureChoiceOdds = hundredSidedDie();
            if (treasureChoiceOdds >= 0 && treasureChoiceOdds <= 25) // stam refill
            {
                int stamGain = staminaRefill();
                player.changeStam(stamGain);
                cout << "Stamina refill!" << endl;
                cout << player.getName() << " gains " << stamGain << " stamina, " << player.getName() << " now has " << player.getStam() << " stamina!" << endl;
            }
            else if (treasureChoiceOdds > 25 && treasureChoiceOdds <= 50) // gold waterfall
            {
                int goldGain = goldWindfall();
                player.changeGold(goldGain);
                cout << "Gold Windfall!" << endl;
                cout << player.getName() << " gains " << goldGain << " gold, " << player.getName() << " now has " << player.getGold() << " gold!" << endl;
            }
            else if (treasureChoiceOdds > 50 && treasureChoiceOdds <= 75) // dmg buff
            {
                int dmgGain = damageBuff();
                player.getEquipped(0).changeDamage(dmgGain);
                cout << "Damage Buff!" << endl;
                cout << player.getName() << "'s weapon " << player.getEquipped(0).getName() << " permanently gains " << dmgGain << " damage!" << endl;
            }
            else // if (treasureChoiceOdds > 75 && treasureChoiceOdds <= 100) // circes brew
            {
                cout << player.getName() << " founr Circe's Brew!" << endl;
                int circeBuff = hundredSidedDie();
                if (circeBuff > 0 && circeBuff <= 30) // serpent (poison)
                {
                    cout << "You've become an elusive serpent." << endl;
                    player.getEquipped(0).setPoison();
                    cout << player.getName() << "'s " << player.getEquipped(0).getName() << " now poisons the enemy on a hit!" << endl;
                }
                else if (circeBuff > 30 && circeBuff <= 70) // lion (dmg)
                {
                    cout << "You've become a ferocious lion." << endl;
                    cout << player.getName() << " gets a permanent 10 damage buff battles!" << endl;
                    player.addBonusDamage(10);
                }
                else // if (circeBuff > 70 && circeBuff <= 100) // wolf (always attack first)
                {
                    cout << "You've become an agile wolf." << endl;
                    cout << player.getName() << " gains agility and now attacks first in battles!" << endl;
                    player.setAdvantage(true);
                }
            }
        }
        else // if (specialType > 75 &&specialType <= 100) // riddles
        {
            cout << "Solve and be rewarded:" << endl;
            int riddleIndex = rand() % (riddlesQ.size() + 1);
            cout << riddlesQ[riddleIndex] << endl;
            cout << "Answer: ";
            string answer;
            getline(cin, answer);
            if (answer == riddlesA[riddleIndex])
            {
                cout << "Correct!" << endl;
                int whichStat = threeSidedDie();
                if (whichStat == 1) // hp
                {
                    player.changeMaxHp(5);
                    cout << player.getName() << "'s max health increases by 5!" << endl;
                }
                else if (whichStat == 2) // stam
                {
                    player.changeMaxStam(5);
                    cout << player.getName() << "'s max stamina increases by 5!" << endl;
                }
                else // if (whichStat == 3) // def
                {
                    player.changeDef(5);
                    cout << player.getName() << "'s defense increases by 5!" << endl;
                }
            }
            else
            {
                cout << "Incorrect!" << endl;
                cout << "Correct Answer: " << riddlesA[riddleIndex] << endl;
            }
        }
    }
    else if (tileType == 4) // Ithica
    {
        // do nothing (game over)
    }
    else
    {
        // do nothing
    }
}
