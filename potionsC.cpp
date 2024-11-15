#include "potionsC.h"

// getters and setters
string Potions::getName()
{
    return _name;
}
void Potions::setName(string name) 
{
    _name = name;
}
string Potions::getDescription()
{
    return _description;
}
char Potions::getType()
{
    return _type;
}
double Potions::getEffectValue()
{
    return _effect_value;
}
double Potions::getPrice()
{
    return _price;
}
int Potions::getQuantity()
{
    return _quantity;
}
void Potions::changeQuantity(int amount)
{
    _quantity += amount;
}

// constuctor
Potions::Potions(string potionLine)
{
    string tempArr[6];
    split(potionLine, '|', tempArr, 6);
    _name = tempArr[0];
    _description = tempArr[1];
    // if statement that determines whether to increase HP or stamina or both
    _type = tempArr[2][0];
    _effect_value = stod(tempArr[3]);
    // element of potions always is none
    _price = stod(tempArr[5]);
    _quantity = 1; // potions start with no quantity
};
Potions::Potions()
{
    _name = "dummy";
};
