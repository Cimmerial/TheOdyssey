#ifndef EP_H
#define EP_H

#include "helperC.h"

struct Equipment
{
private:
    string _name;
    string _description;
    char _type;
    char _element;
    double _damage;
    double _defense;
    double _price;
    bool poison;
    // ult ability var with ult ability subclass? maybe just if name of equip is X then int ultAbility = Y, alters Z depending on Y
public:
    string getName();
    void setName(string name);
    char getType();
    char getElement();
    double getDamage();
    double getDefense();
    double getPrice();
    void changeDamage(int dmgChange);
    void changeDefense(int defChange);
    void setPoison();
    bool getPoison();
    
    Equipment(string equipLine);
    Equipment();
};
#endif