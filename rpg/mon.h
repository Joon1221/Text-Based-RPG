#ifndef MON_H
#define MON_H

class Unit;

//------------------------------------------------------------------------------
// class Hero: child class of class Unit
//------------------------------------------------------------------------------
class Mon : public Unit {
protected:
    int range;
    
public:
    Mon();
    Mon(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
        int gold, int exp, int level, int currentMaxExpToLevelUp,
        bool freeze, int range);
    virtual ~Mon();
    
    virtual void print();

    virtual void setRange(int range);

    virtual void move(int moveDir);
    virtual void interact(Unit *unit);

    bool isMon();
    
    bool moveOrFollowHuman(int moveDir);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif

