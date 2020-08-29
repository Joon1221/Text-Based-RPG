#ifndef INVENTORY_H
#define INVENTORY_H

class Item;
class Unit;

class Inventory {
private:
    Item **slots;
    int maxNumItems;
    int numItems;
    
    // for Iterator
    int curIndexForIter;

    void initSlots(int maxNumItems);
    void deleteSlots();

public:
    Inventory();
    Inventory(int maxNumItems);
    virtual ~Inventory();
    
    void print();
    void printIndex(int startIndex);
    
    int getMaxNumItems();
    int getNumItems();
    
    bool add(Item *item);
    void addPotion(int amount, Unit *unit);
    bool buyPotion(int amount, Unit *unit);
    bool setItemAtIndex(int index, Item *item);
    Item *get(int indexToRemove);
    Item *remove(int indexToRemove);
    bool use(int indexToUse, Unit *unit);

    // remove the key and return the key to the caller.
    Key *getBestKey(); // remove the best key found and return it
    Key *checkBestKey(); // return the best key found without removing
    bool addKey(Key *key, Unit *unit);

    bool isFull();
    int capacity();
    
    // Iterator interface
    bool hasMore();
    Item *next();
    void resetIter();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
