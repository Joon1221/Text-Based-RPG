#ifndef HERO_H
#define HERO_H

class Unit;
class Board;
class Magicbook;
class Car;

//------------------------------------------------------------------------------
// class Hero: child class of class Unit
//------------------------------------------------------------------------------
class Hero : public Unit {
protected:
    //char shape;
    int viewportRangeRow;
    int viewportRangeCol;
    int job;
    int nightRange;
    bool onCar;

    Inventory *slots;
    Backpack *backpack;
    Paperdoll *paperdoll;
    Magicbook *magicbook;
    Car *car;
    
    void initStorage();
    void destroyStorage();

    void initClassEquipment();

public:
    Hero();
    Hero(char shape, int row, int col);
    Hero(char shape, int hp, int maxHp, int mp, int maxMp, int meeleAtk, int rangeAtk, int def, int job);
    Hero(char shape, int hp, int maxHp, int mp, int maxMp, int meeleAtk, int rangeAtk, int gold, int exp, int level, int currentMaxExpToLevelUp, bool freeze,
         int viewportRangeRow, int viewportRangeCol, int nightRange, int maxNumSlots, int backpackCapacity);
    virtual ~Hero();
    
    virtual void printStat(int slotsStartIndex, bool showBackpack, int backpackStartIndex);
    virtual void printStatDual(int slotsStartIndex, bool showBackpack, int backpackStartIndex, Unit *unit2, int slotsStartIndex2, bool showBackpack2, int backpackStartIndex2);
    void showItemsListToSell();
    
    virtual int getViewportRangeRow();
    virtual void setViewportRangeRow(int viewportRangeRow);
    virtual int getViewportRangeCol();
    virtual void setViewportRangeCol(int viewportRangeCol);
    
    virtual int getNightRange();
    
    virtual int getJob();
    
    virtual bool getOnCar();
    virtual void setOnCar(int onCar);

    virtual bool unlock(Prop *prop);

    virtual void move(int moveDir);
    
    bool isHero();
    
    virtual Inventory *getSlots();
    virtual bool useItemInSlots(int indexOfItem);
    
    virtual void addPotion(int amount);
    virtual bool buyPotion(int amount);
    
    virtual Magicbook *getMagicbook();
    virtual bool useMagicInMagicbook(int indexOfItem);
    
    virtual bool addMagicToMagicbook(Magic *magic);
    
    virtual Car *getCar();
    virtual void getInCar(Car *car);
    virtual void getOffCar();
    
    virtual void setHeroFacingDirection(int heroFacingDirection);
    
    virtual Weapon *getRightHand();
    virtual Weapon *getLeftHand();
    
    virtual bool moveItemSlotToBackpack(int indexSlotItem);
    virtual bool moveItemBackpackToSlot(int indexBackpack, int indexSlotItem);
    virtual bool moveItemSlotToSlot(int indexSlotItem, int indexSlotItem2);

    virtual bool equip(Item *item);
    virtual Item *unequip(int bodyPartID);
    
    virtual bool hasRoom();
    virtual void receiveItem(Item *item);
    virtual Item *removeItemByIndex(int index);
    
    virtual void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
    
    void freezeMons(int row, int col);
    void unfreezeMons(int row, int col);
    
    virtual bool rangeAttack(int dir);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
