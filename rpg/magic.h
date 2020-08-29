#ifndef MAGIC_H
#define MAGIC_H

class Unit;
class Item;
class Prop;

class Magic {
protected:
    char shape;
    int job;
    int skillNumber;

public:
    Magic();
    Magic(Magic &other);
    Magic(char shape, int job, int skillNumber);
    
    virtual Magic &operator=(Magic &other);
    
    virtual ~Magic();
    
    void print();
    void printFullSpec();
    
    int getJob();
    int getSkillNumber();
    
    virtual bool cast(Unit *unit) = 0; // pure virtual functions
    void effect(Unit *caster, Unit *unit, Item *item, Prop *prop);

    virtual Magic *clone() = 0; // pure virtual functions
    virtual string getID() = 0; // pure virtual function

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Magic *createRandMagic();
Magic *createMagicByID(string magicID);

class MagicKnightLightHealRing : public Magic {
private:
public:
    MagicKnightLightHealRing();
    MagicKnightLightHealRing(MagicKnightLightHealRing &other);
    MagicKnightLightHealRing(char shape, int job, int skillNumber);
    
    virtual MagicKnightLightHealRing &operator=(MagicKnightLightHealRing &other);
    
    virtual ~MagicKnightLightHealRing();
    
    virtual bool cast(Unit *unit);
    void effect(Unit *caster, Unit *unit, Item *item, Prop *prop);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicKnightSelfLightHeal : public Magic {
private:
public:
    MagicKnightSelfLightHeal();
    MagicKnightSelfLightHeal(MagicKnightSelfLightHeal &other);
    MagicKnightSelfLightHeal(char shape, int job, int skillNumber);
    
    virtual MagicKnightSelfLightHeal &operator=(MagicKnightSelfLightHeal &other);
    
    virtual ~MagicKnightSelfLightHeal();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicKnightSlash : public Magic {
private:
public:
    MagicKnightSlash();
    MagicKnightSlash(MagicKnightSlash &other);
    MagicKnightSlash(char shape, int job, int skillNumber);
    
    virtual MagicKnightSlash &operator=(MagicKnightSlash &other);
    
    virtual ~MagicKnightSlash();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicPaladinHealRing : public Magic {
private:
public:
    MagicPaladinHealRing();
    MagicPaladinHealRing(MagicPaladinHealRing &other);
    MagicPaladinHealRing(char shape, int job, int skillNumber);
    
    virtual MagicPaladinHealRing &operator=(MagicPaladinHealRing &other);
    
    virtual ~MagicPaladinHealRing();
    
    virtual bool cast(Unit *unit);
    void effect(Unit *caster, Unit *unit, Item *item, Prop *prop);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicPaladinSelfHeal : public Magic {
private:
public:
    MagicPaladinSelfHeal();
    MagicPaladinSelfHeal(MagicPaladinSelfHeal &other);
    MagicPaladinSelfHeal(char shape, int job, int skillNumber);
    
    virtual MagicPaladinSelfHeal &operator=(MagicPaladinSelfHeal &other);
    
    virtual ~MagicPaladinSelfHeal();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicPaladinSlash : public Magic {
private:
public:
    MagicPaladinSlash();
    MagicPaladinSlash(MagicPaladinSlash &other);
    MagicPaladinSlash(char shape, int job, int skillNumber);
    
    virtual MagicPaladinSlash &operator=(MagicPaladinSlash &other);
    
    virtual ~MagicPaladinSlash();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicWarriorStomp : public Magic {
private:
public:
    MagicWarriorStomp();
    MagicWarriorStomp(MagicWarriorStomp &other);
    MagicWarriorStomp(char shape, int job, int skillNumber);
    
    virtual MagicWarriorStomp &operator=(MagicWarriorStomp &other);
    
    virtual ~MagicWarriorStomp();
    
    virtual bool cast(Unit *unit);
    void effect(Unit *caster, Unit *unit, Item *item, Prop *prop);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicWarriorDeathCircle : public Magic {
private:
public:
    MagicWarriorDeathCircle();
    MagicWarriorDeathCircle(MagicWarriorDeathCircle &other);
    MagicWarriorDeathCircle(char shape, int job, int skillNumber);
    
    virtual MagicWarriorDeathCircle &operator=(MagicWarriorDeathCircle &other);
    
    virtual ~MagicWarriorDeathCircle();
    
    virtual bool cast(Unit *unit);
    void effect(Unit *caster, Unit *unit, Item *item, Prop *prop);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicWarriorSlash : public Magic {
private:
public:
    MagicWarriorSlash();
    MagicWarriorSlash(MagicWarriorSlash &other);
    MagicWarriorSlash(char shape, int job, int skillNumber);
    
    virtual MagicWarriorSlash &operator=(MagicWarriorSlash &other);
    
    virtual ~MagicWarriorSlash();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicHunterTripleFire : public Magic {
private:
public:
    MagicHunterTripleFire();
    MagicHunterTripleFire(MagicHunterTripleFire &other);
    MagicHunterTripleFire(char shape, int job, int skillNumber);
    
    virtual MagicHunterTripleFire &operator=(MagicHunterTripleFire &other);
    
    virtual ~MagicHunterTripleFire();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicHunterLightHeal: public Magic {
private:
public:
    MagicHunterLightHeal();
    MagicHunterLightHeal(MagicHunterLightHeal &other);
    MagicHunterLightHeal(char shape, int job, int skillNumber);
    
    virtual MagicHunterLightHeal &operator=(MagicHunterLightHeal &other);
    
    virtual ~MagicHunterLightHeal();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicHunterQuadStrike : public Magic {
private:
public:
    MagicHunterQuadStrike();
    MagicHunterQuadStrike(MagicHunterQuadStrike &other);
    MagicHunterQuadStrike(char shape, int job, int skillNumber);
    
    virtual MagicHunterQuadStrike &operator=(MagicHunterQuadStrike &other);
    
    virtual ~MagicHunterQuadStrike();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicArcherOctoStrike : public Magic {
private:
public:
    MagicArcherOctoStrike();
    MagicArcherOctoStrike(MagicArcherOctoStrike &other);
    MagicArcherOctoStrike(char shape, int job, int skillNumber);
    
    virtual MagicArcherOctoStrike &operator=(MagicArcherOctoStrike &other);
    
    virtual ~MagicArcherOctoStrike();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicArcherSnipe : public Magic {
private:
public:
    MagicArcherSnipe();
    MagicArcherSnipe(MagicArcherSnipe &other);
    MagicArcherSnipe(char shape, int job, int skillNumber);
    
    virtual MagicArcherSnipe &operator=(MagicArcherSnipe &other);
    
    virtual ~MagicArcherSnipe();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

class MagicArcherArrowPlatter : public Magic {
private:
public:
    MagicArcherArrowPlatter();
    MagicArcherArrowPlatter(MagicArcherArrowPlatter &other);
    MagicArcherArrowPlatter(char shape, int job, int skillNumber);
    
    virtual MagicArcherArrowPlatter &operator=(MagicArcherArrowPlatter &other);
    
    virtual ~MagicArcherArrowPlatter();
    
    virtual bool cast(Unit *unit);
    
    virtual Magic *clone();
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
