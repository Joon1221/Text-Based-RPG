#ifndef CHEST_H
#define CHEST_H

class Item;
class Unit;

class Chest : public Prop {
private:
    bool locked;

    int lockLevel;

    Item *itemToDrop[MAX_ITEMS_CHEST];
    int numItems;
    
public:
    
    Chest();
    Chest(char shape, bool locked, int lockLevel);
    void initChest(bool chestLocked, int lockLevel);
    
    virtual ~Chest();

    void print();
    
    void unlock();
    void lock();
    
    bool isLocked();
   
    virtual bool isChest();
    
    virtual int getLockLevel();
    bool trigger(int row, int col, Unit *unit);

    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Chest *getRandomChest();

#endif
