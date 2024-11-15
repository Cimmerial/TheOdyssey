#include "entityC.h"

// getters and setters
string Entity::getName()
{
    return _name;
}
char Entity::getType()
{
    return _type;
}
double Entity::getHp()
{
    return _hp;
}
double Entity::getStam()
{
    return _stam;
}
double Entity::getDef()
{
    return _def;
}
char Entity::getCondition()
{
    return _condition;
}
bool Entity::getAdvantage()
{
    return advantage;
}
char Entity::getElementalWeakness()
{
    return elemental_weakness;
}
int Entity::getGold()
{
    return gold;
}
int Entity::getMaxHp()
{
    return _maxHP;
}
double Entity::getBonusDamage()
{
    return bonusDamage;
}
int Entity::getMaxStam()
{
    return _maxStam;
}
bool Entity::getSkip()
{
    return skipPlayer;
}
void Entity::setSkip(bool skip)
{
    skipPlayer = skip;
}
int Entity::getCalamityChance()
{
    return calamityChance;
}
void Entity::changeCalamityChance(int calamity)
{
    calamityChance += calamity;
}
void Entity::changeTotalDamageDealt(double damage)
{
    totalDamageDealt += damage;
}
void Entity::addMiss()
{
    totalMisses += 1;
}
void Entity::getTotals()
{
    std::cout << "Total gold earned: " << totalGoldgained << " Total damage dealt: " << totalDamageDealt << " Number of misses: " << totalMisses << endl;
}
double Entity::getTotalGold()
{
    return totalGoldgained;
}
double Entity::getTotalDamage()
{
    return totalDamageDealt;
}
double Entity::getTotalDamageTaken()
{
    return totalDamageTaken * -1;
}
string Entity::getTempGear(int index)
{
    return _tempGear[index];
}
int Entity::getMisses()
{
    return totalMisses;
}
Equipment Entity::getEquipped(int equippedIndex)
{
    return _equipped[equippedIndex];
}
Potions Entity::getPotions(int potionIndex)
{
    return _potions[potionIndex];
}
Equipment Entity::getInventory(int inventoryIndex)
{
    return _inventory[inventoryIndex];
}
int Entity::getEquippedSize()
{
    return _equipped.size();
}
int Entity::getPotionsSize()
{
    return _potions.size();
}
int Entity::getInventoySize()
{
    return _inventory.size();
}
int Entity::getPotionCount()
{
    return _itemCount[0];
}
void Entity::changeHp(double hp) // change
{
    if (hp < 0)
    {
        totalDamageTaken += hp;
    }
    if (_hp + hp >= getMaxHp())
    {
        _hp = getMaxHp();
    }
    else if (_hp + hp <= 0)
    {
        _hp = 0;
    }
    else
    {
        _hp += hp;
    }
}
void Entity::changeStam(double stam)
{
    if (_stam + stam >= getMaxStam())
    {
        _stam = getMaxStam();
    }
    else if (_stam + stam <= 0)
    {
        _stam = 0; // add tired function or war here
    }
    else
    {
        _stam += stam;
    }
}
void Entity::changeDef(double def) // change
{
    _def += def;
}
void Entity::setCondition(char condition) // set
{
    cout << "test" << endl;
    _condition = condition;
}
void Entity::setAdvantage(bool adv) // set
{
    advantage = adv;
}
void Entity::setElementalWeakness(char eleWeak) // set
{
    elemental_weakness = eleWeak;
}
void Entity::changeGold(int gold_) // change
{
    totalGoldgained += gold_;
    if (gold + gold_ > 500)
    {
        gold = 500;
    }
    else
    {
        gold += gold_;
    }
}
void Entity::changeMaxStam(int maxStam)
{
    _maxStam += maxStam;
}
void Entity::changeMaxHp(int maxHp)
{
    _maxHP += maxHp;
}
void Entity::addBonusDamage(int bonus)
{
    bonusDamage += bonus;
}
Potions Entity::getPotionFromEntity(int potionIndex)
{
    return _potions[potionIndex];
}
Equipment Entity::getEquippedEquipmentFromEntity(int equipmentIndex)
{
    return _equipped[equipmentIndex];
}
Equipment Entity::getInventoryEquipmentFromEntity(int equipmentIndex)
{
    return _inventory[equipmentIndex];
}
void Entity::eraseEquipment(int index)
{
    vector<Equipment> dummyEquipVect;
    for (size_t i = 0; i < _inventory.size(); i++)
    {
        if (i != index)
        {
            dummyEquipVect.push_back(_inventory[i]);
        }
    }
    _inventory = dummyEquipVect;
    // _inventory.erase(_inventory.begin() + index);
}
void Entity::erasePotions(int index)
{
    vector<Potions> dummyPotionVect;
    for (size_t i = 0; i < _potions.size(); i++)
    {
        if (i != index)
        {
            dummyPotionVect.push_back(_potions[i]);
        }
    }
    _potions = dummyPotionVect;
    // _potions.erase(_potions.begin() + index);
}
void Entity::setUltCharge(bool charge)
{
    ultCharge = charge;
}
int Entity::getUltCharge()
{
    return ultCharge;
}
void Entity::changeUltCharge(int change)
{
    if (ultCharge + change <= 0)
    {
        ultCharge = 0;
    }
    else
    {
        ultCharge += change;
    }
}
string Entity::getUlt()
{
    return ult;
}

// initialize
Entity::Entity()
{
}
Entity::Entity(string entityLine) // instance of game helps with item vector iteration
{
    string tempArr[12];
    split(entityLine, '|', tempArr, 12);
    if (tempArr[1] == "P")
    {
        initializePlayer(entityLine);
    }
    else if (tempArr[1] == "E")
    {
        initializeEpicEnemy(entityLine);
    }
    else if (tempArr[1] == "I")
    {
        initializeIslandEnemy(entityLine);
    }
}
void Entity::initializePlayer(string playerLine)
{
    string tempArr[12];
    split(playerLine, '|', tempArr, 12);
    _name = tempArr[0];
    _type = tempArr[1][0];
    _hp = stod(tempArr[2]);
    _stam = stod(tempArr[3]);
    _def = stod(tempArr[4]);
    _maxHP = stod(tempArr[2]);
    _maxStam = stod(tempArr[3]);
    _condition = tempArr[5][0];
    if (tempArr[6][0] == 'F')
    {
        advantage = false;
    }
    else
    {
        advantage = true;
    }
    elemental_weakness = tempArr[7][0];
    gold = stoi(tempArr[8]);
    string subTempyArr[2];                  // only works if monster or player has 1 potion and one weapon
    split(tempArr[9], ',', subTempyArr, 2); // converts line to two strings
    _tempGear.push_back(subTempyArr[0]);    // potion
    _tempGear.push_back(subTempyArr[1]);    // equip
    string subTempArr[2];
    split(tempArr[10], ',', subTempArr, 2); // splits number of items into potions and weapons
    _itemCount[0] = stoi(subTempArr[0]);
    _itemCount[1] = stoi(subTempArr[1]);
    skipPlayer = false;
    calamityChance = 40;
    totalDamageDealt = 0;
    totalGoldgained = 0;
    totalMisses = 0;
    totalDamageTaken = 0;
    bonusDamage = 0;
    ult = tempArr[11];
    ultCharge = 1;
}
void Entity::initializeIslandEnemy(string islandEnemyLine)
{
    string tempArr[12];
    split(islandEnemyLine, '|', tempArr, 12);
    _name = tempArr[0];
    _type = tempArr[1][0];
    _hp = stod(tempArr[2]);
    _stam = stod(tempArr[3]);
    _def = stod(tempArr[4]);
    _maxHP = stod(tempArr[2]);
    _maxStam = stod(tempArr[3]);
    _condition = tempArr[5][0];
    if (tempArr[6][0] == 'F')
    {
        advantage = false;
    }
    else
    {
        advantage = true;
    }
    elemental_weakness = tempArr[7][0];
    gold = stoi(tempArr[8]);
    string subTempyArr[2]; // only works if monster or player has 1 potion and one weapon
    split(tempArr[9], ',', subTempyArr, 2);
    _tempGear.push_back(subTempyArr[0]); // potion
    _tempGear.push_back(subTempyArr[1]); // equip
    string subTempArr[2];
    split(tempArr[10], ',', subTempArr, 2); // splits number of items into potions and weapons
    _itemCount[0] = stoi(subTempArr[0]);
    _itemCount[1] = stoi(subTempArr[1]);
    totalDamageTaken = 0;
    ult = tempArr[11];
}
void Entity::initializeEpicEnemy(string epicEnemyLine)
{
    string tempArr[12];
    split(epicEnemyLine, '|', tempArr, 12);
    _name = tempArr[0];
    _type = tempArr[1][0];
    _hp = stod(tempArr[2]);
    _stam = stod(tempArr[3]);
    _def = stod(tempArr[4]);
    _maxHP = stod(tempArr[2]);
    _maxStam = stod(tempArr[3]);
    _condition = tempArr[5][0];
    if (tempArr[6][0] == 'F')
    {
        advantage = false;
    }
    else
    {
        advantage = true;
    }
    elemental_weakness = tempArr[7][0];
    gold = stoi(tempArr[8]);
    string subTempyArr[2]; // only works if monster or player has 1 potion and one weapon
    split(tempArr[9], ',', subTempyArr, 2);
    _tempGear.push_back(subTempyArr[0]); // potion
    _tempGear.push_back(subTempyArr[1]); // equip
    string subTempArr[2];
    split(tempArr[10], ',', subTempArr, 2); // splits number of items into potions and weapons
    _itemCount[0] = stoi(subTempArr[0]);
    _itemCount[1] = stoi(subTempArr[1]);
    totalDamageTaken = 0;
    ult = tempArr[11];
}

// equipment/potions
int Entity::swap()
{
    if (_equipped.size() == 2) // this means player has shield and weapon
    {
        string swapTypeChoice; // add if no weapons
        string swapWeaponChoice;
        string swapShieldChoice;
        string equipShieldChoice;
        cout << "Would you like to swap your weapon or shield?" << endl;
        cout << "(1) Weapon" << endl;
        cout << "(2) Shield" << endl;
        getline(cin, swapTypeChoice);
        swapTypeChoice = swapTypeChoiceVal(swapTypeChoice);
        if (swapTypeChoice == "1" || swapTypeChoice == "Weapon" || swapTypeChoice == "weapon")
        {
            bool hasWeapon = false;
            for (size_t i = 0; i < _inventory.size(); i++)
            {
                if (_inventory[i].getType() == 'D')
                {
                    hasWeapon = true;
                }
            }
            if (hasWeapon)
            {
                cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                cout << "(1) Nothing" << endl;
                for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                {
                    cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                }
                getline(cin, swapWeaponChoice);
                bool valid = false;
                bool numb = true;
                while (!valid)
                {
                    int val = 0;
                    for (int i = 0; i < swapWeaponChoice.length(); i++)
                    {
                        if (!isdigit(swapWeaponChoice[i]))
                        {
                            numb = false;
                        }
                        else
                        {
                            val++;
                        }
                    }
                    if (val == swapWeaponChoice.length())
                    {
                        numb = true;
                    }
                    else
                    {
                        val = 0;
                    }
                    if (numb)
                    {
                        if ((stoi(swapWeaponChoice) >= 1 && stoi(swapWeaponChoice) <= _inventory.size() + 1 && _inventory[stoi(swapWeaponChoice) - 2].getType() == 'D') || stoi(swapWeaponChoice) == 1)
                        { // ^ input validation
                            valid = true;
                        }
                        else
                        {
                            cout << "Invalid range or equipment type" << endl;
                            cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                            cout << "(1) Nothing" << endl;
                            for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                            {
                                cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                            }
                            getline(cin, swapWeaponChoice);
                        }
                    }
                    else
                    {
                        cout << "Invalid range or equipment type" << endl;
                        cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                        cout << "(1) Nothing" << endl;
                        for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, swapWeaponChoice);
                    }
                }
                if (swapWeaponChoice == "1")
                {
                    return 9; // doesnt skip turn
                }
                else
                {
                    _inventory.push_back(_inventory[stoi(swapWeaponChoice) - 2]); // duplicates
                    _inventory[stoi(swapWeaponChoice) - 2] = _equipped[0];        // replaces
                    _equipped[0] = _inventory[_inventory.size() - 2];             // replaces
                    _inventory.pop_back();                                        // erases duplicate
                    cout << "Sucuessfully swapped! You are now wielding the " << _equipped[0].getName() << endl;
                }
            }
            else
            {
                cout << "You have no weapons to swap to!" << endl;
                return 9;
            }
        }
        else if (swapTypeChoice == "2" || swapTypeChoice == "Shield" || swapTypeChoice == "shield")
        {
            bool hasShield = false;
            for (size_t i = 0; i < _inventory.size(); i++)
            {
                if (_inventory[i].getType() == 'S')
                {
                    hasShield = true;
                }
            }
            if (hasShield)
            {
                cout << "Which shield would you like to swap with " << _equipped[1].getName() << "?" << endl;
                cout << "(1 Nothing)" << endl;
                for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                {
                    cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                }
                getline(cin, swapShieldChoice);
                bool valid = false;
                bool numb = true;
                while (!valid)
                {
                    int val = 0;
                    for (int i = 0; i < swapShieldChoice.length(); i++)
                    {
                        if (!isdigit(swapShieldChoice[i]))
                        {
                            numb = false;
                        }
                        else
                        {
                            val++;
                        }
                    }
                    if (val == swapShieldChoice.length())
                    {
                        numb = true;
                    }
                    else
                    {
                        val = 0;
                    }
                    if (numb)
                    {
                        if ((stoi(swapShieldChoice) >= 1 && stoi(swapShieldChoice) <= _inventory.size() + 1 && _inventory[stoi(swapShieldChoice) - 2].getType() == 'S') || stoi(swapShieldChoice) == 1)
                        { // ^ input validation
                            valid = true;
                        }
                        else
                        {
                            cout << "Invalid range or equipment type" << endl;
                            cout << "Which shield would you like to swap with " << _equipped[1].getName() << "?" << endl;
                            cout << "(1 Nothing)" << endl;
                            for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                            {
                                cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                            }
                            getline(cin, swapShieldChoice);
                        }
                    }
                    else
                    {
                        cout << "Invalid range or equipment type" << endl;
                        cout << "Which shield would you like to swap with " << _equipped[1].getName() << "?" << endl;
                        cout << "(1 Nothing)" << endl;
                        for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, swapShieldChoice);
                    }
                }
                if (swapShieldChoice == "1")
                {
                    return 9; // doesnt skip turn
                }
                else
                {
                    _inventory.push_back(_inventory[stoi(swapShieldChoice) - 2]); // duplicates
                    _inventory[stoi(swapShieldChoice) - 2] = _equipped[1];        // replaces
                    _equipped[1] = _inventory[_inventory.size() - 2];             // replaces
                    _inventory.pop_back();                                        // erases duplicate
                    cout << "Sucuessfully swapped! You are now holding the " << _equipped[1].getName() << endl;
                }
            }
            else
            {
                cout << "You have no shields to swap with!" << endl;
                return 9;
            }
        }
        else
        {
            // do nothing
        }
    }
    else // if the player only has a weapon equipped
    {
        string swapTypeChoice; // add if no weapons
        string swapWeaponChoice;
        string swapShieldChoice;
        string equipShieldChoice;
        cout << "Would you like to swap your weapon or shield?" << endl;
        cout << "(1) Weapon" << endl;
        cout << "(2) Shield" << endl;
        getline(cin, swapTypeChoice);
        swapTypeChoice = swapTypeChoiceVal(swapTypeChoice);
        if (swapTypeChoice == "1" || swapTypeChoice == "Weapon" || swapTypeChoice == "weapon")
        {
            bool hasWeapon = false;
            for (size_t i = 0; i < _inventory.size(); i++)
            {
                if (_inventory[i].getType() == 'D')
                {
                    hasWeapon = true;
                }
            }
            if (hasWeapon)
            {
                cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                cout << "(1) Nothing" << endl;
                for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                {
                    cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                }
                getline(cin, swapWeaponChoice);
                bool valid = false;
                bool numb = true;
                while (!valid)
                {
                    int val = 0;
                    for (int i = 0; i < swapWeaponChoice.length(); i++)
                    {
                        if (!isdigit(swapWeaponChoice[i]))
                        {
                            numb = false;
                        }
                        else
                        {
                            val++;
                        }
                    }
                    if (val == swapWeaponChoice.length())
                    {
                        numb = true;
                    }
                    else
                    {
                        val = 0;
                    }
                    if (numb)
                    {
                        if ((stoi(swapWeaponChoice) >= 1 && stoi(swapWeaponChoice) <= _inventory.size() + 1 && _inventory[stoi(swapWeaponChoice) - 2].getType() == 'D') || stoi(swapWeaponChoice) == 1)
                        { // ^ input validation
                            valid = true;
                        }
                        else
                        {
                            cout << "Invalid range or equipment type" << endl;
                            cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                            cout << "(1) Nothing" << endl;
                            for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                            {
                                cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                            }
                            getline(cin, swapWeaponChoice);
                        }
                    }
                    else
                    {
                        cout << "Invalid range or equipment type" << endl;
                        cout << "Which weapon would you like to swap with " << _equipped[0].getName() << "?" << endl;
                        cout << "(1) Nothing" << endl;
                        for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, swapWeaponChoice);
                    }
                }
                if (swapWeaponChoice == "1")
                {
                    return 9; // doesnt skip turn
                }
                else
                {
                    _inventory.push_back(_inventory[stoi(swapWeaponChoice) - 1]); // duplicates
                    _inventory[stoi(swapWeaponChoice) - 1] = _equipped[0];        // replaces
                    _equipped[0] = _inventory[_inventory.size() - 1];             // replaces
                    _inventory.pop_back();                                        // erases duplicate
                    cout << "Sucuessfully swapped! You are now wielding the " << _equipped[0].getName() << endl;
                }
            }
            else
            {
                cout << "You have no weapons to swap to!" << endl;
                return 9;
            }
        }
        else if (swapTypeChoice == "2" || swapTypeChoice == "Shield" || swapTypeChoice == "shield")
        {
            bool hasShield = false;
            for (size_t i = 0; i < _inventory.size(); i++)
            {
                if (_inventory[i].getType() == 'S')
                {
                    hasShield = true;
                }
            }
            if (hasShield)
            {
                cout << "Which shield would you like to equip?" << endl;
                cout << "(1) Nothing" << endl;
                for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                {
                    cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                }
                getline(cin, equipShieldChoice);
                bool valid = false;
                bool numb = true;
                while (!valid)
                {
                    int val = 0;
                    for (int i = 0; i < equipShieldChoice.length(); i++)
                    {
                        if (!isdigit(equipShieldChoice[i]))
                        {
                            numb = false;
                        }
                        else
                        {
                            val++;
                        }
                    }
                    if (val == equipShieldChoice.length())
                    {
                        numb = true;
                    }
                    else
                    {
                        val = 0;
                    }
                    if (numb)
                    {
                        if ((stoi(equipShieldChoice) >= 1 && stoi(equipShieldChoice) <= _inventory.size() + 1 && _inventory[stoi(equipShieldChoice) - 2].getType() == 'S') || stoi(equipShieldChoice) == 1)
                        { // ^ input validation
                            valid = true;
                        }
                        else
                        {
                            cout << "Invalid range or equipment type" << endl;
                            cout << "Which shield would you like to swap with " << _equipped[1].getName() << "?" << endl;
                            cout << "(1) Nothing" << endl;
                            for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                            {
                                cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                            }
                            getline(cin, equipShieldChoice);
                        }
                    }
                    else
                    {
                        cout << "Invalid range or equipment type" << endl;
                        cout << "Which shield would you like to swap with " << _equipped[1].getName() << "?" << endl;
                        cout << "(1) Nothing" << endl;
                        for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, equipShieldChoice);
                    }
                }
                if (equipShieldChoice == "1")
                {
                    return 9; // doesnt skip turn
                }
                else
                {
                    _equipped.push_back(_inventory[stoi(equipShieldChoice) - 2]);       // equips shield
                    eraseEquipment(stoi(equipShieldChoice) - 2);
                    // _inventory.erase(_inventory.begin() + stoi(equipShieldChoice) - 2); // erases from inventory
                    cout << "Successfully equipped " << _equipped[1].getName() << endl;
                }
            }
            else
            {
                cout << "You have no shields to equip!" << endl;
                return 9;
            }
        }
        else
        {
            // do nothing
        }
    }
    return 7;
};
int Entity::drop()
{
    cout << "Would you like to drop a piece of equipment or a potion?" << endl;
    cout << "(1) Equipment (weapons and shields)" << endl;
    cout << "(2) Potions" << endl;
    string dropTypeChoice;
    string dropEquipmentChoice;
    string dropPotionChoice;
    getline(cin, dropTypeChoice);
    dropTypeChoice = dropTypeChoiceVal(dropTypeChoice);
    if (dropTypeChoice == "1")
    {
        if (_inventory.size() == 0)
        {
            cout << "You have nothing to drop!" << endl;
            return 9;
        }
        else
        {
            cout << "Which piece of equipment would you like to drop?:" << endl;
            cout << "(1) Nothing" << endl;
            for (size_t i = 1; i <= _inventory.size(); i++)
            {
                cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
            }
            getline(cin, dropEquipmentChoice);
            bool valid = false;
            bool numb = true;
            while (!valid)
            {
                int val = 0;
                for (int i = 0; i < dropEquipmentChoice.length(); i++)
                {
                    if (!isdigit(dropEquipmentChoice[i]))
                    {
                        numb = false;
                    }
                    else
                    {
                        val++;
                    }
                }
                if (val == dropEquipmentChoice.length())
                {
                    numb = true;
                }
                else
                {
                    val = 0;
                }
                if (numb)
                {
                    if (stoi(dropEquipmentChoice) >= 1 && stoi(dropEquipmentChoice) <= _inventory.size() + 1)
                    { // ^ input validation
                        valid = true;
                    }
                    else
                    {
                        cout << "Invalid choice" << endl;
                        cout << "Which piece of equipment would you like to drop?:" << endl;
                        cout << "(1) Nothing" << endl;
                        for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, dropEquipmentChoice);
                    }
                }
                else
                {
                    cout << "Invalid choice" << endl;
                    cout << "Which piece of equipment would you like to drop?:" << endl;
                    cout << "(1) Nothing" << endl;
                    for (size_t i = 1; i <= _inventory.size(); i++) // prints options
                    {
                        cout << "(" << i + 1 << ") " << _inventory[i - 1].getName() << " (" << _inventory[i - 1].getType() << ")" << endl;
                    }
                    getline(cin, dropEquipmentChoice);
                }
            }
            if (dropEquipmentChoice == "1")
            {
                return 9; // doesnt skip turn
            }
            else
            {
                cout << "Successfully dropped the " << _inventory[stoi(dropEquipmentChoice) - 2].getName() << endl;
                eraseEquipment(stoi(dropEquipmentChoice) - 2);
                // _inventory.erase(_inventory.begin() + stoi(dropEquipmentChoice) - 2); // erases choice - 1 from vector
            }
        }
    }
    else
    {
        if (_potions.size() == 0)
        {
            cout << "You have nothing to drop!" << endl;
            return 9;
        }
        else
        {
            cout << "Which potion would you like to drop?:" << endl;
            cout << "(1) Nothing" << endl;
            for (size_t i = 1; i <= _potions.size(); i++)
            {
                cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " (" << _potions[i - 1].getType() << ")" << endl;
            }
            getline(cin, dropPotionChoice);
            bool valid = false;
            bool numb = true;
            while (!valid)
            {
                int val = 0;
                for (int i = 0; i < dropPotionChoice.length(); i++)
                {
                    if (!isdigit(dropPotionChoice[i]))
                    {
                        numb = false;
                    }
                    else
                    {
                        val++;
                    }
                }
                if (val == dropPotionChoice.length())
                {
                    numb = true;
                }
                else
                {
                    val = 0;
                }
                if (numb)
                {
                    if (stoi(dropPotionChoice) >= 1 && stoi(dropPotionChoice) <= _potions.size() + 1)
                    { // ^ input validation
                        valid = true;
                    }
                    else
                    {
                        cout << "Invalid choice" << endl;
                        cout << "Which potion would you like to drop?:" << endl;
                        cout << "(1) Nothing" << endl;
                        for (size_t i = 1; i <= _potions.size(); i++) // prints options
                        {
                            cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " (" << _potions[i - 1].getType() << ")" << endl;
                        }
                        getline(cin, dropPotionChoice);
                    }
                }
                else
                {
                    cout << "Invalid choice" << endl;
                    cout << "Which potion would you like to drop?:" << endl;
                    cout << "(1) Nothing" << endl;
                    for (size_t i = 1; i <= _potions.size(); i++) // prints options
                    {
                        cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " (" << _potions[i - 1].getType() << ")" << endl;
                    }
                    getline(cin, dropPotionChoice);
                }
            }
            if (dropPotionChoice == "1")
            {
                return 9; // doesnt skip turn
            }
            else
            {
                cout << "Successfully dropped " << _potions[stoi(dropPotionChoice) - 2].getName() << endl;
                erasePotions(stoi(dropPotionChoice) - 2);
                // _potions.erase(_potions.begin() + stoi(dropPotionChoice) - 2); // erases choice - 1 from vector
            }
        }
    }
    return 7;
};
int Entity::usePotion()
{
    string usePotionChoice;
    if (_potions.size() == 0)
    {
        cout << "You have not potions!" << endl;
    }
    else
    {
        cout << "Which potion do you want to use?" << endl;
        cout << "(1) None of them" << endl;
        for (size_t i = 1; i <= _potions.size(); i++)
        {
            cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " x" << _potions[i - 1].getQuantity() << endl;
        }
        getline(cin, usePotionChoice);
        bool valid = false;
        bool numb = true;
        while (!valid)
        {
            int val = 0;
            for (int i = 0; i < usePotionChoice.length(); i++)
            {
                if (!isdigit(usePotionChoice[i]))
                {
                    numb = false;
                }
                else
                {
                    val++;
                }
            }
            if (val == usePotionChoice.length())
            {
                numb = true;
            }
            else
            {
                val = 0;
            }
            if (numb)
            {
                if (stoi(usePotionChoice) >= 1 && stoi(usePotionChoice) <= _potions.size() + 1)
                { // ^ input validation
                    valid = true;
                }
                else
                {
                    cout << "Invalid choice" << endl;
                    cout << "Which potion do you want to use?" << endl;
                    cout << "(1) None of them" << endl;
                    for (size_t i = 1; i <= _potions.size(); i++) // prints options
                    {
                        cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " x" << _potions[i - 1].getQuantity() << endl;
                    }
                    getline(cin, usePotionChoice);
                }
            }
            else
            {
                cout << "Invalid choice" << endl;
                cout << "Which potion do you want to use?" << endl;
                cout << "(1) None of them" << endl;
                for (size_t i = 1; i <= _potions.size(); i++) // prints options
                {
                    cout << "(" << i + 1 << ") " << _potions[i - 1].getName() << " x" << _potions[i - 1].getQuantity() << endl;
                }
                getline(cin, usePotionChoice);
            }
        }
        if (usePotionChoice == "1")
        {
            return 9; // doesnt skip turn
        }
        else
        {
            int usedPotionIndex = stoi(usePotionChoice) - 2;
            string usedPotionDescription = _potions[usedPotionIndex].getDescription();
            int effectAmount = _potions[usedPotionIndex].getEffectValue();
            if (usedPotionDescription[0] == 'R' && usedPotionDescription[8] == 'H' && usedPotionDescription[17] == 'a') // restore HP and stamina
            {
                changeHp(effectAmount), changeStam(effectAmount);
                cout << "Increased HP and Stamina by " << effectAmount << endl;
            }
            else if (usedPotionDescription[0] == 'R' && usedPotionDescription[8] == 'H') // restore hp
            {
                changeHp(effectAmount);
                cout << "Increased HP by " << effectAmount << endl;
            }
            else if (usedPotionDescription[0] == 'R' && usedPotionDescription[8] == 's') // restore stam
            {
                changeStam(effectAmount);
                cout << "Increased Stamina by " << effectAmount << endl;
            }
            else if (usedPotionDescription[0] == 'C' && usedPotionDescription[1] == 'l') // cleanse
            {
                if (getCondition() == 'H')
                {
                    cout << "Wow. What a waste. You are still healthy...";
                }
                else
                {
                    setCondition('H');
                    cout << "You have been cleansed back to being healthy!" << endl;
                }
            }
            else if (usedPotionDescription[17] == 'U' && usedPotionDescription[18] == 'l') // Philter of Wisdom
            {
                changeUltCharge(1);
                cout << getName() << " gains another Ultimate charge!" << endl;
            }
            else if (usedPotionDescription[0] == 'I' && usedPotionDescription[9] == 'w') // Siren's Salve
            {
                if (getEquippedSize() == 1)
                {
                    getEquipped(0).changeDamage(20);
                    cout << "Permanently increased damage of " << getEquipped(0).getName() << " by 20!" << endl;
                }
                else
                {
                    cout << "Add 20 damage to " << getEquipped(0).getName() << " or 20 defense to " << getEquipped(1).getName() << "?" << endl;
                    cout << "(1) " << getEquipped(0).getName() << " +20 damage" << endl;
                    cout << "(2) " << getEquipped(1).getName() << " +20 defense" << endl;
                    string defOrDamBuff;
                    getline(cin, defOrDamBuff);
                    defOrDamBuff = defOrDamBuffVal(getEquipped(0).getName(), getEquipped(1).getName(), defOrDamBuff);
                    if (defOrDamBuff == "1")
                    {
                        getEquipped(0).changeDamage(20);
                        cout << "Permanently increased damage of " << getEquipped(0).getName() << " by 20!" << endl;
                    }
                    else
                    {
                        getEquipped(1).changeDefense(20);
                        cout << "Permanently increased defense of " << getEquipped(1).getName() << " by 20!" << endl;
                    }
                }
            }
            else if (usedPotionDescription[0] == 'P' && usedPotionDescription[1] == 'e')
            {
                _equipped[0].changeDamage(effectAmount); // add dmg to weapon in hand
                cout << "The " << _equipped[0].getName() << " gained " << effectAmount << " damage!" << endl;
            }
            _potions[usedPotionIndex].changeQuantity(-1);
            if (_potions[usedPotionIndex].getQuantity() == 0) // removes potion from potioninventory if there are zero left
            {
                erasePotions(usedPotionIndex);
                // _potions.erase(_potions.begin() + usedPotionIndex);
            }
        }
    }
    return 7;
};
void Entity::updateEquipment(Equipment equipment)
{
    if (_equipped.size() == 0)
    {
        _equipped.push_back(equipment);
    }
    else if (_equipped.size() == 1)
    {
        if (equipment.getType() == 'S') // if shield is picked up and slot is open, goes there
        {
            _equipped.push_back(equipment);
        }
        else
        {
            _inventory.push_back(equipment);
        }
    }
    else
    {
        _inventory.push_back(equipment);
    }
};
void Entity::updatePotion(Potions potion)
{
    bool potionFound = false;
    for (size_t i = 0; i < _potions.size(); i++) // ups potion quantity by one if found in playr inventory
    {
        if (_potions[i].getName() == potion.getName())
        {
            _potions[i].changeQuantity(1);
            potionFound = true;
        }
    }
    if (!potionFound) // otherwise adds new potion to inv
    {
        _potions.push_back(potion);
    }
};

// menus
void Entity::entityStatsmenu()
{
    cout << getName() << " | "
         << "HP: " << getHp() << " | "
         << "Stamina: " << getStam() << " | "
         << "Defense: " << getDef() << endl;
    cout << "Condition: " << getCondition() << " | "
         << "Elemental Weakness: " << getElementalWeakness() << " | "
         << "Gold: " << getGold() << endl;
}

// player
void Entity::poisonOrDeseaseTick()
{
    if (getCondition() == 'P')
    {
        changeHp(-5);
        cout << getName() << " lost 5 health due to being poisoned!" << endl;
    }
    else if (getCondition() == 'D')
    {
        changeStam(-5);
        cout << getName() << " lost 5 stamina due to being diseased!" << endl;
    }
    else
    {
        // do nothing
    }
}
