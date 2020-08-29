#ifndef PROP_H
#define PROP_H

class Unit;
class Item;

class Prop {
protected:
    char shape;
    bool climbable;
    
public:
    Prop();
    Prop(char shape, bool climbable);
    virtual ~Prop();
    virtual void print();
    
    bool isClimbable();
    virtual bool canGoThroughByThrowableItem();
    
    virtual bool isTree();
    virtual bool isChest();
    virtual bool isWall();
    virtual bool isExit();

    virtual int getLockLevel();
    
    virtual bool trigger(int row, int col, Unit *unit);
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual string getID() = 0;

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Prop *createPropByShape(char shape);
Prop *createPropByID(string propID);

class Wall : public Prop {
private:
public:
    Wall();
    Wall(char shape, bool climbable);
    virtual ~Wall();
    
    void print();
    
    virtual bool isWall();

    virtual string getID();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class Exit : public Prop {
private:
public:
    Exit();
    Exit(char shape, bool climbable);
    virtual ~Exit();
    
    void print();
    
    bool isClimbable();
    virtual bool isExit();
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
