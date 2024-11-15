#include "equipmentC.h"

// getters and setters
string Equipment::getName() // get name
{
    return _name;
}
void Equipment::setName(string name) // set name
{
    _name = name;
}
char Equipment::getType() // get name
{
    return _type;
}
char Equipment::getElement() // get name
{
    return _element;
}
double Equipment::getDamage()
{
    return _damage;
}
double Equipment::getDefense()
{
    return _defense;
}
double Equipment::getPrice()
{
    return _price;
}
void Equipment::changeDamage(int dmgChange)
{
    _damage += dmgChange;
}
void Equipment::changeDefense(int defChange)
{
    _defense += defChange;
}
void Equipment::setPoison()
{
    poison = true;
}
bool Equipment::getPoison()
{
    return poison;
}

// contructors
Equipment::Equipment(string equipLine) // constructor
{
    string tempArr[6];
    split(equipLine, '|', tempArr, 6);
    _name = tempArr[0];
    _description = tempArr[1];
    _type = tempArr[2][0];
    if (_type == 'D') // checks to add the effect value to dmg or def
    {
        _damage = stod(tempArr[3]);
        _defense = 0;
    }
    else if (_type == 'S')
    {
        _defense = stod(tempArr[3]);
        _damage = 0;
    }
    _element = tempArr[4][0];
    _price = stod(tempArr[5]);
    poison = false;
};
Equipment::Equipment()
{
    _name = "test";
};
