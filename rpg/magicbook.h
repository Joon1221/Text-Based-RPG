#ifndef MAGICBOOK_H
#define MAGICBOOK_H

class Item;
class Unit;
class Magic;

class Magicbook {
private:
    Magic **magicbook;
    int maxNumItems;
    int numItems;
    
    // for Iterator
    int curIndexForIter;

    void initMagicbook(int maxNumItems);
    void deleteMagicbook();

public:
    Magicbook();
    Magicbook(int maxNumItems);
    virtual ~Magicbook();
    
    void print();
    void printIndex(int startIndex);
    
    int getMaxNumItems();
    int getNumItems();
    
    int getSkillNumberAtIndex(int index);
    
    bool add(Magic *magic);
    bool setMagicAtIndex(int index, Magic *magic);
    Magic *get(int indexToRemove);
    Magic *remove(int indexToRemove);
    bool cast(int indexToUse, Unit *unit);

    bool isFull();
    int capacity();
    
    // Iterator interface
    bool hasMore();
    Magic *next();
    void resetIter();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
