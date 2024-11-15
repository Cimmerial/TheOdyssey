#ifndef POTIONS_H
#define POTIONS_H

#include "helperC.h"


struct Potions
{
private:
    string _name;
    string _description;
    char _type;
    double _effect_value;
    double _price;
    int _quantity;

public:
    string getName();
    void setName(string name);
    string getDescription();
    char getType();
    double getEffectValue();
    double getPrice();
    int getQuantity();
    void changeQuantity(int amount);
    Potions(string potionLine);
    Potions();
};

#endif