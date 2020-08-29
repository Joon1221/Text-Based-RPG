#ifndef DRAGON_H
#define DRAGON_H

class Dragon : public Unit {
protected:
public:
    int len; // 전체 길이.
    // prev가 NULL인 경우는 자신이 head라는 얘기이고..
    Dragon *prev;
    // next가 NULL인 경우는 자신이 tail라는 얘기이고..
    Dragon *next;
    
    // private helper functions
    void initDragon(int len);
    void destroyDragon();
    
    Dragon();
    Dragon(char shape, int len);
    Dragon(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
           int gold, int exp, int level, int currentMaxExpToLevelUp,
           bool freeze, int len);

    virtual ~Dragon();
    
    virtual void print();
    virtual void printStat();
    
    virtual bool isDragon();
    
    virtual void move(int moveDir);
    virtual void move(int row, int col); // Dragon만 가진 기능.
    virtual void interact(Unit *unit);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Dragon *createDragon(int row, int col, int len);
void createDragonWithHead(Dragon *dragonHead, int len);

#endif
