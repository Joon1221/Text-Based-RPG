#ifndef CAR_H
#define CAR_H

class Unit;
class Hero;

//------------------------------------------------------------------------------
// class Car: child class of class Unit
//------------------------------------------------------------------------------
class Car : public Unit {
protected:
    Hero *passenger;
    
    int carDir;
    int prevDir;
    bool idle;
    
public:
    Car();
    
    virtual ~Car();
    
    virtual void print();
    
    bool isCar();
    
    virtual int getCarDir();
    virtual void setCarDir(int carDir);
    virtual int getPrevDir();
    virtual void setPrevDir(int prevDir);
    
    virtual bool getIdle();
    virtual void setIdle(int idle);
    
    virtual void move(int moveDir);
    virtual void changeDirection(int moveDir);
    virtual void interact(Unit *unit);
    
    virtual void getOffCar();
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif

