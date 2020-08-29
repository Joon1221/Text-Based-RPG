#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Board;
class Unit;
class Prop;
class Item;
class Magic;

//==============================================================================
// 1st Generation
//==============================================================================

class Item {
protected:
    char shape;
    string name;
    int price;
    int level;
    
    int row;
    int col;

    bool disposed;
    bool moved;
    bool processed; // will be used by Tile::processThrowingItems()
    bool disposable;

    bool pickUp;

public:
    Item();
    Item(Item &other);
    Item(char shape, string name, int price, bool disposable, int level);
    
    virtual Item &operator=(Item &other);
    
    virtual ~Item();
    virtual void print();
    virtual void print(ostream &out);
    virtual void printPartSpec();
    virtual void printFullSpec();
    
    char getShape();
    string getName();
    int getPrice();
    int getLevel();
    
    int getRow();
    void setRow(int row);
    int getCol();
    void setCol(int col);
    
    void setMoved(bool moved);

    virtual bool isEquipable();
    virtual bool isConsumable();
    virtual bool isReusable();
    
    virtual bool use(Unit *unit) = 0; // pure virtual finction
    virtual void trigger();
    bool hasBeenDisposed();
    bool hasBeenMoved();
    bool hasBeenProcessed();
    void resetProcessed();
    void dispose();
    bool canPickUp();

    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual bool move(int row, int col);

    virtual Item *clone() = 0;
    virtual string getID() = 0; // pure virtual function

    friend ostream &operator<<(ostream &out, Item &item);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

ostream &operator<<(ostream &out, Item &item);
Item *createRandItem();
Item *createItemByShape(char shape);
Item *createItemByID(string itemID);

//==============================================================================
// 2nd Generation
//==============================================================================
class ConsumableItem : public Item {
protected:
public:
    ConsumableItem();
    ConsumableItem(ConsumableItem &other);
    ConsumableItem(char shape, string name, int price, bool disposable, int level);
    
    virtual Item &operator=(Item &other);

    virtual void printFullSpec();
    
    bool isConsumable();
    virtual bool isKey();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class EquipableItem : public Item {
protected:
public:
    EquipableItem();
    EquipableItem(EquipableItem &other);
    EquipableItem(char shape, string name, int price, bool disposable, int level);
    
    virtual Item &operator=(Item &other);

    virtual void printFullSpec();

    bool isEquipable();
    virtual bool isArmor();
    virtual bool isWeapon();
    virtual bool getRangeAttack();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class ReusableItem : public Item {
protected:
public:
    ReusableItem();
    ReusableItem(ReusableItem &other);
    ReusableItem(char shape, string name, int price, bool disposable, int level);
    
    virtual Item &operator=(Item &other);
    
    virtual void printFullSpec();
    
    bool isReusable();
    virtual bool isTorch();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//==============================================================================
// 3rd Generation
//==============================================================================

class Potion: public ConsumableItem {
protected:
    int hp;
    int mp;
    int potionType;

public:
    Potion();
    Potion(Potion &other);
    Potion(char shape, string name, int price, int level, int hp, int mp, int potionType);
    virtual ~Potion();
    
    virtual Item &operator=(Item &other);

    virtual void printFullSpec();
    
    void print(ostream &out);

    virtual bool use(Unit *unit);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class Key: public ConsumableItem {
protected:
    int keyType;
    
public:
    Key();
    Key(Key &other);
    Key(char shape, string name, int price, int level, int keyType);
    virtual ~Key();
    
    virtual Item &operator=(Item &other);

    virtual void printFullSpec();
    
    void print(ostream &out);
    
    bool isKey(); 

    int getKeyType();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Key *getRandomKey();

class Arrow: public ConsumableItem {
protected:
    int atk;
    int dir;
    int maxRange;
    int currentFlyingDist;
    
    Unit *hero;
    
public:
    Arrow();
    Arrow(Arrow &other);
    Arrow(int atk, int dir, Unit *hero);
    Arrow(char shape, string name, int price, int level, int atk, int dir, int maxRange, Unit *hero);
    virtual ~Arrow();
    
    virtual Item &operator=(Item &other);

    virtual void print(ostream &out);    
    virtual void printFullSpec();

    virtual bool use(Unit *unit);
    
    virtual bool move(int row, int col);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class Armor: public EquipableItem {
protected:
    int def;
    int durability;
    int bodyPartID;
    int armorType;
    
public:
    Armor();
    Armor(Armor &other);
    Armor(char shape, string name, int price, int level, int def, int durability, int bodyPartID, int armorType);
    virtual ~Armor();
    
    virtual Item &operator=(Item &other);

    virtual void printFullSpec();
    void print(ostream &out);

    int getDef();
    int getBodyPartID();
    
    bool isArmor();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Armor *getRandomArmor();
Armor *getRandomArmor(char shape);
bool isArmor(char shape);

class Weapon: public EquipableItem {
protected:
    int atk;
    int durability;
    int numHands;
    bool rangeAttack;
    int weaponType;
    int job;
    
public:
    Weapon();
    Weapon(Weapon &other);
    Weapon(char shape, string name, int price, int level, int atk, int durability, int numHands, bool rangeAttack, int weaponType, int job);
    virtual ~Weapon();
    
    virtual Item &operator=(Item &other);

    virtual void printPartSpec();
    virtual void printFullSpec();
    
    void print(ostream &out);
    
    int getAtk();
    bool getRangeAttack();
    int getNumHands();
    int getWeaponType();
    int getJob();
    
    virtual bool use(Unit *unit);
    
    bool isWeapon();
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Weapon *getRandomWeapon();
Weapon *getRandomWeapon(char shape);
bool isWeapon(char shape);

class Bomb : public ConsumableItem {
protected:
    int range;
    int atk;
    
public:
    Bomb();
    Bomb(Bomb &other);
    Bomb(char shape, string name, int price, bool disposable, int range, int atk);
    
    virtual Item &operator=(Item &other);
    
    virtual ~Bomb();
    
    virtual void printPartSpec();
    virtual void printFullSpec();
    
    void print(ostream &out);
    
    virtual bool use(Unit *unit);
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class TimeBomb : public ConsumableItem {
protected:
    int range;
    int atk;
    
public:
    TimeBomb();
    TimeBomb(TimeBomb &other);
    TimeBomb(char shape, string name, int price, bool disposable, int range, int atk);
    
    virtual Item &operator=(Item &other);
    
    virtual ~TimeBomb();
    
    virtual void printPartSpec();
    virtual void printFullSpec();
    
    void print(ostream &out);
    
    virtual bool use(Unit *unit);
    virtual void trigger();
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual Item *clone();
    virtual string getID();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class Magicscroll : public ConsumableItem {
protected:
    
    Magic *magic;
    
public:
    Magicscroll();
    Magicscroll(Magicscroll &other);
    Magicscroll(char shape, string name, int price, bool disposable);
    
    virtual Item &operator=(Item &other);
    
    virtual ~Magicscroll();
    
    virtual void printPartSpec();
    virtual void printFullSpec();
    
    void print(ostream &out);
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class Torch: public ReusableItem {
protected:
    int range;
    
public:
    Torch();
    Torch(Torch &other);
    Torch(char shape, string name, int price, int level, int range);
    virtual ~Torch();
    
    virtual Item &operator=(Item &other);
    
    virtual void printFullSpec();
    
    void print(ostream &out);
    
    bool isTorch(); 
    
    int getRange();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
