#ifndef BACKPACK_H
#define BACKPACK_H

class Item;
class Key;

class Backpack {
private:
    Item **items;
    int numItems;    // size
    int maxNumItems; // capacity
    
    // for Iterator
    int curIndexForIter;
    
    void initBackpack(int maxNumItems);
    void deleteBackpack();

public:
    Backpack();
    Backpack(int maxNumItems);
    virtual ~Backpack();
    
    void print();
    void printIndex(int startIndex);
    
    bool push(Item *item);
	
    Item *getItemAt(int index);
    Key *getBestKey(); // remove the best key found and return it
    Key *checkBestKey(); // return the best key found without removing
    
	void receiveItem(Item *curItem);
    Item *removeItemAt(int index);
    
    bool isFull();
    bool isEmpty();

    int size();
    int capacity();
    
    // Iterator interface
    bool hasMore();
    Item *next();
    void resetIter();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
