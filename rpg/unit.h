#ifndef UNIT_H
#define UNIT_H

class Item;
class Inventory;
class Backpack;
class Paperdoll;
class Board;
class Weapon;
class Prop;
class Magicbook;
class Magic;
class Car;

class Unit {
protected:
    char shape;
    
    int unitCurDir;
    
    int row;
    int col;
    
    int hp; // health point
    int maxHp; // max health point
    int mp; // magic(mana) point
    int maxMp; // max magic(mana) point
    int meleeAtk; // melee attack point
    int rangeAtk; // range attack point
    int def; // defence point
    //int speed; // moving speed 
    
    int gold;
    int exp;
    
    int currentMaxExpToLevelUp;
    int level;
    
    bool freeze;
    int heroFacingDirection;
    
    Unit *unitEngaged;

public:
    Unit();
    Unit(char shape, int row, int col, int hp, int maxHp, int meleeAtk, int rangeAtk,int gold, int exp, int level, int currentMaxExpToLevelUp, bool freeze);
    
    virtual ~Unit();
    
    virtual void reset();
    
    virtual void print();
    virtual void printStat();
    virtual void printStat(int slotsStartIndex, bool showBackpack, int backpackStartIndex);
    virtual void printStatDual(int slotsStartIndex, bool showBackpack, int backpackStartIndex, Unit *unit2, int slotsStartIndex2, bool showBackpack2, int backpackStartIndex2);
    virtual void showItemsListToSell();

    void setShape(char shape);
    
    int getRow();
    void setRow(int row);
    int getCol();
    void setCol(int col);
    
    int getHp();
    void setHp(int hp);
    void incHp(int hpToInc);
    void decHp(int hpToDec);
    
    int getMaxHp();
    void setMaxHp(int maxHp);
    
    int getMp();
    void setMp(int mp);
    void incMp(int mpToInc);
    void decMp(int mpToDec);
    
    int getMaxMp();
    void setMaxMp(int maxMp);
    
    int getMeleeAtk();
    void incMeleeAtk(int atkToInc);
    void decMeleeAtk(int atkToDec);
    
    int getRangeAtk();
    void incRangeAtk(int atkToInc);
    void decRangeAtk(int atkToDec);
    
    int getDef();
    void incDef(int defToInc);
    void decDef(int defToDec);
    
    int getGold();
    void setGold(int gold);
    void incGold(int goldToInc);
    void decGold(int goldToDec);
    
    int getExp();
    void setExp(int exp);
    void incExp(int expToInc);
    void decExp(int expToDec);
    
    int getCurrentMaxExpToLevelUp();
    void setCurrentMaxExpToLevelUp(int currentMaxExpToLevelUp);

    int getLevel();
    void setLevel(int level);

    bool getFreeze();
    void setFreeze(bool freeze);
    
    virtual int getDir();
    virtual void setDir(int dir);
    virtual int getPrevDir();
    virtual void setPrevDir(int prevDir);
    
    virtual bool getIdle();
    virtual void setIdle(int idle);
    
    virtual bool getOnCar();
    virtual void setOnCar(int onCar);
    
    virtual int getViewportRangeRow();
    virtual void setViewportRangeRow(int viewportRangeRow);

    virtual int getViewportRangeCol();
    virtual void setViewportRangeCol(int viewportRangeCol);

    virtual int getNightRange();
    
    bool isDead();
    
    virtual void changeDirection(int moveDir);
    
    Unit *getUnitEngaged();
    void setUnitEngaged(Unit *unitEngaged);
    
    int getHeroFacingDirection();
    void setHeroFacingDirection(int heroFacingDirection);
    
    virtual bool isHero();
    virtual bool isMon();
    virtual bool isBoss();
    virtual bool isMerchant();
    virtual bool isCar();
    virtual bool isDragon();

    virtual bool unlock(Prop *prop);

    virtual void move(int moveDir) = 0;
    
    // * Hero only functions.
    virtual int getJob();
    
    virtual Inventory *getSlots();
    virtual bool pickUp(Item *item);
    virtual bool useItemInSlots(int indexOfItem);
    
    virtual void addPotion(int amount);
    virtual bool buyPotion(int amount);
    
    virtual Magicbook *getMagicbook();
    virtual bool useMagicInMagicbook(int indexOfItem);
    
    virtual bool addMagicToMagicbook(Magic *magic);
    
    virtual Car *getCar();
    virtual void getInCar(Car *car);
    virtual void getOffCar();

    virtual Weapon *getRightHand();
    virtual Weapon *getLeftHand();
    
    virtual bool moveItemSlotToBackpack(int indexSlotItem);
    virtual bool moveItemBackpackToSlot(int indexBackpack, int indexSlotItem);
    virtual bool moveItemSlotToSlot(int indexSlotItem, int indexSlotItem2);
    
    virtual bool equip(Item *item);
    virtual Item *unequip(int bodyPartID);
    
    virtual void interact(Unit *unit);
    
    virtual bool hasRoom();
    virtual void receiveItem(Item *item);
    virtual Item *removeItemByIndex(int index);
    
    virtual void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
    
    virtual bool rangeAttack(int dir);
    
    virtual string getID() = 0;

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Unit *createUnitByShape(char shape, int row, int col);

#endif
