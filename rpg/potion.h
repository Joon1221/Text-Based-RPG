
#ifndef POTION_H
#define POTION_H

#include "main.h"
#include "unit.h"
#include "item.h"

class Potion: public Item {
protected:
    int hp;
    
public:
    Potion();
    Potion(char shape, int hp);
    virtual ~Potion();
    void print();
    
    virtual bool use(Unit *unit);
};

#endif
