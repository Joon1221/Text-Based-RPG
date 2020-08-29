#ifndef PAPERDOLL_H
#define PAPERDOLL_H

class Item;
class Armor;
class Weapon;
class Unit;

class Paperdoll {
private:

    Armor *head;
    Armor *chest;
    Armor *back;
    Armor *hands;
    Armor *legs;
    Armor *feet;
    
    Weapon *leftHand;
    Weapon *rightHand;
    
public:
    Paperdoll();
    Paperdoll(Paperdoll &other);
    virtual ~Paperdoll();
    void print();
    void printIndex();
   
    bool equip(Item *item, Unit *unit);
    Item *unequip(int bodyPartID, Unit *unit);
    Armor *getArmor(int bodyPartID);
    Weapon *getWeapon(int bodyPartID);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
